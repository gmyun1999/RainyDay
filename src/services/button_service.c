#include "button_service.h"
#include "step.h"
#include "plant.h"
#include <stdio.h>
#include <stdlib.h>

extern int plant_index;
extern int plant_quantity;
extern STEP current_step;

void* step1onPressDown1(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    plant_index = (plant_index + 1) % plant_count;
    printf("Switched plant is: %s\n", plants[plant_index].name);
    return NULL;
}

void* step1onPressDown2(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    printf("Selected: %s\n", plants[plant_index].name);
    current_step = STEP2;
    printf("Current step: %s\n", stepToString(current_step));
    return NULL;
}

void* step2onPressDown1(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    plant_quantity++;
    printf("Current Quantity: %d\n", plant_quantity);
    return NULL;
}

void* step2onPressDown2(BUTTON* btn) {
    (void)btn; // 사용되지 않는 매개변수 경고 방지
    if (plant_quantity == 0) {
        printf("개수 선택이 우선되어야함\n");
    } else {
        printf("개수입력완료: %d개\n", plant_quantity);
        // 식물 정보 출력
        printf("Plant: %s\n", plants[plant_index].name);
        printf("Temperature: %.1f\n", plants[plant_index].temperature);
        printf("Humidity: %.1f\n", plants[plant_index].humidity);
        printf("Water Amount: %.1f\n", plants[plant_index].water_amount);
        printf("Light Intensity: %.1f\n", plants[plant_index].light_intensity);
        exit(0);
    }
    return NULL;
}
