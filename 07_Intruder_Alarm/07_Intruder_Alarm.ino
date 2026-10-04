// IUBPC Robotics Challenge - Card 7: Intruder Alarm
// Board: Arduino Uno

bool alarmOn = false;

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
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (readCm() < 15) alarmOn = true;
  if (digitalRead(2) == LOW) alarmOn = false;

  if (alarmOn) {
    digitalWrite(13, HIGH); tone(8, 1000); delay(150);
    digitalWrite(13, LOW);  noTone(8);     delay(150);
  } else {
    digitalWrite(13, LOW);
    noTone(8);
  }
}
