
void LEDInit() {
  pinMode(WLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  digitalWrite(WLED, HIGH);
  digitalWrite(RLED, HIGH);
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, HIGH);
  digitalWrite(YLED, HIGH);
}

void WLED_ON() {
  digitalWrite(WLED, LOW);
}
void RLED_ON() {
  digitalWrite(RLED, LOW);
}
void GLED_ON() {
  digitalWrite(GLED, LOW);
}
void BLED_ON() {
  digitalWrite(BLED, LOW);
}
void YLED_ON() {
  digitalWrite(YLED, LOW);
}

void WLED_OFF() {
  digitalWrite(WLED, HIGH);
}
void RLED_OFF() {
  digitalWrite(RLED, HIGH);
}
void GLED_OFF() {
  digitalWrite(GLED, HIGH);
}
void BLED_OFF() {
  digitalWrite(BLED, HIGH);
}
void YLED_OFF() {
  digitalWrite(YLED, HIGH);
}
void LEDTest() {
  WLED_ON();
  delay(300);
  WLED_OFF();
  RLED_ON();
  delay(300);
  RLED_OFF();
  GLED_ON();
  delay(300);
  GLED_OFF();
  BLED_ON();
  delay(300);
  BLED_OFF();
  YLED_ON();
  delay(500);
  YLED_OFF();
}
