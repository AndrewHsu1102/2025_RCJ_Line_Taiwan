#include "SimpleMotor.h"
#include "OLD_EyeMini_V100.h"
#include "OLP_ESLOV_V100.h"

#define Button0_Pin 11
#define Button1_Pin 12
byte WLED = 22;
byte RLED = 23;
byte GLED = 24;
byte BLED = 25;
byte YLED = 26;

#define EyeBoardLeftNum 0x07
#define EyeBoardRightNum 0x0b

byte EyeValue[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte EyeCorValue[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// byte EyeValue_R[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// byte EyeValue_G[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// byte EyeValue_B[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int EyeValue_H[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte EyeValue_S[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte EyeValue_V[14] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#define MaxMotorPWM 80
#define BaseMotorPWM 50
#define EyeCor_Maxvalue 100
#define EyeCor_WhiteThreshold 80
#define EyeCor_BlackThreshold 20

byte LineState = 0;
#define LineState_AllWhite 1
#define LineState_AllBlack 2
#define LineState_LeftBlack 3
#define LineState_RightBlack 4

#define BlackValue 70

motor WheelR;
motor WheelL;
OLP_ESLOV_V100Class ESLOV;
OLD_EyeMini_V100Class EyeMiniR;
OLD_EyeMini_V100Class EyeMiniL;

#define NUM_SENSORS 14

// PD control parameters
float Kp = 20.0;  // Proportional constant
float Kd = 60;    // Derivative constant

int lastError = 0;
int lastState = 0;

int lastIntegral[5];
int cntIntegral = -1;

void MotorInit() {
  WheelR.Init(32, 33, 9);
  WheelL.Init(34, 35, 10);
}

void BoardInit() {
  Serial.begin(1000000);
  Serial.println("BoardInit");
}

void setup() {
  BoardInit();
  LEDInit();
  delay(1500);
  ESLOV.WireSetup(0);
  MotorInit();
  EyeInit();
  UpdateEyeLimitSoftware();
  Serial.println("Finish Setup");
  WheelR.Brake();
  WheelL.Brake();
}

void loop() {
  //======forward=======
  WheelR.CW_DirectMode(-60);
  WheelL.CW_DirectMode(60);
  //====================
  // delay(1000);
  // WheelR.Brake();
  // WheelL.Brake();
  // delay(1000);
  //======backward=======
  // WheelR.CW_DirectMode(-100);
  // WheelL.CW_DirectMode(-100);
  //=====================
  // delay(1000);
  // WheelR.Slide();
  // WheelL.Slide();
  // delay(1000);

  UpdateAllEyeValue();
  Serial.println("UpdateAllEyeValue");
  // PrintEyeCorValue();
  PrintEyeValue_H();
  PrintEyeValue_S();
  PrintEyeValue_V();
  // detect_red();
  detect_green();
  // tune_D();
  // PD_control();
}

void detect_green()
// 等一下要寫中線校正（if eyecor[i] < black_number）{看i在哪邊，轉反邊}   跨線問題(跨黑看到綠)
{
  byte isfullblack = LineStateCalculate();
  if (isfullblack == LineState_AllBlack) {
    // WheelR.CW_DirectMode(-100);
    // WheelL.CW_DirectMode(100);
    delay(250);
    WheelR.Brake();
    WheelL.Brake();
    while (1)
      ;
  } else {
    int ifgreen = 0;  //0 = no green; 1 = left green; 2 = right green; 3 = both green;
    for (int i = 2; i < 12; i++) {
      if (EyeValue_V[i] < 40 && EyeValue_H[i] < 155 && i != 6 && i != 7)  //有看到
      {
        if (i < 7)  //前半段有看到
        {
          if (!ifgreen) {
            ifgreen = 1;  //左邊
            // WheelR.CW_DirectMode(-100);
            WheelL.CW_DirectMode(100);
            delay(25);
            WheelR.Brake();
            WheelL.Brake();
            for (int j = 8; j < 12; j++) {
              if (EyeValue_V[j] < 45 && EyeValue_H[j] < 160) {
                ifgreen = 3;
              }
            }
          }
        } else  //後半段有看到
        {
          ifgreen = 2;  //右邊
          WheelR.CW_DirectMode(-100);
          // WheelL.CW_DirectMode(100);
          delay(25);
          WheelR.Brake();
          WheelL.Brake();
          for (int j = 2; j < 6; j++) {
            if (EyeValue_V[j] < 45 && EyeValue_H[j] < 155) {
              ifgreen = 3;
            }
          }
        }
      }
    }

    if (ifgreen) {
      Serial.print("GREEEEEEEEEEENNNNNN!!!!!!!!!!!!!!!!   ");
      if (ifgreen == 1) {
        Serial.print("Left");
        WheelR.CW_DirectMode(-100);
        WheelL.CW_DirectMode(-100);
        delay(265);
        WheelR.Brake();
        WheelL.Brake();
        while (1)
          ;
      } else if (ifgreen == 2) {
        Serial.print("Right");
        WheelR.CW_DirectMode(100);
        WheelL.CW_DirectMode(100);
        delay(265);
        WheelR.Brake();
        WheelL.Brake();
        while (1)
          ;
      } else if (ifgreen == 3) {
        Serial.print("Both");
        WheelR.CW_DirectMode(-100);
        WheelL.CW_DirectMode(-100);
        delay(530);
        WheelR.Brake();
        WheelL.Brake();
        while (1)
          ;
      }
      Serial.println();
    } else {
      Serial.print("No Green No Green No Green No Green No Green No Green No Green No Green No Green No Green No Green");
      Serial.println();
    }
  }
}
void detect_red() {
  int ifred = 0;
  for (int i = 0; i < 14; i++) {
    if (EyeValue_H[i] > 300 && EyeValue_V[i] > 55) {
      ifred++;
    }
  }
  if (ifred > 10) {
    WheelR.Brake();
    WheelL.Brake();
    while (1)
      ;
  }
}
