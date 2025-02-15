
void EyeInit() {
  EyeMiniR.SetBoardConfig(EyeBoardRightNum, Wire);
  EyeMiniL.SetBoardConfig(EyeBoardLeftNum, Wire);
  EyeMiniR.Setup(ColorMode_Blue, LightMode_Quincunx, 8, 70);
  EyeMiniL.Setup(ColorMode_Blue, LightMode_Quincunx, 8, 70);
  //  EyeMiniL.PrintEyeValueLimit(0);
  //  EyeMiniR.PrintEyeValueLimit(0);
}

void UpdateEyeLimitSoftware(void) {
  if (digitalRead(Button0_Pin) == 0) {
    while (digitalRead(Button1_Pin) == 1) {
      EyeMiniL.ReplaceEyeValueLimit();
      EyeMiniR.ReplaceEyeValueLimit();
      EyeMiniL.PrintEyeValueLimit(0);
      EyeMiniR.PrintEyeValueLimit(0);
      WLED_ON();
    }
    EyeMiniL.DownloadEyeValueLimit();
    EyeMiniL.PrintEyeValueLimit(0);
    delay(100);
    EyeMiniR.DownloadEyeValueLimit();
    EyeMiniR.PrintEyeValueLimit(0);
    delay(100);
    WLED_OFF();
  }
}

void UpdateAllEyeValue(void) {
  EyeMiniL.MeasureAll();
  EyeMiniR.MeasureAll();
  delay(6);
  EyeMiniL.Calculate_Advance(1, 1, 0);
  EyeMiniR.Calculate_Advance(1, 1, 0);
  // EyeMiniL.Calculate();
  // EyeMiniR.Calculate();
  EyeCorValue[0] = EyeMiniL.CorValue[0];
  EyeCorValue[1] = EyeMiniL.CorValue[1];
  EyeCorValue[2] = EyeMiniL.CorValue[2];
  EyeCorValue[3] = EyeMiniL.CorValue[3];
  EyeCorValue[4] = EyeMiniL.CorValue[4];
  EyeCorValue[5] = EyeMiniL.CorValue[5]; 
  EyeCorValue[6] = EyeMiniL.CorValue[6];
  EyeCorValue[7] = EyeMiniR.CorValue[0];
  EyeCorValue[8] = EyeMiniR.CorValue[1];
  EyeCorValue[9] = EyeMiniR.CorValue[2];
  EyeCorValue[10] = EyeMiniR.CorValue[3];
  EyeCorValue[11] = EyeMiniR.CorValue[4];
  EyeCorValue[12] = EyeMiniR.CorValue[5];
  EyeCorValue[13] = EyeMiniR.CorValue[6];

  EyeValue_H[0]  = EyeMiniL.Value_H[0];
  EyeValue_H[1]  = EyeMiniL.Value_H[1];
  EyeValue_H[2]  = EyeMiniL.Value_H[2];
  EyeValue_H[3]  = EyeMiniL.Value_H[3];
  EyeValue_H[4]  = EyeMiniL.Value_H[4];
  EyeValue_H[5]  = EyeMiniL.Value_H[5];
  EyeValue_H[6]  = EyeMiniL.Value_H[6];
  EyeValue_H[7]  = EyeMiniR.Value_H[0];
  EyeValue_H[8]  = EyeMiniR.Value_H[1];
  EyeValue_H[9]  = EyeMiniR.Value_H[2];
  EyeValue_H[10] = EyeMiniR.Value_H[3];
  EyeValue_H[11] = EyeMiniR.Value_H[4];
  EyeValue_H[12] = EyeMiniR.Value_H[5];
  EyeValue_H[13] = EyeMiniR.Value_H[6];

  EyeValue_S[0] = EyeMiniL.Value_S[0];
  EyeValue_S[1] = EyeMiniL.Value_S[1];
  EyeValue_S[2] = EyeMiniL.Value_S[2];
  EyeValue_S[3] = EyeMiniL.Value_S[3];
  EyeValue_S[4] = EyeMiniL.Value_S[4];
  EyeValue_S[5] = EyeMiniL.Value_S[5];
  EyeValue_S[6] = EyeMiniL.Value_S[6];
  EyeValue_S[7] = EyeMiniR.Value_S[0];
  EyeValue_S[8] = EyeMiniR.Value_S[1];
  EyeValue_S[9]  = EyeMiniR.Value_S[2];
  EyeValue_S[10] = EyeMiniR.Value_S[3];
  EyeValue_S[11] = EyeMiniR.Value_S[4];
  EyeValue_S[12] = EyeMiniR.Value_S[5];
  EyeValue_S[13] = EyeMiniR.Value_S[6];

  EyeValue_V[0] = EyeMiniL.Value_V[0];
  EyeValue_V[1] = EyeMiniL.Value_V[1];
  EyeValue_V[2] = EyeMiniL.Value_V[2];
  EyeValue_V[3] = EyeMiniL.Value_V[3];
  EyeValue_V[4] = EyeMiniL.Value_V[4];
  EyeValue_V[5] = EyeMiniL.Value_V[5];
  EyeValue_V[6] = EyeMiniL.Value_V[6];
  EyeValue_V[7] = EyeMiniR.Value_V[0];
  EyeValue_V[8] = EyeMiniR.Value_V[1];
  EyeValue_V[9]  = EyeMiniR.Value_V[2];
  EyeValue_V[10] = EyeMiniR.Value_V[3];
  EyeValue_V[11] = EyeMiniR.Value_V[4];
  EyeValue_V[12] = EyeMiniR.Value_V[5];
  EyeValue_V[13] = EyeMiniR.Value_V[6];
}

void PrintEyeCorValue(void)  // byte num
{
  Serial.print("PrintEyeCorValue: ");
  for (int i = 0; i < 14; i++) {
    // Serial.print(EyeMiniL.Value_H[i]);
    Serial.print(EyeCorValue[i]);
    Serial.print("\t");
  }
  Serial.println("...finish");
}

void PrintEyeValue_H(void)  // byte num
{
  Serial.print("PrintEyeValue_H: ");
  for (int i = 0; i < 14; i++) {
    // Serial.print(EyeMiniL.Value_H[i]);
    Serial.print(EyeValue_H[i]);
    Serial.print("\t");
    if(i == 6)
    {
      Serial.print("||");
    }
  }
  Serial.println("...finish");
}

void PrintEyeValue_S(void)  // byte num
{
  Serial.print("PrintEyeValue_S: ");
  for (int i = 0; i < 14; i++) {
    // Serial.print(EyeMiniL.Value_H[i]);
    Serial.print(EyeValue_S[i]);
    Serial.print("\t");
    if(i == 6)
    {
      Serial.print("||");
    }
  }
  Serial.println("...finish");
}
void PrintEyeValue_V(void)  // byte num
{
  Serial.print("PrintEyeValue_V: ");
  for (int i = 0; i < 14; i++) {
    // Serial.print(EyeMiniL.Value_H[i]);
    Serial.print(EyeValue_V[i]);
    Serial.print("\t");
    if(i == 6)
    {
      Serial.print("||");
    }
  }
  Serial.println("...finish");
}

