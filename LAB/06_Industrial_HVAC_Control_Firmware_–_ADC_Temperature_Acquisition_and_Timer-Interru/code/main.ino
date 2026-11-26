const int tempPin = A0;
const int motorPin = 9;

float temperature;
int pwmValue;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);

  Serial.println("HVAC Control System");
  Serial.println("-------------------");
}

void loop() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  temperature = voltage * 100.0;

  if (temperature < 25.0) {
    pwmValue = 0;
  }
  else if (temperature < 30.0) {
    pwmValue = 100;
  }
  else if (temperature < 35.0) {
    pwmValue = 180;
  }
  else {
    pwmValue = 255;
  }

  analogWrite(motorPin, pwmValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("PWM Value: ");
  Serial.print(pwmValue);
  Serial.print(" / 255  |  Duty Cycle: ");
  Serial.print((pwmValue * 100) / 255);
  Serial.println("%");

  Serial.print("Fan Speed: ");
  if (pwmValue == 0) {
    Serial.println("OFF");
  } else if (pwmValue <= 100) {
    Serial.println("LOW");
  } else if (pwmValue <= 180) {
    Serial.println("MEDIUM");
  } else {
    Serial.println("HIGH");
  }

  Serial.println("-------------------");
  delay(1000);
}
