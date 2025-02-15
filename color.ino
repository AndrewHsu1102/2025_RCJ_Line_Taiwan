void detect_green()
// 等一下要寫中線校正（if eyecor[i] < black_number）{看i在哪邊，轉反邊}   跨線問題(跨黑看到綠)
{
  int is_green[14] = { 0 };
  int green_cnt = 0;
  int green_total = 0;
  UpdateAllEyeValue();
  int ifgreen = 0;  //0 = no green; 1 = left green; 2 = right green; 3 = both green;
  for (int i = 0; i < 14; i++) {
    if (/*EyeValue_V[i] < 50 && */ EyeValue_H[i] < 165)  //有看到
    {
      is_green[i] = 1 * (i + 1);
      Serial.print("\tis_green[i] = ");
      Serial.print(is_green[i]);
      green_total += is_green[i];
      green_cnt++;
      // is_green[i] = 1;
    }
  }
  Serial.println();
  Serial.print("green_cnt = ");
  Serial.print(green_cnt);
  int green_position = green_total / green_cnt;
  Serial.print("\tgreen_position = ");
  Serial.print(green_position);
  Serial.print("\tposition = ");
  Serial.println(position);
  if (green_cnt > 4 && green_position >= (position - 1) && green_position <= (position + 1)) {
    ifgreen = 3;
  } else if (green_position >= (position + 1)) {
    UpdateAllEyeValue();
    both_brake();
    delay(100);
    both_back_waitMode(10);
    both_brake();
    delay(100);
    WheelL.CW_WaitMode(BaseMotorPWM, 30);
    // WheelR.CW_WaitMode(BaseMotorPWM, 9);
    both_brake();
    green_cnt = 0;
    UpdateAllEyeValue();
    //while(1);
    for (int i = 0; i < 14; i++) {
      if (/*EyeValue_V[i] < 50 && */ EyeValue_H[i] < 165)  //有看到
      {
        // is_green[i] = 1 * (i + 1);
        Serial.print("\tis_green[i] = ");
        Serial.print(i);
        // green_total += is_green[i];
        green_cnt++;
        // is_green[i] = 1;
      }
    }
    // green_position = green_total / green_cnt;

    if (green_cnt >= 5)
    {
      ifgreen = 3;
    }
    else
    {
      ifgreen = 2;
    }
    WheelL.CW_WaitMode(-BaseMotorPWM, 30);
    // WheelR.CW_WaitMode(BaseMotorPWM, 9);
    both_brake();
    delay(200);
  } else if (green_position <= (position - 1) && green_position > 0) {
    
    UpdateAllEyeValue();
    both_brake();
    delay(100);
    both_back_waitMode(10);
    both_brake();
    delay(100);
    WheelR.CCW_WaitMode(BaseMotorPWM, 30);
    // WheelL.CCW_WaitMode(BaseMotorPWM, 9);
    both_brake();
    green_cnt = 0;
    UpdateAllEyeValue();
    for (int i = 0; i < 14; i++) {
      if (/*EyeValue_V[i] < 50 && */ EyeValue_H[i] < 165)  //有看到
      {
        Serial.print("\tis_green[i] = ");
        Serial.print(i);
        // green_total += (i + 1);
        green_cnt++;
        // is_green[i] = 1;
      }
    }
    // green_position = green_total / green_cnt;
    if (green_cnt >= 5)
    {
      ifgreen = 3;
    }
    else
    {
      ifgreen = 1;
    }
    WheelR.CW_WaitMode(BaseMotorPWM, 30);
    // WheelR.CW_WaitMode(BaseMotorPWM, 9);
    both_brake();
  }
  int left_green = 0;
  int right_green = 0;
  // for(int i = 0; i < position; i++){
  //   left_green += is_green[i];
  // }
  // for (int i = position;i < 14; i++){
  //   right_green += is_green[i];
  // }
  // if (left_green == right_green){
  //   ifgreen = 3;
  // } else if (left_green > right_green){
  //   ifgreen = 1;
  // } else {
  //   ifgreen = 2;
  // }

  Serial.print("\t ifgreen = ");
  Serial.print(ifgreen);
  Serial.println();

  if (ifgreen) {
    // while(1)
    // {
    //   both_brake();
    //   UpdateAllEyeValue();
    //   PrintEyeCorValue();
    //   PrintEyeValue_H();
    //   PrintEyeValue_S();
    //   PrintEyeValue_V();
    //   Serial.print("Position = ");
    //   Serial.println(position);
    //   Serial.print("green_Position = ");
    //   Serial.println(green_position);
    //   Serial.print("green_cnt = ");
    //   Serial.println(green_cnt);
    //   Serial.print("\t ifgreen = ");
    //   Serial.print(ifgreen);
    //   Serial.println();
    // }
    Serial.print("GREEEEEEEEEEENNNNNN!!!!!!!!!!!!!!!!   ");
    both_brake();
    // //while(1);
    if (ifgreen == 1) {
      GLED_ON();
      both_brake();
      // delay(2000);
      Serial.print("Left");
      // delay(2000);
      both_waitMode(200);
      both_Left_waitMode(180);
      both_brake();
      // while (1);
        // ;
      // while (EyeCorValue[6] >= EyeCor_BlackThreshold && EyeCorValue[7] >= EyeCor_BlackThreshold) {
      //   UpdateAllEyeValue();
      //   WheelR.CW_DirectMode(-BaseMotorPWM);
      //   WheelL.CW_DirectMode(-BaseMotorPWM);
      //   WLED_ON();
      // }
      // WLED_OFF();
      // delay(265);
      both_brake();
      // delay(1000);
      GLED_OFF();
      UpdateAllEyeValue();
      both_waitMode(20);
      // while (1)
      // ;
    } else if (ifgreen == 2) {
      RLED_ON();
      Serial.print("Right");
      
      both_waitMode(200);
      both_Right_waitMode(150);
      both_brake();
      // while (1);
        // ;
      both_brake();
      RLED_OFF();
      UpdateAllEyeValue();
      both_waitMode(20);
    } else if (ifgreen == 3) {
      Serial.print("Both");
      // delay(530);
      GLED_ON();
      RLED_ON();
      both_waitMode(150);
      both_Right_waitMode(350);
      WheelR.Brake();
      WheelL.Brake();
      // while (1);
        // ;
      // while (1)
      // ;
    }
    Serial.println();
  } else {
    Serial.print("No Green No Green No Green No Green No Green No Green No Green No Green No Green No Green No Green");
    Serial.println();
  }
  // }
  ifgreen = 0;
}