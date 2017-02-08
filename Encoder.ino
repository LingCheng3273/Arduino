#include <Servo.h>
//red is 5V
Servo myservo;  // create servo object to control a servo

String command;

 int sp = 0; //speed you want the motor to turn
 int encoder0PinA = 11;
 int prevPulse = LOW;
 int motorPin = 9;
 int pulsePerRev= 50;
 int pulses;


 void setup() { 
   pinMode (encoder0PinA,INPUT);
   Serial.begin (9600);   // opens serial port, sets data rate to 9600 bps
   myservo.attach(motorPin);  // attaches the servo on pin 9 to the servo object
 } 

 void loop() {

 // send data only when you receive data:
  if (Serial.available() > 0) {
    followCommand();
  }
  countPulse();
  
  /*Serial.print("Pulse Per Sec: ");
  Serial.println(getPulsePerSec());*/
  //Serial.print("Pulse Per Min: ");
  /*Serial.println(getPulsePerMin());
  Serial.println("");*/
  /*Serial.print("RPM: ");
  Serial.println(getRPM());*/
  Serial.print("Revolutions: ");
  Serial.println(getRev());
  delay(500);
  
  /*Serial.print("Pulse: ");
  Serial.println(pulses);
  Serial.print("");*/
 }
 
 //set motor speed to _speed
void setSpeed(int _speed){
  Serial.println("setting speed to ");
  Serial.print(_speed);
  myservo.write(_speed);
}

int getPulse(){
  return digitalRead(encoder0PinA);
}

void countPulse(){
  int currentPulse = getPulse();
  if (prevPulse == LOW && currentPulse == HIGH){
    pulses++;
  }
  prevPulse= currentPulse;
}

int getPulsePerSec(){
  unsigned long startTime = micros();
  int startPulse = pulses;
  while (micros() - startTime < 1000000){
    countPulse();
  }
  return pulses - startPulse;
}
int getPulsePerMin(){
  return getPulsePerSec() * 60;
}

int getRPM(){
  unsigned long microsec=1000000;
  int initPulse= pulses;
  unsigned long startTime=micros();
   
   while(micros()-startTime < microsec){
      countPulse();
   }
   return ((pulses- initPulse)* 60)/pulsePerRev;
}

int getRev(){
  return pulses/ pulsePerRev;
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

unsigned long getRevPeriod(){
  int initialpulse = pulses;
  unsigned long initialtime = micros();
  while( pulses - initialpulse < pulsePerRev){
    countPulse();
  }
  return micros() - initialtime;
}

