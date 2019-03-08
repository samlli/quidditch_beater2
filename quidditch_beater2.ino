#include <Servo.h>

#define robot_code 'b'
#define Rx 17
#define Tx 16
#define button 5
#define tx_LED 2
#define rx_LED 3
#define line_sensor3 14
#define line_sensor1 15
#define line_sensor2 19

Servo servoRight;
Servo servoLeft;

void setup() {
  pinMode(button, INPUT);
  pinMode(tx_LED, OUTPUT);
  pinMode(rx_LED, OUTPUT);

  Serial.begin(9600);
  Serial2.begin(9600);

  servoRight.attach(12);
  servoLeft.attach(11);
  
  delay(500);
}

void loop() {
  int qti1 = RCTime(line_sensor1);  //left
  int qti2 = RCTime(line_sensor2);  //middle
  int qti3 = RCTime(line_sensor3);  //right

  if(qti1<150 and qti2>150 and qti3<150){ //white black white
    forwards();
  }

  if(qti1>150 and qti2>150 and qti3>150){ //black black black
    stopMoving(); //do whatever
    delay(1500);
    forwards(); //move past line
    delay(200);
  }

  if(qti1<150 and qti2<150 and qti3<150){ //white white white
    forwards();
  }

  if(qti1<150 and qti2<150 and qti3>150){ //white white black
    turnRight();
    Serial.println("turn right");
  }

  if(qti1>150 and qti2<150 and qti3<150){ //black white white
    turnLeft();
    Serial.println("turn left");
  }
  
  if(qti1<150 and qti2>150 and qti3>150){ //white black black
    turnRight();
    Serial.println("turn right");
  }

  if(qti1>150 and qti2>150 and qti3<150){ //black black white
    turnLeft();
    Serial.println("turn left");
  }

  Serial.println(toString(qti1)+" "+toString(qti2)+" "+toString(qti3));

//  char buf[32];  //memory for string formatting
//  
//  if(digitalRead(button)){  //button pressed
//    char outgoing = robot_code;
//    Serial2.print(outgoing); //send code
//
//    sprintf(buf, "sent signal %c", robot_code);  //string formatting
//    Serial.println(buf);  //print to screen
//
//    blinkLED(tx_LED);
//  }
//
//  if(Serial2.available()){  //signal received
//    char incoming = Serial2.read();
//    if(incoming!=robot_code){
//      sprintf(buf, "received signal %c", incoming);
//      Serial.println(buf);
//
//      blinkLED(rx_LED);
//    }
//  }
}

long RCTime(int sensor){  //reads value from QTI sensor
  long duration=0;
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, HIGH);
  delay(1);
  pinMode(sensor, INPUT);
  digitalWrite(sensor, LOW);

  while(digitalRead(sensor)){ //wait for pin to go low
    duration++;
  }
  return duration;  //return duration of pulse
}

void turnLeft(){
  servoLeft.writeMicroseconds(1300);//
  servoRight.writeMicroseconds(1300);
}

void turnRight(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);//
}

void stopMoving(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void forwards(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}

void blinkLED(int pin){
  digitalWrite(pin, HIGH);
  delay(1500);
  digitalWrite(pin, LOW);
}

String toString(int qti_val){
  if(qti_val>150){
    return "B";
  }
  return "W";
}

