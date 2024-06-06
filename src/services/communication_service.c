#include "communication_service.h"
#include "socket.h"
#include "plant.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <cjson/cJSON.h>

// 센서 및 액추에이터 상태를 저장할 구조체
typedef struct {
    int humidity;
    int water_level;
    int light_intensity;
    int water_pump;
    int led;
    int speaker;
} SensorActuatorStatus;

SensorActuatorStatus status = {0, 0, 0, 0, 0, 0};

void *communication_thread(void *arg) {
    (void)arg; // 사용되지 않는 매개변수를 무시합니다.

    int server_fd = setup_server_socket();
    printf("Server listening on port %d\n", PORT);

    while (1) {
        int new_socket = accept_client_connection(server_fd);
        if (new_socket < 0) continue;

        char buffer[1024] = {0};
        char response[1024] = {0};
        int read_bytes = read(new_socket, buffer, 1024);
        if (read_bytes < 0) {
            perror("read failed");
            close(new_socket);
            continue;
        }

        buffer[read_bytes] = '\0'; // Ensure null-terminated string
        printf("Received message: %s\n", buffer);

        // JSON 파싱 및 처리
        cJSON *json = cJSON_Parse(buffer);
        if (json == NULL) {
            printf("Failed to parse JSON\n");
            close(new_socket);
            continue;
        }

        const cJSON *type = cJSON_GetObjectItem(json, "type");
        if (cJSON_IsString(type) && (type->valuestring != NULL)) {
            if (strcmp(type->valuestring, "sensor") == 0) {
                const cJSON *sensor_type = cJSON_GetObjectItem(json, "sensor_type");
                const cJSON *value = cJSON_GetObjectItem(json, "value");

                if (cJSON_IsString(sensor_type) && (sensor_type->valuestring != NULL) && cJSON_IsNumber(value)) {
                    if (strcmp(sensor_type->valuestring, "humidity") == 0) {
                        status.humidity = value->valueint;
                    } else if (strcmp(sensor_type->valuestring, "water_level") == 0) {
                        status.water_level = value->valueint;
                    } else if (strcmp(sensor_type->valuestring, "light_intensity") == 0) {
                        status.light_intensity = value->valueint;
                    }
                    sprintf(response, "{\"status\":\"ok\"}");
                }
            } else if (strcmp(type->valuestring, "actuator") == 0) {
                const cJSON *actuator_type = cJSON_GetObjectItem(json, "actuator_type");

                if (cJSON_IsString(actuator_type) && (actuator_type->valuestring != NULL)) {
                    int action = 0;

                    if (plant_index < 0 || plant_index >= plant_count) {
                        printf("Invalid plant index: %d\n", plant_index);
                    } else {
                        if (strcmp(actuator_type->valuestring, "water_pump") == 0) {
                            action = (status.humidity < plants[plant_index].min_humidity);
                        } else if (strcmp(actuator_type->valuestring, "led") == 0) {
                            action = (status.light_intensity < plants[plant_index].min_light_intensity);
                        } else if (strcmp(actuator_type->valuestring, "speaker") == 0) {
                            action = (status.water_level < plants[plant_index].min_water_level);
                        }
                    }

                    sprintf(response, "{\"action\":%d}", action);
                }
            }
        }

        send(new_socket, response, strlen(response), 0);
        printf("Sent response: %s\n", response);
        close(new_socket);
        cJSON_Delete(json);
    }
}
