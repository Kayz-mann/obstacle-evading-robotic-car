//motor A connected between A01 and A02
//motor B connected between B01 and B02
#include <HCSR04.h>
UltraSonicDistanceSensor ultrasonic(15,16);
float distance;


int STBY = 10; //standby


// defines variables
long duration;
//int distance;

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
  
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup(){

Serial.begin(9600); // Starts the serial 

pinMode(STBY, OUTPUT);

pinMode(PWMA, OUTPUT);
pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);

pinMode(PWMB, OUTPUT);
pinMode(BIN1, OUTPUT);
pinMode(BIN2, OUTPUT);
}

void loop(){
distance = ultrasonic.measureDistanceCm();
Serial.println(distance);

if(distance > -1 && distance < 45){
  stop();
   move(1, 2055, 1); //motor 1, full speed, left

 
}else{
   stop();
  delay(1000);
  move(1, 128, 0); //motor 1, half speed, right
  move(2, 128, 0); //motor 2, half speed, right
 
}

}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

digitalWrite(STBY, HIGH); //disable standby

boolean inPin1 = LOW;
boolean inPin2 = HIGH;

if(direction == 1){
inPin1 = HIGH;
inPin2 = LOW;
}

if(motor == 1){
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}else{
digitalWrite(BIN1, inPin1);
digitalWrite(BIN2, inPin2);
analogWrite(PWMB, speed);
}
}

void stop(){
//enable standby
digitalWrite(STBY, LOW);
}
