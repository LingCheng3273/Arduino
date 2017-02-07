#include <Servo.h>

Servo myservo;  // create servo object to control a servo

String command;

 int sp = 0; //speed you want the motor to turn
 int encoder0PinA = 5;
 int encoder0PinB = 6;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;
 int motorPin = 9;
 int stepsPerRev= 1024;


 void setup() { 
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   Serial.begin (9600);   // opens serial port, sets data rate to 9600 bps
   myservo.attach(motorPin);  // attaches the servo on pin 9 to the servo object
 } 

 void loop() {

 // send data only when you receive data:
  if (Serial.available() > 0) {
    followCommand();
  }
  //setSteps();
  Serial.println(getRevPerSec());
 }
 
 //set motor speed to _speed
void setSpeed(int _speed){
  Serial.println("setting speed to ");
  Serial.print(_speed);
  myservo.write(_speed);
}

long getRevPerSec(){
   int milisec=1000;
   int startPos= encoder0Pos;
   unsigned long startTime=millis();
   
   while(millis()-startTime < milisec){
      setSteps();
   }
   Serial.println("");
   Serial.print("Initial pos: ");
   Serial.println(startPos);
   Serial.print("End pos: ");
   Serial.println( encoder0Pos);
   return (encoder0Pos- startPos)/ stepsPerRev;
}

void setSteps(){
  n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
     //Serial.print (encoder0Pos);
     //Serial.print ("/");
   } 
   encoder0PinALast = n;
}

void followCommand(){
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

