#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "credentials.h"

int PWMA = 5; //Right side
int PWMB = 4; //Left side
int DA = 0; //Right reverse
int DB = 2; //Left reverse
void setup() {
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, server, 80);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);
}

void driveMotor(int enableSpeedPin, int input1Pin, int input2Pin, int speedAndDirection)
{
  bool forward = speedAndDirection > 0;

  analogWrite(enableSpeedPin, speedAndDirection == 0 ? 0 : map(abs(speedAndDirection), 0, 100, 0, 1024));
  //digitalWrite(enableSpeedPin, speedAndDirection == 0 ? 0 : 1);
  digitalWrite(input1Pin, speedAndDirection == 0 ? 0 : forward);
  digitalWrite(input2Pin, speedAndDirection == 0 ? 0 : !forward);

  // TODO: Implement break
}

BLYNK_WRITE(V0) {
  driveMotor(DA, PWMA, PWMB, param.asInt());
}

void loop() {
  Blynk.run();
}

// Handling Joystick data 
BLYNK_WRITE(V1){ 
int x = param[0].asInt(); 
int y = param[1].asInt();  
if(x==-1 && y==-1){             //Backward and Left     
     digitalWrite(PWMA, LOW); 
     digitalWrite(DA, LOW); 
     
     digitalWrite(PWMB, HIGH); 
     digitalWrite(DB, HIGH); 
}else if(x==-1 && y==0){        //Left Turn 
     digitalWrite(PWMA, 450); 
     digitalWrite(DA, HIGH); 
    
     digitalWrite(PWMB, 450); 
     digitalWrite(DB, LOW); 
}else if(x==-1 && y==1){        //Forward and Left     
     digitalWrite(PWMA, LOW); 
     digitalWrite(DA, LOW); 
    
     digitalWrite(PWMB, HIGH); 
     digitalWrite(DB, LOW); 
}else if(x==0 && y==-1){        //Backward     
     digitalWrite(PWMA, HIGH); 
     digitalWrite(DA, HIGH); 
     
     digitalWrite(PWMB, HIGH); 
     digitalWrite(DB, HIGH);
}else if(x==0 && y==0){        //Stay 
     digitalWrite(PWMA, LOW); 
     digitalWrite(DA, LOW); 
     
     digitalWrite(PWMB, LOW); 
     digitalWrite(DB, LOW); 
}else if(x==0 && y==1){        //Forward 
     digitalWrite(PWMA, HIGH); 
     digitalWrite(DA, LOW); 
    
     digitalWrite(PWMB, HIGH); 
     digitalWrite(DB, LOW); 
}else if(x==1 && y==-1){        //Backward and Right     
     digitalWrite(PWMA, HIGH); 
     digitalWrite(DA, HIGH); 
     
     digitalWrite(PWMB, LOW); 
     digitalWrite(DB, LOW); 
}else if(x==1 && y==0){        //Right turn 
     digitalWrite(PWMA, 450); 
     digitalWrite(DA, LOW); 
     
     digitalWrite(PWMB, 450); 
     digitalWrite(DB, HIGH); 
}else if(x==1 && y==1){        //Forward and Right 
     digitalWrite(PWMA, HIGH); 
     digitalWrite(DA, LOW); 
     
     digitalWrite(PWMB, LOW); 
     digitalWrite(DB, LOW);
 } 
} 
