int HW = 13;
void setup() {
  Serial.begin(9600);
  pinMode(HW,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  int cm = digitalRead(13);
  Serial.print(cm);
  Serial.println("cm");
  //未检测到为0，检测到为1
  if(cm == 1){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  
  for(int i = 0;i < 5;i++){
    digitalWrite(4,HIGH);
    delay(1000);
    digitalWrite(4,LOW);
    delay(1000);
  }
  }
  else{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);

    for(int j = 2;j < 6;j++){
    digitalWrite(j,HIGH);
    delay(1000);
    digitalWrite(j,LOW);
  }
}
}
