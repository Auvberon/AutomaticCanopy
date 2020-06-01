#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DS3231 rtc(SDA, SCL);
BH1750 lightMeter;
Servo servo;

int menu = 0;
int jam;
int menit;
  
void ServoSetup(){
  servo.attach(3);
  servo.write(0);
  delay(2000);
}

void timeSetup(){
  int P1=6; // Button SET MENU'
  int P2=7; // Button +
  int P3=8; // Button -
  
  lcd.init();
  lcd.backlight();

  pinMode(P1,INPUT);
  pinMode(P2,INPUT);
  pinMode(P3,INPUT);

  rtc.begin();
  rtc.setTime(0,0,0);
}

void lisSetup(){
  lightMeter.begin();
}

void setup() 
{
  timeSetup();
  lisSetup();
  ServoSetup();
  Serial.begin(9600);
  Wire.begin();
  int menu = 0;
}

void loop() 
{ 
  timeSet();
  Serial.println(timeConversion());
  Serial.println(getLightInstensity());
  Serial.println(RainModule());
  
  if(timeConversion() > 6 && timeConversion() < 19){
    if(getLightInstensity() < 15000 && RainModule() == 0){
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

int RainModule(){ 
  const int capteur_D = 5;
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

int timeConversion(){
  String stringWaktu = rtc.getTimeStr(); //ambil waktu dari rtc
  String convertWaktu = stringWaktu.substring(0,2); //ambil string jam
  int IntJam = convertWaktu.toInt();

  return IntJam;
}

void timeSet(){
  int P1=6; // Button SET MENU'
  int P2=7; // Button +
  int P3=8; // Button -
  
  if(digitalRead(P1) == HIGH){
    menu = menu + 1;
  }
  
 if(menu == 0 ){ //for displaying time
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current Time : ");
    lcd.setCursor(0,1);
    lcd.print(rtc.getTimeStr());
    delay(200);
  }
 if(menu == 1){ //for setting hour
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Hour : ");
  
    if(digitalRead(P2) == HIGH){
      if(jam == 23){
        jam = 0;
        }
      else{
        jam = jam + 1;  
        }
      }
    if(digitalRead(P3) == HIGH){
       if(jam == 0){
        jam = 23;
        }
       else{
        jam = jam - 1;
        }
      }
  
     lcd.setCursor(0,1);
     lcd.print(jam);
     delay(200);
  }
 if(menu == 2 ){ //for setting minute
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Minute : ");
  
    if(digitalRead(P2) == HIGH){
      if(menit == 60){
        menit = 0;
        }
      else{
        menit = menit + 1;  
        }
      }
    if(digitalRead(P3) == HIGH){
       if(menit == 0){
        menit = 60;
        }
       else{
        menit = menit - 1;
        }
      }
  
     lcd.setCursor(0,1);
     lcd.print(menit);
     delay(200);
  }
  if(menu == 3 ){ //saving the time
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Saving.");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("Saving..");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("Saving...");
    delay(500);
    rtc.setTime(jam, menit,0);
    delay(777);
    menu = 0;
  }
}
