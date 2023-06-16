#include <arduinoFFT.h>

#define SAMPLES 64               // FFTのサンプル数
#define SAMPLING_FREQUENCY 1000  // サンプリング周波数

/* ピン番号 */
const char swTopPin = 3;
const char swBottomPin = 2;
const char micTopPin = 0;
const char micBottomPin = 1;

/* 他変数  */
int micVal[2];  // マイク入力
bool swVal[2];  // スイッチ入力
double vReal[2][SAMPLES];
double vImag[2][SAMPLES];

unsigned int sampling_period_us;
unsigned long microseconds;

/* 関数 */
void read_val();
double* output_amp();
double calculate_phase_difference();

arduinoFFT FFT = arduinoFFT();

/* 構造体 */
struct mic_position {
  double top;
  double btm;
} McPost;

void setup() {
  Serial.begin(9600);
  pinMode(swTopPin, INPUT_PULLUP);
  pinMode(swBottomPin, INPUT_PULLUP);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  double* amp;
  double phaseDifference;

  read_val();
  amp = output_amp();
  phaseDifference = calculate_phase_difference();

  /* print debug
  for (int i = 0; i < 2; i++) {
    Serial.print(amp[i]);
    Serial.print(" ");
  }
  Serial.println(phaseDifference);
  /* ----------- */

  delay(1000);

  free(amp);
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

double* output_amp() {
  double* ret_amp = malloc(2 * sizeof(int));

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

  return ret_amp;
}

double calculate_phase_difference() {
  // FFTの各ビンの周波数ステップ（周波数解像度）
  double frequencyStep = SAMPLING_FREQUENCY / SAMPLES;

  // 224Hzの位相差を計算
  int targetFrequency = 224;
  int index = round(targetFrequency /
                    frequencyStep);  // ターゲット周波数のインデックスを計算
  double phaseTop = atan2(vImag[0][index], vReal[0][index]);
  double phaseBottom = atan2(vImag[1][index], vReal[1][index]);
  double phaseDifference = phaseTop - phaseBottom;  // 位相差を計算

  // ラジアンを度に変換
  phaseDifference = phaseDifference * (180.0 / PI);

  return phaseDifference;
}
