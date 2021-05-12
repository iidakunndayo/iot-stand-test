#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define HIGH 1
#define LOW 0

const int LCD_id = 0x3e; //LCDのI2Cレジスタ指定
const int LCD_backlight = 7; //バックライト操作ピン番号指定
const int LCD_reset = 0; //物理リセット操作ピン指定

int LCD_fd = wiringPiI2CSetup(LCD_id); //LCDのファイル識別子設定

//モータードライバのピン指定
const int driver_enable = 3;
const int driver_in1 = 4;
const int driver_in2 = 5;

void LCDSetup(){ //LCDの初期化
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
    if(LCD_fd == -1) { //識別子が -1 のとき戻り値1で終了、それ以外ならLCDのバックライトを点灯し表示を初期化
        return 1;
    } else {
        pinMode(LCD_backlight, OUTPUT);
        pinMode(LCD_reset, OUTPUT);
        pinMode(driver_enable, OUTPUT);
        pinMode(driver_in1, OUTPUT);
        pinMode(driver_in2, OUTPUT);

        digitalWrite(LCD_backlight, HIGH);
        digitalWrite(LCD_reset, HIGH);
        LCDSetup();
        digitalWrite(driver_enable, HIGH);
        digitalWrite(driver_in1, LOW);
        digitalWrite(driver_in2, LOW);
    }

    int count = 0;
    while(count < 10){ //リレーのON/OFFを10回(多分)繰り返す
        digitalWrite(driver_in1, HIGH);
        digitalWrite(driver_in2, LOW);
        std::cout << "on" << std::endl;
        sleep(1);

        digitalWrite(driver_in1, LOW);
        digitalWrite(driver_in2, HIGH);
        std::cout << "off" << std::endl;
        sleep(1);

        count ++;
    }

    /* 終了処理
    digitalWrite(driver_in1, LOW);
    digitalWrite(driver_in2, LOW);
    digitalWrite(driver_enable, LOW);
    */
}