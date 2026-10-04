// IUBPC Robotics Challenge - Card 3: SOS Signal
// Board: Arduino Uno

void blinkMs(int on) {
  digitalWrite(13, HIGH); delay(on);
  digitalWrite(13, LOW);  delay(200);
}

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) blinkMs(200);   // S
  for (int i = 0; i < 3; i++) blinkMs(600);   // O
  for (int i = 0; i < 3; i++) blinkMs(200);   // S
  delay(2000);
}
