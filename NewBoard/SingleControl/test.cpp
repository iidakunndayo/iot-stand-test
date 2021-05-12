#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define HIGH 1
#define LOW 0

const int LCD_id = 0x3e;
int LCD_fd = wiringPiI2CSetup(LCD_id);

const int LCD_backlight = 7;
const int LCD_reset = 0; 
const int relay_on = 4;
const int relay_off = 5;

void LCDSetup(){
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x38);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x39);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x14);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x70);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x56);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x6c);
    usleep(200E3);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x38);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x0c);
    wiringPiI2CWriteReg8(LCD_fd, 0x00, 0x01);
    usleep(1e3);
}

int main() {
    if (LCD_fd == -1){
        return 1;
    } else {
        wiringPiSetup();
        pinMode(LCD_backlight, OUTPUT);
        pinMode(LCD_reset, OUTPUT);
        pinMode(relay_on, OUTPUT);
        pinMode(relay_off, OUTPUT);

        digitalWrite(LCD_backlight, HIGH);
        digitalWrite(LCD_reset, HIGH);
        digitalWrite(relay_off, LOW);
        digitalWrite(relay_on, LOW);

        LCDSetup();
    }
    
    int count = 0;
    while (count < 10){
        digitalWrite(relay_on, HIGH);
        digitalWrite(relay_off, LOW);
        std::cout << "on" << std::endl;
        sleep(1);

        digitalWrite(relay_on, LOW);
        digitalWrite(relay_off, HIGH);
        std::cout << "off" << std::endl;
        sleep(1);

        count ++;
    }
}