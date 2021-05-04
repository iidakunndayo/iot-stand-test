#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define HIGH 1
#define LOW 0

//I2Cのid指定とGPIOのピン指定
const int LCD_id = 0x3e;
const int Expander1_id = 0x20;
const int Expander2_id = 0x21;
const int LCD_backlight = 7;
const int LCD_reset = 0;

//I2Cのファイル識別子の初期化
int LCD_fd = wiringPiI2CSetup(LCD_id);
int Expander1_fd = wiringPiI2CSetup(Expander1_id);
int Expander2_fd = wiringPiI2CSetup(Expander2_id);

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
    if (LCD_fd == -1 && Expander1_fd == -1 && Expander2_fd == -1){
        std::cout << "I2C Error!!" << std::endl;
        return -1;
    } else {
        wiringPiSetup();                    //GPIOのアクティベーション
        pinMode(LCD_backlight, OUTPUT);     //LCDのバックライトピンの出力設定
        pinMode(LCD_reset, OUTPUT);         //LCDの物理リセットピンの出力設定
        digitalWrite(LCD_backlight ,HIGH);  //LCDのバックライトの点灯
        digitalWrite(LCD_reset, HIGH);      //LCDの物理リセットのピンをHIGHに設定(LOWでリセット)
        wiringPiI2CWriteReg8(Expander1_fd, 0x00, 0x00);
        wiringPiI2CWriteReg8(Expander1_fd, 0x01, 0x00);
        wiringPiI2CWriteReg8(Expander2_fd, 0x00, 0x00);
        wiringPiI2CWriteReg8(Expander2_fd, 0x01, 0x00);
    }

    int count = 0;
    while (count != 9){
        wiringPiI2CWriteReg8(Expander1_fd, 0x14, 0xff);
        wiringPiI2CWriteReg8(Expander2_fd, 0x14, 0xff);
        wiringPiI2CWriteReg8(Expander1_fd, 0x15, 0x00);
        wiringPiI2CWriteReg8(Expander2_fd, 0x15, 0x00);
        std::cout << "on" << std::endl;
        sleep(1);

        wiringPiI2CWriteReg8(Expander1_fd, 0x14, 0x00);
        wiringPiI2CWriteReg8(Expander2_fd, 0x14, 0x00);
        wiringPiI2CWriteReg8(Expander1_fd, 0x15, 0xff);
        wiringPiI2CWriteReg8(Expander2_fd, 0x15, 0xff);
        std::cout << "off" << std::endl;
        sleep(1);
        count ++;
    }
    
}