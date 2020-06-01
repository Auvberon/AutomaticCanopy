const int capteur_D = 0;
const int capteur_A = A0;

int val_analogique;

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
if(digitalRead(capteur_D) == LOW) 
  {
    Serial.println("Digital value : wet"); 
    delay(10); 
    digitalWrite(LED_BUILTIN, HIGH);
  }
else
  {
    Serial.println("Digital value : dry");
    delay(10); 
    digitalWrite(LED_BUILTIN, LOW);
  }
val_analogique=analogRead(capteur_A); 
 Serial.print("Analog value : ");
 Serial.println(val_analogique); 
 Serial.println("");
  delay(1000);
}
