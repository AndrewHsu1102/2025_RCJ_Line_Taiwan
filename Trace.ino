void PD_control(){
  // Read sensors
  LineState = LineStateCalculate();
  if (LineState == LineState_AllWhite){
    UpdateAllEyeValue();
    Serial.println("ALL_WHITE");
    if (lastState <= 6){
      while(EyeCorValue[7] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(-BaseMotorPWM);
        Serial.println(lastState);
      }
    } else if (lastState >= 8){
      while(EyeCorValue[6] >= EyeCor_BlackThreshold){
        UpdateAllEyeValue();
        WheelR.CW_DirectMode(BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
        Serial.println(lastState);
      }
    } else {
      while(LineState == LineState_AllWhite){
        UpdateAllEyeValue();
        LineState = LineStateCalculate();
        WheelR.CW_DirectMode(-BaseMotorPWM);
        WheelL.CW_DirectMode(BaseMotorPWM);
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

  WheelL.CW_DirectMode(rightSpeed);
  WheelR.CW_DirectMode(-leftSpeed);
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


