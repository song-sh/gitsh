#include <U8glib.h>
#include <Wire.h> 
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>    

//  Variables

const int PulseWire = 0;       
SoftwareSerial btSerial(2,3); //Rx,Tx          
int Threshold = 550;          
Adafruit_MLX90614 mlx = Adafruit_MLX90614();                              
PulseSensorPlayground pulseSensor;  
U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9, 8);// SW SPI Com: SCK(D0) = 13, MOSI(D1) = 11, CS = 10, A0(DC) = 9, Res = 8
char chConvert_Int[16];                       // 정수 -> 문자열 변환용 캐릭터형 변수 선언
bool bHeart_Status = false;   

void setup() {   
  Serial.begin(9600);
  btSerial.begin(9600);
  mlx.begin();
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   
  if (pulseSensor.begin()) {
    Serial.println("80");  
  }
}

void loop() {
 int myBPM = pulseSensor.getBeatsPerMinute(); 
 itoa(myBPM, chConvert_Int, 10);               // Convert integer to string
 if (pulseSensor.sawStartOfBeat()) {            
  bHeart_Status = !bHeart_Status;  // 반전
  }
  delay(20);                                      
  u8g.firstPage();  
  do{
    Draw();
    } while( u8g.nextPage() ); 
 
 if (pulseSensor.sawStartOfBeat()) {            
 if(mlx.readObjectTempC()>= 25.0){
  if(myBPM >= 20 && myBPM <= 205){                        
  Serial.println(myBPM);
  btSerial.println(myBPM);   
  }
  else{
   Serial.println(0);
   btSerial.println(0);
  }
 }
  delay(1000);                    
}
}
