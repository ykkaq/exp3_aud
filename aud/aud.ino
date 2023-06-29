#include <arduinoFFT.h>
#include <math.h>

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
double amp[2];  //振幅
arduinoFFT FFT = arduinoFFT();
unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[2][SAMPLES];
double vImag[2][SAMPLES];
double phase;
double angle[4];

/* 関数 */
void debug();
void one_step();
void read_val();
void val_fft();
void calculate_phase_difference();
void ext_freq();
void rev_fft();
void calc_phase();

//  -------------------
void setup() {
  Serial.begin(9600);
  pinMode(swTopPin, INPUT_PULLUP);
  pinMode(swBottomPin, INPUT_PULLUP);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  
  read_val();
  val_fft();
  ext_freq();
  calc_phase();
  delay(10);

  //debug();

  delay(500);
  exit(1);
}

void one_step() {
}



void debug() {
  for (int i = 0; i < 2; i++) {
    Serial.println(i);
    for (int j = 0; j < SAMPLES; j++) {
      Serial.print(j);
      Serial.print(",");
      Serial.print(vReal[i][j]);
      Serial.print(",");
      Serial.print(vImag[i][j]);
      Serial.print(",");
      Serial.println(" ");
    }
    Serial.println("---");
  }


  Serial.print(phase);
  Serial.print(",");
  Serial.print(phase * 180 / M_PI);
  Serial.println("");
}
