// sound2phase.ino
// 音声解析



// FFTのサンプル数とサンプリング周波数から、各サンプルが表す周波数の間隔（周波数解像度）を計算
double frequencyResolution = (double)SAMPLING_FREQUENCY / SAMPLES;
// 224Hzの成分が格納されている配列のインデックスを計算
int index = round(224 / frequencyResolution);

// 関数

void execute() {
  read_val();
  val_fft();
  calc_phase();
  ext_freq();
  delay(10);
}


//フーリエ変換
void val_fft() {
  for (int i = 0; i < 2; i++) {
    FFT.Windowing(vReal[i], SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal[i], vImag[i], SAMPLES, FFT_FORWARD);
    //FFT.ComplexToMagnitude(vReal[i], vImag[i], SAMPLES);
  }
}

//周波数抽出
void ext_freq() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < SAMPLES; j++) {
        vReal[i][j] = 0;
        vImag[i][j] = 0;
      
    }
  }
}

//角度計算
void calc_phase() {
  double vAngl[2];
  for (int i = 0; i < 2; i++) {
    vAngl[i] = atan2(vReal[i][index] , vImag[i][index]);
    
    Serial.print(vReal[i][index]);
    Serial.print(",");
    Serial.print(vImag[i][index]);
    Serial.print(",");
    Serial.println(vAngl[i]);
    
  }

  phase = vAngl[0] - vAngl[1];
  //Serial.println(index);
}
