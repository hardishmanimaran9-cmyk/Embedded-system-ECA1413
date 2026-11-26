void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');

    if (data == "TEST") {
      Serial.println("PASS");
    }
  }
}
