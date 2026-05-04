#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <FastIMU.h>

// ----------------- OLED -----------------
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// ----------------- IMU -----------------
MPU6500 IMU;
calData calib = { 0 };
AccelData accelData;

// ----------------- Pins -----------------
const int potXPin = A0;
const int potYPin = A1;

// ----------------- Drawing state -----------------
int prevX = 64;
int prevY = 32;
bool firstRun = true;

// ----------------- Shake detection -----------------
const float shakeThreshold = 1.5;
const unsigned long minShakeGap = 300;   // ms between counted shakes
const unsigned long shakeWindow = 2000;  // 2 shakes must happen within this time

int shakeCount = 0;
unsigned long firstShakeTime = 0;
unsigned long lastShakeTime = 0;

// ----------------- Helpers -----------------
int readSmooth(int pin) {
  long sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 8;
}

void clearDrawing(int x, int y) {
  u8g2.clearBuffer();
  u8g2.sendBuffer();

  prevX = x;
  prevY = y;
  firstRun = false;
}

bool doubleShakeDetected() {
  IMU.update();
  IMU.getAccel(&accelData);

  float ax = accelData.accelX;
  float ay = accelData.accelY;
  float az = accelData.accelZ;
  float mag = sqrt(ax * ax + ay * ay + az * az);

  unsigned long now = millis();

  // Reset the shake count if the second shake does not happen within the time window
  if (shakeCount > 0 && (now - firstShakeTime > shakeWindow)) {
    shakeCount = 0;
    firstShakeTime = 0;
  }

  if (mag > shakeThreshold && (now - lastShakeTime > minShakeGap)) {
    lastShakeTime = now;

    if (shakeCount == 0) {
      firstShakeTime = now;
    }

    shakeCount++;

    if (shakeCount >= 2) {
      shakeCount = 0;
      firstShakeTime = 0;
      return true;
    }
  }

  return false;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.sendBuffer();

  int err = IMU.init(calib, 0x68);
  if (err != 0) {
    // Stop here if the IMU does not initialize
    while (1) {}
  }
}

void loop() {
  int rawX = readSmooth(potXPin);
  int rawY = readSmooth(potYPin);

  // X axis flipped, Y axis flipped
  int x = map(rawX, 0, 1023, 127, 0);
  int y = map(rawY, 0, 1023, 63, 0);

  x = constrain(x, 0, 127);
  y = constrain(y, 0, 63);

  // Double shake clears the screen
  if (doubleShakeDetected()) {
    clearDrawing(x, y);
  }

  // Normal drawing
  if (firstRun) {
    prevX = x;
    prevY = y;
    firstRun = false;
  } else {
    u8g2.drawLine(prevX, prevY, x, y);
    prevX = x;
    prevY = y;
  }

  u8g2.sendBuffer();
  delay(10);
}