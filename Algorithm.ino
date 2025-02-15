
byte LineStateCalculate(void) {

  // 檢查是否全白
  byte isWhiteCounter = 0;
  for (byte i = 0; i < 14; i++) {
    if (EyeCorValue[i] > EyeCor_WhiteThreshold)
      isWhiteCounter++;
  }
  if (isWhiteCounter >= 12)
    return LineState_AllWhite;

  // 檢查是否全黑
  byte isBlackCounter = 0;
  for (byte i = 0; i < 14; i++) {
    if (EyeCorValue[i] < EyeCor_BlackThreshold)
      isBlackCounter++;
  }
  if (isBlackCounter >= 12)
    return LineState_AllBlack;

  // 檢查 6, 5, 4, 3, 2, 1, 0是否小於黑色閾值
  byte isLeftBlackCounter = 0;
  for (int i = 6; i >= 0; i--) {
    if (EyeCorValue[i] < EyeCor_BlackThreshold)
      isLeftBlackCounter++;
  }
  if (isLeftBlackCounter >= 5)
    return LineState_LeftBlack;

  // 檢查 13, 12, 11, 10, 9, 8 ,7 是否小於黑色閾值
  byte isRightBlackCounter = 0;
  for (int i = 13; i >=7; i--) {
    if (EyeCorValue[i] < EyeCor_BlackThreshold)
      isRightBlackCounter++;
  }
  if (isRightBlackCounter >= 5)
    return LineState_RightBlack;

  // if (Abs_Direction_Total_Eye_Value >= Const_CornerTotalValue) {
  //   return CoordinateUpdateFlag;
  // }
  return 0;
}

void both_waitMode(int step){
  // back 300 steps
  WheelR.CCW_DirectMode(BaseMotorPWM);
  WheelL.CW_DirectMode(BaseMotorPWM);
  WheelR.StartInterrupt();
  WheelL.StartInterrupt();
  while (motor::InterruptCounter1 <= step) {
  }
  WheelR.Brake();
  WheelL.Brake();
  WheelR.StopInterrupt();
  WheelL.StopInterrupt();
}
void both_back_waitMode(int step){
  // back 300 steps
  WheelR.CW_DirectMode(BaseMotorPWM);
  WheelL.CCW_DirectMode(BaseMotorPWM);
  WheelR.StartInterrupt();
  WheelL.StartInterrupt();
  while (motor::InterruptCounter1 <= step) {
  }
  WheelR.Brake();
  WheelL.Brake();
  WheelR.StopInterrupt();
  WheelL.StopInterrupt();
}
void both_Left_waitMode(int step){
  // back 300 steps
  WheelR.CCW_DirectMode(BaseMotorPWM);
  WheelL.CCW_DirectMode(BaseMotorPWM);
  WheelR.StartInterrupt();
  WheelL.StartInterrupt();
  while (motor::InterruptCounter1 <= step) {
  }
  WheelR.Brake();
  WheelL.Brake();
  WheelR.StopInterrupt();
  WheelL.StopInterrupt();
}
void both_Right_waitMode(int step){
  // back 300 steps
  WheelR.CW_DirectMode(BaseMotorPWM);
  WheelL.CW_DirectMode(BaseMotorPWM);
  WheelR.StartInterrupt();
  WheelL.StartInterrupt();
  while (motor::InterruptCounter1 <= step) {
  }
  WheelR.Brake();
  WheelL.Brake();
  WheelR.StopInterrupt();
  WheelL.StopInterrupt();
}

void H_Integral(){
  cntIntegral_h++;
  if (cntIntegral_h > sizeof(H_arr_l)-1) cntIntegral_h = 0;
  int h_l = 0, h_r = 0;
  for (int i = 0; i < 7; i++) {
    if (EyeValue_H[i] < 150 && EyeValue_S[i] >= 25)
      h_l = 1;
  }
  for (int i = 7; i < 13; i++) {
    if (EyeValue_H[i] < 150 && EyeValue_S[i] >= 25)
      h_r = 1;
  }
  H_arr_l[cntIntegral_h] = h_l;
  H_arr_r[cntIntegral_h] = h_r;
}
