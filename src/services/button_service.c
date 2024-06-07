#include "button_service.h"
#include "step.h"
#include "plant.h"
#include "services/lcd1602_service.h"
#include "services/communication_service.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int plant_index;
extern int plant_quantity;
extern STEP current_step;
extern pthread_t comm_thread; // 통신 스레드

void* step1onPressDown1(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    plant_index = (plant_index + 1) % plant_count;
    printf("Switched plant is: %s\n", plants[plant_index].name);
    char bottom_message[32];
    snprintf(bottom_message, sizeof(bottom_message), "plant: %s", plants[plant_index].name);
    update_lcd_message("STEP1", bottom_message);
    return NULL;
}

void* step1onPressDown2(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    printf("Selected: %s\n", plants[plant_index].name);
    current_step = STEP2;
    printf("Current step: %s\n", stepToString(current_step));
    update_lcd_message("STEP2", "Select quantity");
    return NULL;
}

void* step2onPressDown1(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    plant_quantity++;
    printf("Current Quantity: %d\n", plant_quantity);
    char bottom_message[32];
    snprintf(bottom_message, sizeof(bottom_message), "Quantity: %d", plant_quantity);
    update_lcd_message("STEP2", bottom_message);
    return NULL;
}

void* step2onPressDown2(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    if (plant_quantity == 0) {
        printf("개수 선택이 우선되어야함\n");
        update_lcd_message("STEP2", "Select first");
    } else {
        printf("개수입력완료: %d개\n", plant_quantity);

        // 식물 정보 출력
        printf("Plant: %s\n", plants[plant_index].name);
        printf("min_temperature_humidity: %.1f\n", plants[plant_index].min_humidity);
        printf("min_water_level: %.1f\n", plants[plant_index].min_water_level);
        printf("min_light_intensity: %.1f\n", plants[plant_index].min_light_intensity);

        char bottom_message[32];
        
        snprintf(bottom_message, sizeof(bottom_message), "Selected %d %s", plant_quantity, plants[plant_index].name);
        update_lcd_message("STEP2", bottom_message);

        sleep(2); // 타이밍 문제
        update_lcd_message("hello user", "everything ready");

        // 통신 스레드 시작
        if (pthread_create(&comm_thread, NULL, communication_thread, NULL) != 0) {
            printf("Failed to create communication thread\n");
        }
        
        // 이후 다른 로직 필요할수도 ㅇㅇ?
        
    }
    return NULL;
}

void* onLongClick(BUTTON* btn) {
    // 안씀
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    return NULL;
}

void* onPressDown1(BUTTON* btn) {
    if (current_step == STEP1) {
        return step1onPressDown1(btn);
    } else if (current_step == STEP2) {
        return step2onPressDown1(btn);
    }
    return NULL;
}

void* onPressDown2(BUTTON* btn) {
    if (current_step == STEP1) {
        return step1onPressDown2(btn);
    } else if (current_step == STEP2) {
        return step2onPressDown2(btn);
    }
    return NULL;
}

void* onPressUp(BUTTON* btn) {
    // 안씀
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    return NULL;
}
