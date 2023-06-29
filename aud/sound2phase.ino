// sound2phase.ino
// 音声解析

// FFTのサンプル数とサンプリング周波数から、各サンプルが表す周波数の間隔（周波数解像度）を計算
double frequencyResolution = (double)SAMPLING_FREQUENCY / SAMPLES;
// 224Hzの成分が格納されている配列のインデックスを計算
int index = round(224 / frequencyResolution);


//　関数
//フーリエ変換
void val_fft() {
  for (int i = 0; i < 2; i++) {
    FFT.Windowing(vReal[i], SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal[i], vImag[i], SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal[i], vImag[i], SAMPLES);
  }
}


//絶対値計算
double calc_abs(double a, double b) {
  return sqrt(pow(a, 2) + pow(b, 2));
}


//周波数抽出
void ext_freq() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < SAMPLES; j++) {
      if (j != index) {
        vReal[i][j] = 0;
        vImag[i][j] = 0;
      }
    }
  }
}

//逆フーリエ変換
void rev_fft() {
  for (int i = 0; i < 2; i++) {
    FFT.Compute(vReal[i], vImag[i], SAMPLES, FFT_REVERSE);
  }
}

//角度計算
void calc_phase() {
  double vAngl[2];
  for (int i = 0; i < 2; i++) {
    vAngl[i] = calc_abs(vReal[i][index], vImag[i][index]);
  }

  phase = vAngl[0] - vAngl[1];
  Serial.println(index);
}
