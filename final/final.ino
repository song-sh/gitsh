#include<Servo.h>
#include<SoftwareSerial.h>
#define FAN 6
#include<DHT11.h>

SoftwareSerial bt(2,3);
Servo servo;

int angle = 2;

int IR1 = A1;

int LED0 = 10;
int LED1 = 11;
int LED2 = 12;
int LED3 = 13;

int i;
int num1 = 1;
int total1 = 0;
int average1 = 0;

DHT11 dht11(pin);

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  bt.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(FAN, OUTPUT);

  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  if(bt.available() > 0) {
    int data = bt.read();
    int err;
    float temp, hunmi;
     if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else                                //에러일 경우 처리
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
    delay(500);
  for(i = 0;i <= num1;i++){
    float v = analogRead(IR1) * (5.0/1023.0);
    float di = 60.495 * pow(v, -1.1904);
    total1 = total1 + di;
    delay(100);
  }
  average1 = (int)total1 / num1;
  if(i >= num1){
    i = 0;
    total1 = 0;
  }
 
    servo.write(180);
    delay(1000);
    if(average1 < 50) {
      servo.write(0);
      if(temp >= 25) {
        digitalWrite(FAN, HIGH);
      }
      else {
        digitalWrite(FAN, LOW);
      }
      delay(2000);
      digitalWrite(LED0,HIGH);
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      delay(5000);
    }
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
  }
}
  
  
