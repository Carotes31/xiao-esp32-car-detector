#pragma once

#include <Arduino.h>
#include <vector>

namespace project {
constexpr const char* WIFI_SSID = "XIAO-LUX-CAM";
constexpr const char* WIFI_PASSWORD = "luxury123";
constexpr uint16_t WIFI_PORT = 80;

constexpr uint16_t CAMERA_WIDTH = 800;
constexpr uint16_t CAMERA_HEIGHT = 600;
constexpr int CAMERA_JPEG_QUALITY = 12;

constexpr float DETECTION_THRESHOLD = 0.75f;
constexpr size_t BURST_FRAME_COUNT = 8;
constexpr uint32_t CAPTURE_GAP_MS = 250;

constexpr int SD_MISO_PIN = 38;
constexpr int SD_MOSI_PIN = 39;
constexpr int SD_SCK_PIN = 40;
constexpr int SD_CS_PIN = 41;

constexpr const char* CAPTURE_DIR = "/captures";
constexpr const char* EVENT_LOG_PATH = "/captures/events.log";
}
