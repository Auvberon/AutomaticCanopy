#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

BH1750 lightMeter;
Servo servo;
File myFile;

void loggingSetup(){
  if (SD.begin()){
    Serial.println("SD card is ready to use.");
  } 
  else{
   Serial.println("SD card initialization failed");
   return;
  }
}
  
void ServoSetup(){
  servo.attach(3);
  servo.write(0);
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
  loggingSetup();
  Serial.begin(9600);
  Wire.begin();
  int menu = 0;
  pinMode(2, OUTPUT); //error LIS
  pinMode(4, OUTPUT); //error Time, Servo
}

void loop() 
{ 
  Serial.println(getLightInstensity());
  Serial.println(RainModule());
  if(getLightInstensity() < 5 && RainModule() == 0){
    servo.write(130);  
  }
  else{
    servo.write(0);  
  }
  loggingFile();
  
}

int loggingFile(){
  myFile = SD.open("logging.txt", FILE_WRITE);
  if (myFile){       
    myFile.print(getLightInstensity());
    myFile.print(",");    
    myFile.println(RainModule());
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening logging.txt");
  }
}

int RainModule(){ 
  const int capteur_D = 0;
  const int capteur_A = A0;

  pinMode(capteur_D, INPUT); 
  
  if(digitalRead(capteur_D) == LOW) 
  {
    Serial.println("Digital value : wet"); 
    delay(1); 
    return 1;
  }
  else
  {
    Serial.println("Digital value : dry");
    delay(1); 
    return 0;
  } 
}

float getLightInstensity(){  
  float lux = lightMeter.readLightLevel(); //baca dari lightsensor
  return lux;
}
