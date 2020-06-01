#include <DS3231.h>
#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>

//Constructor Rain Sensor
const int capteur_D = 4;
const int capteur_A = A0;

//RTC
DS3231 rtc(SDA, SCL);

//Light Intensity
BH1750 lightMeter;

//Servo
Servo servo;

void setup() {
  //Rain Sensor
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  
  Serial.begin(9600);
  
  //Setting Time for RTC
  rtc.begin(); 
  rtc.setTime(13, 59, 50);

  //Begin detecting light
  Wire.begin();
  lightMeter.begin();

  //Servo
  servo.attach(8);
  servo.write(0);
  delay(2000);
}

void loop() {
  float lux = lightMeter.readLightLevel(); //baca dari lightsensor
  int InputRTC, InputIntensity;
  String stringWaktu = rtc.getTimeStr(); //ambil waktu dari rtc
  String convertWaktu = stringWaktu.substring(0,2); //ambil string jam
  int IntJam = convertWaktu.toInt();
  Serial.println(IntJam);
  Serial.println(lux);
  
  delay (1000); //delay  

  InputRTC = RealTimeClock(IntJam);
  InputIntensity = IntensitasCahaya(lux); // hasil dari function = 1 atau 0
  //InputRain = RainSensor(capteur_D);

  // bagus 1, kering 1, pagi 1
  // silaau 0, basah 0, malam 0
  if(InputRTC == 1){ //Ketika terang buka
    if(InputIntensity == 0 && digitalRead(capteur_D) == HIGH){
        Serial.println("Dry");
        servo.write(90);
    }
    else{
        servo.write(0);
    }
    
  }
  else{
    servo.write(0);
  }


    
}

// function cahaya sensor
    int IntensitasCahaya(int cahaya)
    {
      int hasil = 0; // 0 tutup 1 buka
      if(cahaya < 15000){
        hasil = 1; // bagus
      }
      else{
        hasil = 0; // silaau
      }
    return cahaya;
    }

// function rtc
    int RealTimeClock(int waktu)
    {
      int hasil = 0; // 0 tutup 1 bukaa
      if(waktu > 6 && waktu < 19){
        hasil = 1; // siang
      }
      else{
        hasil = 0;  // malam
      }
    return hasil;
    }

// function rain
/*    int RainSensor(int air)
    {
      int hasil = 0; // 0 tutup 1 bukaa
      if(air == HIGH){
        hasil = 1;  // kering
      }
      else{
        hasil = 0;  // basah
      }
    return hasil;
    }

*/
