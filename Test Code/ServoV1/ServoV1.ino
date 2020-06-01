#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(3);
  servo.write(0);
  delay(500);
}

void loop() {
  servo.write(0);
  delay(500);
  servo.write(45);
  delay(500);
  servo.write(90);
  delay(500);
}
