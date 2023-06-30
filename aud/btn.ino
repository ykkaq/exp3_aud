void startup(){
  swVal[0] = !digitalRead(swTopPin);
  swVal[1] = !digitalRead(swBottomPin);

  for(int i=0;i<2;i++){
    if((swVal[i] == HIGH)&& (old_swVal[i] == LOW)){
      up_swVal[i] = HIGH;
    }else{
      up_swVal[i] = LOW;
    }
  }

  for(int i=0;i<2;i++){
    old_swVal[i] = swVal[i];
  }
}
