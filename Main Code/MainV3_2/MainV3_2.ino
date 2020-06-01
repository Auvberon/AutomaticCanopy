#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>
#include <DS3231.h>

Servo servo;

void TimeSetup(){
  DS3231 rtc(SDA, SCL);
  rtc.begin(); 
  rtc.setTime(15, 59, 50);
}

void ServoSetup(){
  servo.attach(8);
  servo.write(0);
  delay(2000);
}


void setup() {
  Serial.begin(9600);
  ServoSetup();
  TimeSetup();
}

void loop() {
  int Jam = RTC();
  float Lux = LIS();
  int Rain = RainModule();
  
  Serial.println(Jam);
  Serial.println(Lux);
  
  delay (1000); //delay  

  if(Jam > 6 && Jam < 19){ //Ketika siang buka
        if(Lux < 15000 && Rain == 1){ //ketika gelap && gk hujan = buka
            Serbo(90);
        }
        else{
            Serbo(0); 
        }
    }
     else{ //else tutup
        Serbo(0);
    }
}

int RTC(){
  DS3231 rtc(SDA, SCL);
  String stringWaktu = rtc.getTimeStr(); //ambil waktu dari rtc
  String convertWaktu = stringWaktu.substring(0,2); //ambil string jam
  int IntJam = convertWaktu.toInt();

  return IntJam;
}

float LIS(){
  BH1750 lightMeter;
  Wire.begin();
  lightMeter.begin();
  
  float lux = lightMeter.readLightLevel(); //baca dari lightsensor
  return lux;
}

int RainModule(){
  const int capteur_D = 4;
//  const int capteur_A = A0;

  pinMode(capteur_D, INPUT);  
  if(digitalRead(capteur_D) == LOW) 
    {
      Serial.println("Digital value : wet"); 
      delay(1); 
      return 0;
    }
  else
    {
      Serial.println("Digital value : dry");
      delay(1); 
      return 1;
    } 
}

void Serbo(int x){
  servo.write(x);
}
