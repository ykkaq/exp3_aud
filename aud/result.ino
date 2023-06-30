#include <math.h>

// result.ino
// 解析と結果の橋渡し

// 変数
int step = -1;  //評価方法
int sub_step = -1;

// 出力
void result() {
  startup();

  if (up_swVal[0]) {
    step = (step + 1) % 3;
    sub_step = -1;

    Serial.print("> ");
    Serial.println(step + 1);
  }

  switch (step) {
    case 0:
      first();
      break;
    case 1:
      second();
      break;
    case 2:
      therd();
      break;
  }
}

// ラジアン to degree
void phase2angle(bool rotate, int i) {
  angle[i] = phase * 180 / M_PI;
  //  adjust phase
  angle[i] += 90;
  // rotate curcuit
  if (rotate) {
    angle[i] += 90;
  }
  angle[i] = round(angle[i]) % 360;
}

// 1
void first() {
  // bottom b
  if (up_swVal[1] == false) {
    return;
  }

  // 実行
  execute();
  // rad to deg
  phase2angle(false, 0);

  Serial.println(angle[0]);

  if (angle[0] <= 60) {
    Serial.print("left");
  } else if (angle[0] <= 120) {
    Serial.print("middle");
  } else if (angle [0] <= 180){
    Serial.print("right");
  } else {
    Serial.print("out of range");
  }
  Serial.print("\n");
}

void second() {
  if (up_swVal[1] == false) {
    return;
  } else {
    sub_step++;
  }

  execute();
  phase2angle(sub_step % 2 == 1, sub_step);

  Serial.print(sub_step);
  Serial.print(": ");
  Serial.println(angle[sub_step]);

  if (sub_step == 1) {
    angle[0] = (angle[0] + angle[1]) / 2;
    Serial.print("ave: ");
    Serial.println(angle[0]);
    sub_step = -1;
  }
}

void therd() {
  if (up_swVal[1] == false) {
    return;
  } else {
    sub_step++;
  }

  execute();

  phase2angle(sub_step % 2 == 1, sub_step);

  Serial.print(sub_step);
  Serial.print(": ");
  Serial.println(angle[sub_step]);

  if (sub_step % 2 == 1) {
    angle[sub_step - 1] = (angle[sub_step - 1] + angle[sub_step]) / 2;
    Serial.print("ave: ");
    Serial.println(angle[sub_step / 2]);
  }

  if (sub_step == 3) {
    double dist = 25;
    double m[2];
    double sx[2] = { -1 * dist / 2, dist / 2 };
    for (int i = 0; i < 2; i++) {
      m[i] = tan(angle[i] * M_PI / 180);
    }
    // x = - (m2 * x2 - m1 * x1) / (m1 - m2)
    double px = -1 * (m[1] * sx[1] - m[0] * sx[0]) / (m[1] - m[2]);
    // y = m1 * x - m1 * x1 = m1 ( x - x1)
    double py = m[0] * (px - sx[0]);

    Serial.print("point: (");
    Serial.print(px);
    Serial.print(", ");
    Serial.print(py);
    Serial.println(")");
    sub_step = -1;
  }
}
