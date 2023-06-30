// front.ino
// マイクとarduinoの間

void read_val() {
  for (int i = 0; i < SAMPLES; i++) {
    micVal[0] = analogRead(micTopPin);
    micVal[1] = analogRead(micBottomPin);

    for (int j = 0; j < 2; j++) {
      vReal[j][i] = (double)micVal[j];
      vImag[j][i] = 0;
    }

    delayMicroseconds(sampling_period_us);
  }
}
