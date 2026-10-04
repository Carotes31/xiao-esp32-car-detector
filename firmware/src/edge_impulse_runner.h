#pragma once

#include <Arduino.h>
#include <vector>

class SdManager {
 public:
  bool begin();
  bool saveJpeg(const String& filename, const std::vector<uint8_t>& jpegData);
  bool saveCaptureBurst(const std::vector<uint8_t>& jpegData);
  bool appendLog(const String& message);

 private:
  String generateTimestampedName(const String& prefix) const;

 private:
  bool initialized_ = false;
};
