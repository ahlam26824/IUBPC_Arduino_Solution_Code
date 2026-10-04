// IUBPC Robotics Challenge - Card 4: Parking Sensor
// Board: Arduino Uno

long readCm() {
  digitalWrite(7, LOW);  delayMicroseconds(2);
  digitalWrite(7, HIGH); delayMicroseconds(10);
  digitalWrite(7, LOW);
  long t = pulseIn(6, HIGH, 30000);
  if (t == 0) return 999;
  return t * 0.034 / 2;
}

void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  long d = readCm();
  if (d > 30) {
    noTone(8);
    delay(100);
  } else {
    tone(8, 1000, 50);
    delay(map(constrain(d, 2, 30), 2, 30, 50, 500));
  }
}
