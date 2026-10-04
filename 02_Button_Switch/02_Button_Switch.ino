// IUBPC Robotics Challenge - Card 2: Button Switch
// Board: Arduino Uno

void setup() {
  pinMode(2, INPUT_PULLUP);   // pressed = LOW
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(2) == LOW) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
}
