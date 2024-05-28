#ifndef GPIO_H
#define GPIO_H

#define LOW 0
#define HIGH 1
#define IN 0
#define OUT 1

int GPIOExport(int pin);
int GPIOUnexport(int pin);
int GPIODirection(int pin, int dir);

#endif // GPIO_H
