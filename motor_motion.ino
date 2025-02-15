void both_waitMode(int step){
  // back 300 steps
  WheelR.CCW_DirectMode(BaseMotorPWM);
  WheelL.CW_DirectMode(BaseMotorPWM);
  WheelR.StartInterrupt();
  WheelL.StartInterrupt();
  while (motor::InterruptCounter0 <= step) {
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
void both_brake()
{
  WheelR.Brake();
  WheelL.Brake();
}