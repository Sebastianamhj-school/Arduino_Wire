#include <Wire.h>


#define address 0x4F

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0xAC);
  Wire.write(0);
  Wire.beginTransmission(address);
  Wire.write(0xEE);
  Wire.endTransmission();
}

char c_buffer[8];

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);

  int16_t c_temp = getTemp();

  if(c_temp > 0) {
    c_temp = abs(c_temp);
    sprintf(c_buffer, "-%02u.%1u%s", c_temp / 10, c_temp % 10, "C");
  } else {
    if (c_temp >= 1000) {
      sprintf(c_buffer, "%03u.%1u%s", c_temp / 10, c_temp % 10, "C");
    } else {
      sprintf(c_buffer, " %02u.%1u%s", c_temp / 10, c_temp % 10, "C");
    }
  }
  Serial.println(c_buffer);
}

int16_t getTemp() {
  Wire.beginTransmission(address);
  Wire.write(0xAA);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 2);
  uint8_t t_msb = Wire.read();
  uint8_t t_lsb = Wire.read();

  int16_t raw_t = (int8_t)t_msb << 1 | t_lsb >> 7;
  raw_t = raw_t * 10/2;
  return raw_t;
}
