// IUBPC Robotics Challenge - Card 6: Smart Door
// Board: Arduino Uno

#include <Servo.h>

Servo door;

void setup() {
  pinMode(2, INPUT_PULLUP);
  door.attach(9);
  door.write(0);
}

void loop() {
  if (digitalRead(2) == LOW) {
    door.write(90);
    delay(3000);
    door.write(0);
  }
}
