// if (i <= position)  //前半段有看到
//   {
//     if (!ifgreen) {
//       ifgreen = 1;  //左邊
//       WheelR.CW_DirectMode(-100);
//       // WheelL.CW_DirectMode(100);
//       delay(25);
//       WheelR.Brake();
//       WheelL.Brake();
//       for (int j = 8; j < 12; j++) {
//         if (EyeValue_V[j] < 45 && EyeValue_H[j] < 155) {
//           ifgreen = 3;
//         }
//       }
//     }
//   } else  //後半段有看到
//   {
//     ifgreen = 2;  //右邊
//     // WheelR.CW_DirectMode(-100);
//     WheelL.CW_DirectMode(100);
//     delay(30);
//     WheelR.Brake();
//     WheelL.Brake();
//     for (int j = 2; j < 6; j++) {
//       if (EyeValue_V[j] < 45 && EyeValue_H[j] < 155) {
//         ifgreen = 3;
//       }
//     }
//   }