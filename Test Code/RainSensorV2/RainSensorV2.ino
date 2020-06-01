#include <Servo.h>

Servo servo;

const int capteur_D = 4;
const int capteur_A = A0;

int val_analogique;

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  servo.attach(8);
  servo.write(0); //nutup
}

void loop()
{
if(digitalRead(capteur_D) == LOW) 
  {
    Serial.println("Digital value : wet"); 
    delay(10); 
    servo.write(0); //nutup
    delay(10000); 
  }
else
  {
    Serial.println("Digital value : dry");
    delay(10); 
    servo.write(80); //buka
  }
val_analogique=analogRead(capteur_A); 
 Serial.print("Analog value : ");
 Serial.println(val_analogique); 
 Serial.println("");
  delay(1000);
}
