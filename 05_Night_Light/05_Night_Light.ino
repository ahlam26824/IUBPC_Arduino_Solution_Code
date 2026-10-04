// IUBPC Robotics Challenge - Card 5: Night Light
// Board: Arduino Uno

// Threshold 500 may need adjusting in the simulator
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);              // handy for finding your threshold
  if (v < 500) digitalWrite(13, HIGH);   // dark
  else digitalWrite(13, LOW);            // bright
  delay(50);
}
