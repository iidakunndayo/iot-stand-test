#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define HIGH 1
#define LOW 0

const int LCD_id = 0x3e;                                //LCDのI2CのID指定
const int expander_id [4] = {0x20, 0x21, 0x22, 0x23};   //ExpanderのI2Cの各IDを指定し、配列に格納
int expander_fd[4];                                     //ファイル識別子の配列の宣言
int id;                                                 //配列の要素の番号を示す変数の宣言

int LCD_fd = wiringPiI2CSetup(LCD_id);                  //LCDのファイル識別子の設定

const int LCD_backlight = 7;                            //LCDのバックライトの操作をするピン番号の指定
const int LCD_reset = 0;                                //     物理リセット

void LCDSetup(){                                        //LCDの初期化
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
    //Expanderのファイル識別子の設定
    for(id = 0; id < 4; id++){
        expander_fd[id] = wiringPiI2CSetup(expander_id[id]);
    }

    //I2Cのファイル識別子がどれかひとつでも -1 となった場合、戻り値1で終了、それ以外の場合はLCDの初期化をし、バックライトの点灯とExpanderのピンを出力に設定
    if(LCD_fd == -1 || expander_fd[0] == -1 || expander_fd[1] == -1 || expander_fd[2] == -1 || expander_fd[3] == -1) {
        return 1;
    } else {
        pinMode(LCD_backlight, OUTPUT);
        pinMode(LCD_reset, OUTPUT);
        LCDSetup();
        digitalWrite(LCD_backlight, HIGH);
        digitalWrite(LCD_reset, HIGH);
        
        for(id = 0; id < 4; id++) {
            wiringPiI2CWriteReg8(expander_fd[id], 0x00, 0x00);
            wiringPiI2CWriteReg8(expander_fd[id], 0x01, 0x00);
        }
        
    }

    //リレーのON/OFFを10回繰り返す
    int count = 0;
    while(count < 10) {
        for(id = 0; id < 4; id++) {
            wiringPiI2CWriteReg8(expander_fd[id], 0x15, 0xff);
            wiringPiI2CWriteReg8(expander_fd[id], 0x14, 0x00);
        }
        std::cout << "on" << std::endl;

        for(id = 0; id < 4; id++) {
            wiringPiI2CWriteReg8(expander_fd[id], 0x15, 0x00);
            wiringPiI2CWriteReg8(expander_fd[id], 0x14, 0xff);
        }
        std::cout << "off" << std::endl;

        count++;
    }
}