#include <Arduino.h>
#include <vector>

#include "config.h"
#include "camera_manager.h"

CameraManager cam;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n=== Xiao ESP32-S3 Camera Test ===");

  if (!cam.beginCamera()) {
    Serial.println("Camera failed");
    while (1) {
      delay(1000);
    }
  }

  if (!cam.beginSd()) {
    Serial.println("SD failed, continuing anyway");
  }

  if (!cam.beginWifiAp()) {
    Serial.println("WiFi AP failed");
  }

  Serial.println("Base setup OK\n");
}

void loop() {
  static int count = 0;
  std::vector<uint8_t> frame;

  if (cam.captureFrame(frame)) {
    String fileName = cam.timestampFileName("test");
    if (cam.saveJpeg(fileName, frame)) {
      Serial.printf("Frame saved: %s\n", fileName.c_str());
    }
  }

  Serial.println("Waiting...");
  delay(5000);

  count++;
  if (count > 5) {
    Serial.println("End of basic validation cycle");
    while (1) {
      delay(1000);
    }
  }
}
