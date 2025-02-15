// int kp = 0;
// int d = 0;

// void Trace();
// {

// }
void ALL_White()
{
  /*if (LineState == LineState_AllWhite) {
    UpdateAllEyeValue();
    Serial.println("ALL_WHITE");
    if (lastState <= 3){
      WheelR.CW_DirectMode(-BaseMotorPWM - 10);
      WheelL.CW_DirectMode(-BaseMotorPWM + 10);
      delay(20);
      while(EyeCorValue[7] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_DirectMode(-BaseMotorPWM - 10);
        WheelL.CW_DirectMode(-BaseMotorPWM + 10);
        Serial.println(lastState);
      }
    } else if (lastState >= 11){
      WheelR.CW_DirectMode(BaseMotorPWM - 10);
      WheelL.CW_DirectMode(BaseMotorPWM + 10);
      delay(20);
      while(EyeCorValue[6] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_DirectMode(BaseMotorPWM - 10);
        WheelL.CW_DirectMode(BaseMotorPWM + 10);
        Serial.println(lastState);
      }
    } 
    else {
      while(LineState == LineState_AllWhite){
        UpdateAllEyeValue();
        LineState = LineStateCalculate();
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        delay(50);
      }
    }
  } */
  /*else if (LineState == LineState_AllBlack) {
    WheelL.Brake();
    WheelR.Brake();
    delay(100);
    Serial.print("left_h: ");
    for(int i : H_arr_l){
      Serial.print(i);
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("right_h: ");
    for(int i : H_arr_r){
      Serial.print(i);
      Serial.print(" ");
    }
    Serial.println();
    // while(1);
    // detect_greeeen();
  }*/
}