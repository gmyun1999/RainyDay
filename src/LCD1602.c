#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "LCD1602.h"


int lcd_addr;
int blen;
int i2c_file;

void write_word(int data) {
    int temp = data;
    if (blen == 1) {
        temp |= 0x08;
    } else {
        temp &= 0xF7;
    }
    i2c_smbus_write_byte(i2c_file, temp);
}

void send_command(int comm) {
    int buf = comm & 0xF0;
    buf |= 0x04;
    write_word(buf);
    usleep(2000);
    buf &= 0xFB;
    write_word(buf);

    buf = (comm & 0x0F) << 4;
    buf |= 0x04;
    write_word(buf);
    usleep(2000);
    buf &= 0xFB;
    write_word(buf);
}

void send_data(int data) {
    int buf = data & 0xF0;
    buf |= 0x05;
    write_word(buf);
    usleep(2000);
    buf &= 0xFB;
    write_word(buf);

    buf = (data & 0x0F) << 4;
    buf |= 0x05;
    write_word(buf);
    usleep(2000);
    buf &= 0xFB;
    write_word(buf);
}

void LCD_init(int addr, int bl) {
    lcd_addr = addr;
    blen = bl;

    char *filename = (char*)"/dev/i2c-1";
    if ((i2c_file = open(filename, O_RDWR)) < 0) {
        printf("Failed to open the i2c bus\n");
        exit(1);
    }

    if (ioctl(i2c_file, I2C_SLAVE, lcd_addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave\n");
        exit(1);
    }

    send_command(0x33);
    usleep(5000);
    send_command(0x32);
    usleep(5000);
    send_command(0x28);
    usleep(5000);
    send_command(0x0C);
    usleep(5000);
    send_command(0x01);
    i2c_smbus_write_byte(i2c_file, 0x08);
}

void LCD_clear() {
    send_command(0x01);
}

void LCD_openLight() {
    i2c_smbus_write_byte(i2c_file, 0x08);
    close(i2c_file);
}

void LCD_write(int x, int y, const char* str) {
    if (x < 0) x = 0;
    if (x > 15) x = 15;
    if (y < 0) y = 0;
    if (y > 1) y = 1;

    int addr = 0x80 + 0x40 * y + x;
    send_command(addr);

    for (int i = 0; i < strlen(str); i++) {
        send_data(str[i]);
    }
}
