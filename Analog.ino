#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int input = 0; //analog input
int analog_pin = 5;
int motor_speed = 0; //speed you want the motor to turn

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //reads analog input
  input = analogRead(analog_pin);
  Serial.print("This is your input: ");
  Serial.println(input);
  
  motor_speed= input / (1023.0 / 20.0);
  motor_speed+= 80;
  
  setSpeed(motor_speed);
  Serial.print("This is your speed: ");
  Serial.println(motor_speed);
  delay(1000);
}


//set motor speed to _speed
void setSpeed(int _speed){
  Serial.print("setting speed to ");
  Serial.println(_speed);
  myservo.write(_speed);
}

