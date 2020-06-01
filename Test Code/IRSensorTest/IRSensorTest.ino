const int pinIR = 9;
const int pinLed = 7;
void setup() {
  Serial.begin(9600);
  pinMode(pinIR, INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.println("Deteksi Sensor IR");
  delay(3000);
}
void loop() {
  int sensorState = digitalRead(pinIR);
  if (sensorState == LOW) {
    Serial.println("Tedeteksi");
    digitalWrite(pinLed, HIGH);
  } else {
    Serial.println("Tidak terdeteksi");
    digitalWrite(pinLed, LOW);
  }
  delay(500);
}
