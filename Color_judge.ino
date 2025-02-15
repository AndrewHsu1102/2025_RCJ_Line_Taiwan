void detect_green()
// 等一下要寫中線校正（if eyecor[i] < black_number）{看i在哪邊，轉反邊}   跨線問題(跨黑看到綠)
{
  byte isfullblack = LineStateCalculate();
  // if (isfullblack == LineState_AllBlack) {
  //   // WheelR.CW_DirectMode(-100);
  //   // WheelL.CW_DirectMode(100);
  //   delay(250);
  //   WLED_ON();
  //   Serial.println("ALLBLAKKKKKKKKKKKKKKKKKK~~!!!!");
  //   WheelR.Brake();
  //   WheelL.Brake();
  //   while (1)
  //     ;
  // } 
  // else {
    int ifgreen = 0;  //0 = no green; 1 = left green; 2 = right green; 3 = both green;
    for (int i = 2; i < 12; i++) {
      if (EyeValue_V[i] < 40 && EyeValue_H[i] < 155 && i != 6 && i != 7)  //有看到
      {
        if (i < 7)  //前半段有看到
        {
          if (!ifgreen) {
            ifgreen = 1;  //左邊
            WheelR.CW_DirectMode(-100);
            // WheelL.CW_DirectMode(100);
            delay(25);
            WheelR.Brake();
            WheelL.Brake();
            for (int j = 8; j < 12; j++) {
              if (EyeValue_V[j] < 45 && EyeValue_H[j] < 155) {
                ifgreen = 3;
              }
            }
          }
        } else  //後半段有看到
        {
          ifgreen = 2;  //右邊
          // WheelR.CW_DirectMode(-100);
          WheelL.CW_DirectMode(100);
          delay(30);
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
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        delay(70);
        while(EyeCorValue[6] >= EyeCor_BlackThreshold && EyeCorValue[7] >= EyeCor_BlackThreshold)
        {
          UpdateAllEyeValue();
          WheelR.CW_DirectMode(-BaseMotorPWM);
          WheelL.CW_DirectMode(-BaseMotorPWM);
        }
        // delay(265);
        GLED_ON();
        WheelR.Brake();
        WheelL.Brake();
        delay(1000);
        GLED_OFF();
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(-BaseMotorPWM);
        delay(50);
        // while (1)
          // ;
      } else if (ifgreen == 2) {
        Serial.print("Right");
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        delay(70);
        while(EyeCorValue[6] >= EyeCor_BlackThreshold && EyeCorValue[7] >= EyeCor_BlackThreshold)
        {
          UpdateAllEyeValue();
          WheelR.CW_DirectMode(BaseMotorPWM);
          WheelL.CW_DirectMode(BaseMotorPWM);
        }
        // delay(265);
        RLED_ON();
        WheelR.Brake();
        WheelL.Brake();
        delay(1000);
        WheelR.CW_DirectMode(BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        delay(50);
        RLED_OFF();
        // while (1)
        //   ;
      } else if (ifgreen == 3) {
        Serial.print("Both");
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        delay(200);
        WheelR.CW_DirectMode(-100);
        WheelL.CW_DirectMode(-100);
        // delay(530);
        GLED_ON();
        RLED_ON();
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
  // }
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

// void detect_greeeen() {
//   int ifgreen_l = 0, ifgreen_r = 0;
//   for (int i : H_arr_l) {  // left
//     ifgreen_l += i;
//   }
//   for (int i : H_arr_r) {
//     ifgreen_r += i;
//   }
//   if (ifgreen_l >= 3) ifgreen_l = 1;
//   else ifgreen_l = 0;
//   if (ifgreen_r >= 3) ifgreen_r = 1;
//   else ifgreen_r = 0;
//   // if (ifgreen > 0) {
//   //   while (1) {
//   //     Serial.println(ifgreen);
//   //     WheelR.Brake();
//   //     WheelL.Brake();
//   //     PrintEyeValue_H();
//   //     PrintEyeValue_S();
//   //     PrintEyeValue_V();
//   //   }
//   // }
//   if (ifgreen_l && ifgreen_r) {
//     GLED_ON();
//     RLED_ON();
//     both_waitMode(50);
//     // delay(50);
//     both_Right_waitMode(step180);
//     // WheelR.Brake();
//     // WheelL.Brake();
//     // delay(20);

//     // delay(200);
//     // UpdateAllEyeValue();
//     // while (EyeCorValue[6] >= EyeCor_BlackThreshold || EyeCorValue[7] >= EyeCor_BlackThreshold) {
//     //   UpdateAllEyeValue();
//     //   WheelR.CW_DirectMode(BaseMotorPWM);
//     //   WheelL.CW_DirectMode(BaseMotorPWM);
//     // }
//     // WheelR.Brake();
//     // WheelL.Brake();
//     // delay(20);
//     while (1)
//       ;
//     GLED_OFF();
//     RLED_OFF();
//   } else if (ifgreen_l) {
//     RLED_ON();
//     both_waitMode(100);
//     // delay(50);
//     both_Right_waitMode(step90);
//     while (1)
//       ;
//     RLED_OFF();
//   } else if (ifgreen_r) {
//     GLED_ON();
//     both_waitMode(100);
//     // delay(50);
//     both_Left_waitMode(step90);
//     while (1)
//       ;
//     GLED_OFF();
//   }
// }