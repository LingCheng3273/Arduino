#include <Servo.h>

Servo myservo;  // create servo object to control a servo

String command;
int sp = 0; //speed you want the motor to turn
int encoderA= 5;
int encoderB= 6;
int encoder0Pos=0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    
    // read the incoming byte:
    command = Serial.readString();
    Serial.println("I received: "+ command);  
    command.trim();
    
    //Case for moving forward
    if(command.substring(0,1).equals("F") ){
      sp= 90 + command.substring(1).toInt();
      Serial.println("This is a forward command");
    }
    
    //Case for moving backwardss
    if(command.substring(0, 1).equals("R") ){
      sp= 90 - command.substring(1).toInt() ;
      Serial.println("This is a reverse command"); 
    }

    setSpeed(sp);
    
  }
}

//set motor speed to _speed
void setSpeed(int _speed){
  Serial.println("setting speed to "+ _speed);
  myservo.write(_speed);
}

