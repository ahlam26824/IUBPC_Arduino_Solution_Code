// IUBPC Robotics Challenge - Card 8: Reaction Game
// Board: Arduino Uno

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  randomSeed(analogRead(A0));
}

void loop() {
  digitalWrite(13, LOW);
  delay(random(2000, 5001));      // random 2-5 s wait
  digitalWrite(13, HIGH);
  unsigned long start = millis();
  while (digitalRead(2) == HIGH) { }   // wait for press
  Serial.print("Reaction time: ");
  Serial.print(millis() - start);
  Serial.println(" ms");
  digitalWrite(13, LOW);
  delay(2000);
}
