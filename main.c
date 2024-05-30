#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "button.h"
#include "config.h"
#include "services/button_service.h"
#include "services/plant_service.h"
#include "services/lcd1602_service.h"
#include "step.h"
#include <unistd.h>

// 설정 파일 경로
#define CONFIG_FILE "config.txt"

pthread_t *pt1;
pthread_t *pt2;
pthread_t lcd_thread;

// BUTTON 구조체 초기화
BUTTON *button1;
BUTTON *button2;

int main(void)
{
    int pins[4];
    int polling_rates[2];

    if (read_config(CONFIG_FILE, pins, polling_rates) != 0)
    {
        return 1;
    }

    initializePlants();

    // 첫 번째 버튼 초기화
    button1 = (BUTTON *)malloc(sizeof(BUTTON));
    button1->pin = pins[0];
    button1->pout = pins[1];
    button1->polling_rate = polling_rates[0];
    button1->onLongClick = onLongClick;
    button1->onPressDown = onPressDown1;
    button1->onPressUp = onPressUp;

    pt1 = initButton(button1);

    // 두 번째 버튼 초기화
    button2 = (BUTTON *)malloc(sizeof(BUTTON));
    button2->pin = pins[2];
    button2->pout = pins[3];
    button2->polling_rate = polling_rates[1];
    button2->onLongClick = onLongClick;
    button2->onPressDown = onPressDown2;
    button2->onPressUp = onPressUp;

    pt2 = initButton(button2);

    // LCD 출력 스레드 생성
    if (pthread_create(&lcd_thread, NULL, lcd_display_thread, NULL) != 0) {
        printf("Failed to create LCD display thread\n");
        return 1;
    }

    if (pt1 == NULL || pt2 == NULL)
    {
        printf("button init fail\n");
        return 1;
    }
    else
    {
        printf("Hello Buttons!\n");

        while (1) {
            sleep(1);
        }

        // 아래 코드는 더 이상 사용되지 않지만, 참고로 남겨둠
        // pthread_join(*pt1, NULL);
        // pthread_join(*pt2, NULL);
        // stop_lcd_thread(); // 종료 신호 전송
        // pthread_join(lcd_thread, NULL); // LCD 스레드 종료 대기
        // printf("buttons disposed. please enter to rerun\n");
        // char c[1000];
        // fgets(c, 1000, stdin);
    }
    // free(button1);
    // free(button2);
    return 0;
}
