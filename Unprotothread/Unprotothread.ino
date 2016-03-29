#include "pt.h"
#include <IRremote.h>
#include <IRremoteTools.h>

static int state = 1;
char cmd;

const int TrigPin = 2;
const int EchoPin = 3;
const int TrigPin1 = 4;
const int EchoPin1 = 5;
const int TrigPin2 = 6;
const int EchoPin2 = 7;

const int left1 = 8;
const int left2 = 9;
const int right1 = 10;
const int right2 = 11;

char g = 'G';
char s = 'S';
char r = 'R';
char t = 'T';
char b = 'B';

float cm;
float cm1;
float cm2;

void go(){
    digitalWrite(left1,!state);
    digitalWrite(left2,state);
    digitalWrite(right1,!state);
    digitalWrite(right2,state);  
}
//
void back(){
    digitalWrite(left1,state);
    digitalWrite(left2,!state);
    digitalWrite(right1,state);
    digitalWrite(right2,!state); 
}
//
void left(){
    digitalWrite(left1,!state);
    digitalWrite(left2, state);
    digitalWrite(right1, state);
    digitalWrite(right2, !state);
}
//
void right(){
    digitalWrite(left1,state);
    digitalWrite(left2, !state);
    digitalWrite(right1, !state);
    digitalWrite(right2, state);
}
//
void stop(){
  
}
int measure(){
    digitalWrite(TrigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin,LOW);
/*超声波传感器的探头被遮挡或者距离过短的时候声波无法反射
从而收不到返回声波，会返回一个很大的值，此为特殊情况*/
    float CM;
    CM = pulseIn(EchoPin,HIGH)/58.0;
    return CM;  
}
int measure1(){
    digitalWrite(TrigPin1,LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin1,HIGH);
    delayMicroseconds(10);//10微秒的高电平时间
    digitalWrite(TrigPin1,LOW);
    float CM1;
    CM1 = pulseIn(EchoPin1,HIGH) / 58.0;//通过IO输出一个高电平，高电平持续时间就是超声波从发射到返回的时间
    return CM1;
}
int measure2(){
    digitalWrite(TrigPin2,LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin2,LOW);
    float CM2;
    CM2 = pulseIn(EchoPin2,HIGH) / 58.0; 
    return CM2;
}
void setup(){
  Serial.begin(9600);
  pinMode(EchoPin,INPUT);
  pinMode(TrigPin1,OUTPUT);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin1,INPUT);
  pinMode(TrigPin2,OUTPUT);
  pinMode(EchoPin2,INPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  
}
void loop(){
  cm = measure();
  if(cm>50){
    while(Serial.available() > 0){//判断窗口缓冲器中有没有数据
    cmd = Serial.read();

    if(cmd == 'P'){//停止
      /*Stop*/

    }
    else if(cmd == 'R'){//右转
    right();
    }
    else if(cmd == 'L'){//左转
    left();
    }
    else if(cmd == 'B'){//后退
    back();
    }
    else{//前进
    go();
    }
  }
 }
 else{
    /*左侧测距*/
    cm1 = measure1();
    /*右侧测距*/
    cm2 = measure2();
//判断完成后，结果存入变量
    int index;//较空旷一边
    int side;//另一边
    int ns;//当前的状态量
    if(cm1 > cm2){
      index = cm1;
      side = cm2;
      ns = !state;    
    }

    else{
      index = cm2;
      side = cm1;
      ns = state;      
    }

    do{//转圈，转到前方测距大于50
    digitalWrite(left1, ns);
    digitalWrite(left2, !ns);
    digitalWrite(right1, ns);
    digitalWrite(right2, !ns);
    }while(cm > 50);
    do{//转到应转角度后，直行
    go();
    }while(side > 50 && cm > 50);
  } 
}

