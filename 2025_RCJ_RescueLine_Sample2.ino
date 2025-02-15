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
float Kd = 60;   // Derivative constant

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
  delay(1000);
  ESLOV.WireSetup(0);
  MotorInit();
  EyeInit();
  UpdateEyeLimitSoftware();
}

void loop() {
  //======forward=======
  // WheelR.CW_Mode(-100);
  // WheelL.CW_Mode(100);
  //====================
  // delay(1000);
  // WheelR.Brake();
  // WheelL.Brake();
  // delay(1000);
  //======backward=======
  // WheelR.CW_Mode(-100);
  // WheelL.CW_Mode(-100);
  //=====================
  // delay(1000);
  // WheelR.Slide();
  // WheelL.Slide();
  // delay(1000);

  UpdateAllEyeValue();
  // PrintEyeCorValue();
  // PrintEyeValue_S();
  tune_D();
  PD_control();
}

void PD_control(){
  // Read sensors
  LineState = LineStateCalculate();
  if (LineState == LineState_AllWhite){
    UpdateAllEyeValue();
    Serial.println("ALL_WHITE");
    if (lastState <= 6){
      while(EyeCorValue[7] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_Mode(-BaseMotorPWM);
        WheelL.CW_Mode(-BaseMotorPWM);
        Serial.println(lastState);
      }
    } else if (lastState >= 8){
      while(EyeCorValue[6] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_Mode(BaseMotorPWM);
        WheelL.CW_Mode(BaseMotorPWM);
        Serial.println(lastState);
      }
    } else {
      while(LineState == LineState_AllWhite){
        UpdateAllEyeValue();
        LineState = LineStateCalculate();
        WheelR.CW_Mode(-BaseMotorPWM);
        WheelL.CW_Mode(BaseMotorPWM);
        Serial.println(lastState);
      }
    }
  }
  int position = 0;
  for (int i : EyeCorValue){
    Serial.print(i);
    Serial.print("  ");
  }
  Serial.println();
  int addCor = 0;
  for (int i = 0; i < NUM_SENSORS; i++) {
    position += (i+1) * abs(100 - EyeCorValue[i]);  // Weighted position
    addCor += abs(100 - EyeCorValue[i]);
  }
  Serial.println();
  // Serial.println(totalActiveSensors);
  // Calculate error
  float error = 0;

  // lastState = 0;
  // cntIntegral++;
  // if (cntIntegral > sizeof(lastIntegral)-1) cntIntegral = 0;
  // lastIntegral[cntIntegral] = position / addCor;
  // for (int i : lastIntegral) lastState += i;
  // lastState /= sizeof(lastIntegral);
  Serial.print("LastState: ");
  Serial.println(lastState);
  lastState = position / addCor;

  error = 7.5 - (position / addCor); 
  // Calculate derivative
  int derivative = error - lastError;

  // PD correction
  int correction = Kp * error + Kd * derivative;
  // Serial.println(correction);

  // Update last error
  lastError = error;

  // Adjust motor speeds
  int leftSpeed = BaseMotorPWM + correction;
  int rightSpeed = BaseMotorPWM - correction;

  // Constrain motor speeds
  leftSpeed = constrain(leftSpeed, 0, MaxMotorPWM);
  rightSpeed = constrain(rightSpeed, 0, MaxMotorPWM);

  WheelL.CW_Mode(rightSpeed);
  WheelR.CW_Mode(-leftSpeed);
}

void tune_P(){
  if (!digitalRead(Button1_Pin)) {
    Kp++;
    delay(100);
  } else if (!digitalRead(Button0_Pin)){
    Kp--;
    delay(100); 
  }
  if (Kp >= 100) Kp = 100;
  else if (Kp <= 0) Kp = 0;
  Serial.println(Kp);
}
void tune_D(){
  if (!digitalRead(Button1_Pin)) {
    Kd++;
    delay(100);
  } else if (!digitalRead(Button0_Pin)){
    Kd--;
    delay(100); 
  }
  if (Kd >= 100) Kd = 100;
  else if (Kd <= 0) Kd = 0;
  Serial.println(Kd);
}


