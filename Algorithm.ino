
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
