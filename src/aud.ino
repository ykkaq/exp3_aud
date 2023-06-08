// 音源推定
// memo:ブレッドボードの上をtop,下をbottomとする．

#include <arduinoFFT.h>

#define SAMPLES 64               // FFTのサンプル数
#define SAMPLING_FREQUENCY 1000  // サンプリング周波数

/* ピン番号 */
const char swTopPin = 3;
const char swBottomPin = 2;
const char micTopPin = 0;
const char micBottomPin = 1;

unsigned int sampling_period_us;
unsigned long microseconds;

/* 他変数  */
int micVal[2];  // マイク入力
bool swVal[2];  // スイッチ入力
double vReal[2][SAMPLES];
double vImag[2][SAMPLES];

/* 関数 */
void read_val();
double* exec_amp(double* ret);

arduinoFFT FFT = arduinoFFT();

void setup() {
  Serial.begin(9600);
  pinMode(swTopPin, INPUT_PULLUP);
  pinMode(swBottomPin, INPUT_PULLUP);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  double amp[2];

  read_val();
  output_amp(int* amp);

  Serial.println(amp);

  delay(1000);
}

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

double* output_amp(double* ret_amp) {
  // double ret_amp[2];

  for (int i = 0; i < 2; i++) {
    /* フーリエ変換 */
    FFT.Windowing(vReal[i], SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal[i], vImag[i], SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal[i], vImag[i], SAMPLES);

    // FFTの各ビンの周波数ステップ（周波数解像度）
    double frequencyStep = SAMPLING_FREQUENCY / SAMPLES;

    // 224Hzの振幅を探す
    int targetFrequency = 224;
    int index = round(targetFrequency /
                      frequencyStep);  // ターゲット周波数のインデックスを計算
    double amplitude = vReal[i][index];  // ターゲット周波数の振幅を取得

    ret_amp[i] = amplitude;
  }

  Serial.println();

  return ret_amp;
}
