#include <Wire.h>

#define LM75_ADDRESS 0x48

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Health Monitoring System");
  Serial.println("------------------------");
}

void loop() {
  Wire.beginTransmission(LM75_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(LM75_ADDRESS, 2);

  if (Wire.available() == 2) {
    int msb = Wire.read();
    int lsb = Wire.read();

    int raw = (msb << 8) | lsb;
    raw >>= 7;

    if (raw & 0x100)
      raw -= 512;

    float temperature = raw * 0.5;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    if (temperature >= 38.0)
      Serial.println("Status: HIGH TEMPERATURE");
    else
      Serial.println("Status: NORMAL");
  } else {
    Serial.println("Sensor Error");
  }

  delay(1000);
}
