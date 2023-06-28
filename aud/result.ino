// result.ino
// 解析と結果の橋渡し

/*
void all();
void phase2angle(bool);
void first();
void second();
void therd();
*/



void all(){
  //　ボタンでやる
}

void phase2angle(bool rotate){
  // rad 2 deg
  int i=0;
  angle[i] = phase * 180 / M_PI;
  //  adjust phase 
  angle[i] = phase - 90;
  // rotate curcuit 
  if(rotate){
    angle[i] += 90;
  }
}

void first(){
  Serial.println("<1st>");

  if(angle < -60){
    Serial.print("left");
  }else if(angle > 60){
    Serial.print("middle");
  }else{
    Serial.print("right");
  }
  Serial.print("\n");
}

void second(){
  int i=0;
  Serial.println("<2nd>");
  
  Serial.print(i);
  Serial.print(": ");
  Serial.println(angle[i]);
  

}

void therd(){
  //
  Serial.println("<3rd>");

  
}


void 