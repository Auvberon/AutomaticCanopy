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

  String stringWaktu = rtc.getTimeStr(); //ambil waktu dari rtc
  String convertWaktu = stringWaktu.substring(0,2); //ambil string jam
  int IntJam = convertWaktu.toInt();
  Serial.println(IntJam);
  Serial.println(lux);
  
  delay (1000); //delay  

  if(IntJam > 6 && IntJam < 19 ){ //Ketika siang buka
        if(lux < 15000 && digitalRead(capteur_D) == HIGH){ //ketika gelap && gk hujan = buka
            Serial.println("Dry");
            servo.write(90);
        }
        else{
            servo.write(0); 
        }
    }
     else{ //else tutup
        servo.write(0); 
    }
}
