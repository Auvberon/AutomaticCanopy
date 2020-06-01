#include <Wire.h>
#include <BH1750.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void TimeSetup(){
  DS3231 rtc(SDA, SCL);
  rtc.begin(); 
  rtc.setTime(18, 59, 50); //default time
}

void LCDSetup(){
  lcd.init();
  lcd.backlight();
}

void setup() {
  Serial.begin(9600);
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
        if(Rain == 1){ //ketika gelap && gk hujan = buka
            Serial.print("Buka");
        }
        else{
            Serial.print("Nutup");
        }
    }
     else{ //else tutup
        Serial.print("Nutup");
    }
}

int RTC(){
  DS3231 rtc(SDA, SCL);
  
  int P1=6; // Button SET MENU'
  int P2=7; // Button +
  int P3=8; // Button -
  
  int jam;
  int menit;
  int menu = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time : ");
  lcd.setCursor(0,1);
  lcd.print(rtc.getTimeStr());
  delay(200);
 
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
  const int capteur_A = A0;

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
