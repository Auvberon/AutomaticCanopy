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

void irSetup(){
  pinMode(9, INPUT);
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
  irSetup();
  Serial.begin(9600);
  Wire.begin();
  pinMode(5, OUTPUT); //error LIS
  pinMode(7, OUTPUT); //error Time, Servo
}

void loop() 
{ 
  errorCorrection();
  Serial.println(getLightInstensity());
  Serial.println(RainModule());
  if( RainModule() == 0 && getLightInstensity() < 1000){
    servo.write(130);  
  }
  else{
    servo.write(0);  
  }
  loggingFile();
  
}

void errorCorrection(){
  int sensorState = digitalRead(9);
  if (sensorState == LOW && servo.read() == 90){ //IR baca, tapi servo buka
    Serial.println("Tedeteksi tapi buka");
    digitalWrite(7, HIGH);
  }
  else if (sensorState == HIGH && servo.read() == 0){
    Serial.println("Tidak terdeteksi tapi nutup");
    digitalWrite(7, HIGH);
  }
  else{
    digitalWrite(7, LOW);
  }
  if(getLightInstensity() == -2 || getLightInstensity() == -1){
    digitalWrite(5, HIGH);  
  }
  else{
    digitalWrite(5, LOW);  
  }
  delay(500);
}

int loggingFile(){
  myFile = SD.open("logging.txt", FILE_WRITE);
  if (myFile){       
    myFile.print(getLightInstensity());
    myFile.print(",");    
    myFile.println(RainModule());
    myFile.close(); // close the file
  }
  //if the file didn't open, print an error:
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
