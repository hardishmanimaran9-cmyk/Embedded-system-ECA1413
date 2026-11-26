#define GAS_PIN A0
#define TRIG_PIN 9
#define ECHO_PIN 8
#define PIR_PIN 2
#define LED_PIN 12
#define BUZZER_PIN 10

int gasValue;
int motion;
long duration;
float distance;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("SMART GAS AND SECURITY SYSTEM");
  Serial.println("--------------------------------");
}

void loop() {
  // Read gas sensor
  gasValue = analogRead(GAS_PIN);

  // Read PIR motion sensor
  motion = digitalRead(PIR_PIN);

  // Measure distance using HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.0343 / 2;
  }

  // Display sensor readings
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  Serial.print("Motion: ");
  Serial.println(motion ? "DETECTED" : "NOT DETECTED");

  Serial.print("Distance: ");

  if (distance < 0) {
    Serial.println("No Echo");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Alert conditions
  bool gasAlert = gasValue > 400;
  bool motionAlert = motion == HIGH;
  bool distanceAlert = distance > 0 && distance < 20;

  if (gasAlert || motionAlert || distanceAlert) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("WARNING: ALERT DETECTED!");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("SYSTEM SAFE");
  }

  Serial.println("------------------------------");
  delay(1000);
}
