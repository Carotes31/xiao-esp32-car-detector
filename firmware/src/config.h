#pragma once

#include <Arduino.h>

namespace project {
  // WiFi
  constexpr const char* WIFI_SSID = "XIAO-LUX-CAM";
  constexpr const char* WIFI_PASSWORD = "luxury123";

  // Camera
  constexpr uint16_t CAMERA_WIDTH = 800;
  constexpr uint16_t CAMERA_HEIGHT = 600;
  constexpr int CAMERA_JPEG_QUALITY = 12;

  // SD card pins (SPI mode)
  constexpr int SD_MISO_PIN = 38;
  constexpr int SD_MOSI_PIN = 39;
  constexpr int SD_SCK_PIN = 40;
  constexpr int SD_CS_PIN = 41;

  constexpr const char* CAPTURE_DIR = "/captures";
  constexpr const char* EVENT_LOG_PATH = "/captures/events.log";

  // Detection config
  constexpr float DETECTION_THRESHOLD = 0.75f;
  constexpr int BURST_COUNT = 8;
  constexpr int BURST_GAP_MS = 250;
}
