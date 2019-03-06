#include <Servo.h>

#define tx_code 'b'
#define Rx 17
#define Tx 16
#define button 5
#define tx_led 2
#define rx_led 3
#define line_sensor1 14
#define line_sensor2 15
#define line_sensor3 19

Servo servoRight;
Servo servoLeft;

void setup() {
  pinMode(button, INPUT);
  pinMode(tx_led, OUTPUT);
  pinMode(rx_led, OUTPUT);

  Serial.begin(9600);
  Serial2.begin(9600);

  ServoRight.attach(12);
  ServoLeft.attach(11);
  delay(500);
}

void loop() {
  int qti1 = RCTime(line_sensor1);
  int qti2 = RCTime(line_sensor2);
  int qti3 = RCTime(line_sensor3);

  if(qti1>100 and qti2<100 and qti3>100){ //white black white
    forwards();
  }

  if(qti1<100 and qti2<100 and qti3<100){ //black black black
    stopMoving(); //do whatever
    delay(1000);
    forwards();//get off the line
    delay(200);
  }

  if(qti1>100 and qti2>100 and qti3<100){ //white white black
    turnLeft();
  }

  if(qti1<100 and qti2>100 and qti3>100){ //black white white
    turnRight();
  }

  Serial.println(toString(qti1)+" "+toString(qti2)+" "+toString(qti3));
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
  servoLeft.writeMicroseconds(1650);
  servoRight.writeMicroseconds(1300);
  delay(100);
}

void turnRight(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1350);
  delay(100);  
}

void stopMoving(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(100);
}

void forwards(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(100);
}

String toString(int qti_val){
  if(qti_val>100){
    return "B";
  }
  return "W"
}

