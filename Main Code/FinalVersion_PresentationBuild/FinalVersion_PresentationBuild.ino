#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

#define capteur_D  0
#define capteur_A  A0

BH1750 lightMeter;
Servo servo;
//File myFile;

void errorSetup(){
  SD.begin();
  pinMode(5, OUTPUT); //error LIS
  pinMode(7, OUTPUT); //error Time, Servo
}

void irSetup(){
  pinMode(9, INPUT);
}
  
void ServoSetup(){
  servo.attach(3);
  servo.write(130);
  delay(2000);
}

void lisSetup(){
  lightMeter.begin();
}

void setup() 
{
  lisSetup();
  ServoSetup();
  errorSetup();
  irSetup();
  Serial.begin(9600);
  Wire.begin();

}

void loop() 
{ 
  errorCorrection();
  if( RainModule() == 0 && getLightInstensity() < 1000){
    servo.write(0);  
  }
  else{
    servo.write(130);  
  }
}

void errorCorrection(){
 myFile = SD.open("logging.txt", FILE_WRITE);

 int sensorState = digitalRead(9);
 if (sensorState == HIGH && servo.read() == 130){ //IR baca, tapi servo buka
   if(getLightInstensity() == -2 || getLightInstensity() == -1){
       digitalWrite(5, HIGH);
       digitalWrite(7, HIGH);        
       myFile.print(getLightInstensity());
       myFile.print(F("||"));    
       myFile.print(RainModule());
       myFile.print(F("||"));
       myFile.println(F("er-04"));
       myFile.close(); // close the file
     }
     else{
       digitalWrite(7, HIGH);     
       digitalWrite(5, LOW);    
       myFile.print(getLightInstensity());
       myFile.print(F("||"));    
       myFile.print(RainModule());
       myFile.print(F("||"));
       myFile.println(F("er-01"));
       myFile.close(); // close the file
     }
 }
 else if (sensorState == LOW && servo.read() == 0){
   if(getLightInstensity() == -2 || getLightInstensity() == -1){
       digitalWrite(5, HIGH);
       digitalWrite(7, HIGH);        
       myFile.print(getLightInstensity());
       myFile.print(F("||"));    
       myFile.print(RainModule());
       myFile.print(F("||"));
       myFile.println(F("er-05"));
       myFile.close(); // close the file
     }
     else{
       digitalWrite(7, HIGH);  
       digitalWrite(5, LOW);   
       myFile.print(getLightInstensity());
       myFile.print(F("||"));    
       myFile.print(RainModule());
       myFile.print(F("||"));
       myFile.println(F("er-02"));
       myFile.close(); // close the file
     }
 }
 else if(getLightInstensity() == -2 || getLightInstensity() == -1){
   digitalWrite(5, HIGH);  
   digitalWrite(7, LOW);     
   myFile.print(getLightInstensity());
   myFile.print(F("||"));    
   myFile.print(RainModule());
   myFile.print(F("||"));
   myFile.println(F("er-03"));
   myFile.close(); // close the file
 }
 else{
   digitalWrite(5, LOW);  
   digitalWrite(7, LOW);
 }
 delay(500);
}

int RainModule(){ 
//  const int capteur_D = 0;
//  const int capteur_A = A0;

  pinMode(capteur_D, INPUT); 
  
  if(digitalRead(capteur_D) == LOW) 
  {
    delay(1); 
    return 1;
  }
  else
  {
    delay(1); 
    return 0;
  } 
}

float getLightInstensity(){  
  float lux = lightMeter.readLightLevel(); //baca dari lightsensor
  return lux;
}
