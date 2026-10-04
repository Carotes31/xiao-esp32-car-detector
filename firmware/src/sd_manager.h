#include "sd_manager.h"

#include <SPI.h>
#include <SD.h>

#include "config.h"

bool SdManager::begin() {
  SPI.begin(project::SD_SCK_PIN, project::SD_MISO_PIN, project::SD_MOSI_PIN, project::SD_CS_PIN);

  if (!SD.begin(project::SD_CS_PIN, SPI, 8000000)) {
    Serial.println("SD card initialization failed");
    return false;
  }

  if (!SD.exists(project::CAPTURE_DIR)) {
    if (!SD.mkdir(project::CAPTURE_DIR)) {
      Serial.println("Failed to create captures directory");
      return false;
    }
  }

  initialized_ = true;
  Serial.println("SD card initialized successfully.");
  return true;
}

bool SdManager::saveJpeg(const String& filename, const std::vector<uint8_t>& jpegData) {
  if (!initialized_ || jpegData.empty()) {
    return false;
  }

  String path = String(project::CAPTURE_DIR) + "/" + filename;
  File file = SD.open(path.c_str(), FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open JPG file for writing");
    return false;
  }

  const size_t written = file.write(jpegData.data(), jpegData.size());
  file.close();

  if (written != jpegData.size()) {
    Serial.println("Partial JPG write detected");
    return false;
  }

  return true;
}

bool SdManager::saveCaptureBurst(const std::vector<uint8_t>& jpegData) {
  const String name = generateTimestampedName("capture") + ".jpg";
  return saveJpeg(name, jpegData);
}

bool SdManager::appendLog(const String& message) {
  if (!initialized_) {
    return false;
  }

  File file = SD.open(project::EVENT_LOG_PATH, FILE_APPEND);
  if (!file) {
    Serial.println("Unable to open event log");
    return false;
  }

  const String line = generateTimestampedName("event") + " " + message + "\n";
  const size_t written = file.print(line);
  file.close();
  return written > 0;
}

String SdManager::generateTimestampedName(const String& prefix) const {
  const uint32_t now = millis();
  return prefix + "_" + String(now);
}
