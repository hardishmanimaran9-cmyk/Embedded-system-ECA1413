
int leds[] = {2, 3, 4, 5, 6, 7};

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Turn ON LEDs one by one
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
  }

  // Turn ON LEDs in reverse order
  for (int i = 5; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
  }
}
