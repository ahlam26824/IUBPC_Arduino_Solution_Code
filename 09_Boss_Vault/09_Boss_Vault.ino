// IUBPC Robotics Challenge - BOSS: The Vault
// Board: Arduino Uno (Tinkercad)
#include <Servo.h>

const int PIN_BTN = 2, PIN_TRIG = 7, PIN_ECHO = 6, PIN_BUZ = 8;
const int PIN_SERVO = 9, PIN_GREEN = 12, PIN_RED = 13;

const unsigned long DEBOUNCE = 30, SHORT_MAX = 300, LONG_MIN = 600;
const unsigned long GAP_MAX = 2000, OPEN_MS = 5000, LOCKOUT_MS = 10000;
const int WAKE_CM = 20, MAX_FAILS = 3;

enum State { LOCKED, OPEN, LOCKOUT };
State state = LOCKED;
Servo lockServo;

const char secret[4] = {'S', 'S', 'L', 'S'};
char entry[4];
int count = 0, fails = 0, beepStage = 0;

bool handNear = false, pressing = false;
bool rawLast = false, stable = false;
unsigned long lastChange = 0, pressStart = 0, lastRelease = 0;
unsigned long stateStart = 0, lastProx = 0, lastBlink = 0, lastSecPrint = 0;

long readCm() {
  digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  long t = pulseIn(PIN_ECHO, HIGH, 30000);
  if (t == 0) return 999;
  return t * 0.034 / 2;
}

void logEvent(const char *msg) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms] ");
  Serial.println(msg);
}

void setLocked() {
  state = LOCKED;
  lockServo.write(0);
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  count = 0;
}

void checkEntry(unsigned long now) {
  bool ok = true;
  for (int i = 0; i < 4; i++) if (entry[i] != secret[i]) ok = false;
  count = 0;
  if (ok) {
    state = OPEN;
    stateStart = now;
    beepStage = 0;
    fails = 0;
    lockServo.write(90);
    digitalWrite(PIN_GREEN, HIGH);
    digitalWrite(PIN_RED, LOW);
    logEvent("UNLOCKED");
  } else {
    fails++;
    tone(PIN_BUZ, 200, 800);
    logEvent("WRONG KNOCK");
    if (fails >= MAX_FAILS) {
      state = LOCKOUT;
      stateStart = now;
      lastBlink = now;
      lastSecPrint = now - 1000;   // print countdown immediately
      fails = 0;
      digitalWrite(PIN_RED, HIGH);
      digitalWrite(PIN_GREEN, LOW);
      logEvent("LOCKOUT START");
    }
  }
}

void onPress(unsigned long now) {
  if (state != LOCKED || !handNear) return;   // ignored
  pressing = true;
  pressStart = now;
}

void onRelease(unsigned long now) {
  if (!pressing) return;
  pressing = false;
  unsigned long d = now - pressStart;
  char sym = (d <= SHORT_MAX) ? 'S' : (d >= LONG_MIN ? 'L' : 'X');
  entry[count++] = sym;
  lastRelease = now;
  if (sym == 'S') logEvent("press: SHORT");
  else if (sym == 'L') logEvent("press: LONG");
  else logEvent("press: INVALID");
  if (count == 4) checkEntry(now);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZ, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  lockServo.attach(PIN_SERVO);
  setLocked();
  logEvent("VAULT READY");
}

void loop() {
  unsigned long now = millis();

  // proximity check every 100 ms
  if (now - lastProx >= 100) {
    lastProx = now;
    handNear = (readCm() <= WAKE_CM);
  }

  // debounced button
  bool raw = (digitalRead(PIN_BTN) == LOW);
  if (raw != rawLast) { lastChange = now; rawLast = raw; }
  if (now - lastChange >= DEBOUNCE && raw != stable) {
    stable = raw;
    if (stable) onPress(now); else onRelease(now);
  }

  // entry timeout: more than 2 s between presses cancels the attempt
  if (state == LOCKED && count > 0 && !pressing && now - lastRelease > GAP_MAX) {
    count = 0;
    logEvent("entry cleared (timeout)");
  }

  if (state == OPEN) {
    unsigned long e = now - stateStart;
    if (beepStage == 0) { tone(PIN_BUZ, 880, 150); beepStage = 1; }
    else if (beepStage == 1 && e >= 250) { tone(PIN_BUZ, 1320, 150); beepStage = 2; }
    if (e >= OPEN_MS) { setLocked(); logEvent("RELOCKED"); }
  }

  if (state == LOCKOUT) {
    unsigned long e = now - stateStart;
    if (e >= LOCKOUT_MS) {
      setLocked();
      logEvent("LOCKOUT END");
    } else {
      if (now - lastBlink >= 100) {
        lastBlink = now;
        digitalWrite(PIN_RED, !digitalRead(PIN_RED));
      }
      if (now - lastSecPrint >= 1000) {
        lastSecPrint = now;
        Serial.print("Lockout: ");
        Serial.print((LOCKOUT_MS - e + 999) / 1000);
        Serial.println(" s left");
      }
    }
  }
}
