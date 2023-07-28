// ** Phần khai báo thư viện, các biến toàn cục *****
#include<Servo.h>    
#include <string.h>

// Khai báo thư viện dùng để điều khiển Servo  
#define SERVO_PIN_1 9              // Chân PWM kết nối với Servo ( Lưu ý: bao nhiêu Servo sẽ khai báo nhiêu đó chân Pin)
#define SERVO_PIN_2 10  
#define SERVO_PIN_3 11 
//#define SERVO_PIN_4 12 
//#define SERVO_PIN_5 13 

int servoPinky,servoMiddle,servoIndex,servoThumb,servoRing;

int c;
char mes;
String myString = "";
String myStringRec;
int stringCounter = 0;
bool stringCounterStart = false;
String myRevivedString;
int stringLength = 6;

// ** Khai báo các servo được dùng theo cú pháp  " Servo + <tên_mình_đặt>; " ***
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;
//Servo Servo_4;
//Servo Servo_5;


void setup()
 {
      
      Serial.begin(9600);
      Servo_1.attach(SERVO_PIN_1); // Config servo với chân tín hiệu
      Servo_2.attach(SERVO_PIN_2);
      Servo_3.attach(SERVO_PIN_3);
//      Servo_4.attach(SERVO_PIN_4);
//      Servo_5.attach(SERVO_PIN_5);
      
      Servo_1.write(0);
      Servo_2.write(0);
      Servo_3.write(0);

 }

// **** Phần code mình chạy *****
void loop()
 {
  while(Serial.available()){
  
    myString = Serial.readString();

    int index_thumb = myString.indexOf('.');
    int index_index = myString.indexOf('^');
    int index_Pinky = myString.indexOf('&');
    String servoThumb_str = myString.substring(index_thumb - 1,index_thumb);
    String servoIndex_str = myString.substring(index_index - 1,index_index);
    String servoPinky_str = myString.substring(index_Pinky - 1,index_Pinky);
    servoThumb = servoThumb_str.toInt();
    servoIndex = servoIndex_str.toInt();
    servoPinky = servoPinky_str.toInt();
    Serial.println("---- Start-----");
    Serial.println(servoThumb);
    Serial.println(servoIndex);
    Serial.println(servoPinky);
    Serial.println("----End-----");
    
    
    if (servoThumb == 1){ Servo_1.write(100);}else{Servo_1.write(0);}
    if (servoIndex == 1){ Servo_2.write(140);}else{Servo_2.write(20);}
    if (servoPinky == 1){ Servo_3.write(130);}else{Servo_3.write(0);}
    delay(2000);
    myString = "";
  
  }

  
 }//loop

 
