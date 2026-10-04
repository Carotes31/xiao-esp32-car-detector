#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <esp_camera.h>
#include <vector>

#include "config.h"

class CameraManager {
public:
  bool beginCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = 11;
    config.pin_d1 = 9;
    config.pin_d2 = 8;
    config.pin_d3 = 10;
    config.pin_d4 = 12;
    config.pin_d5 = 18;
    config.pin_d6 = 17;
    config.pin_d7 = 16;
    config.pin_xclk = 15;
    config.pin_pclk = 13;
    config.pin_vsync = 6;
    config.pin_href = 7;
    config.pin_sscb_sda = 4;
    config.pin_sscb_scl = 5;
    config.pin_pwdn = -1;
    config.pin_reset = -1;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = project::CAMERA_JPEG_QUALITY;
    config.fb_count = 2;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
      Serial.printf("Camera init failed: 0x%x\n", err);
      return false;
    }

    sensor_t* sensor = esp_camera_sensor_get();
    if (sensor) {
      sensor->set_framesize(sensor, FRAMESIZE_SVGA);
      sensor->set_quality(sensor, project::CAMERA_JPEG_QUALITY);
    }

    Serial.println("Camera initialized successfully.");
    return true;
  }

  bool beginSd() {
    SPI.begin(project::SD_SCK_PIN, project::SD_MISO_PIN, project::SD_MOSI_PIN, project::SD_CS_PIN);

    if (!SD.begin(project::SD_CS_PIN, SPI, 8000000)) {
      Serial.println("SD card init failed!");
      return false;
    }

    if (!SD.exists(project::CAPTURE_DIR)) {
      if (!SD.mkdir(project::CAPTURE_DIR)) {
        Serial.println("Failed to create captures directory");
        return false;
      }
    }

    Serial.println("SD card initialized successfully.");
    return true;
  }

  bool beginWifiAp() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(project::WIFI_SSID, project::WIFI_PASSWORD);

    IPAddress ip = WiFi.softAPIP();
    Serial.print("AP IP: ");
    Serial.println(ip);

    return true;
  }

  bool captureFrame(std::vector<uint8_t>& output) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Failed to capture frame");
      return false;
    }

    output.clear();
    output.assign(fb->buf, fb->buf + fb->len);

    esp_camera_fb_return(fb);
    return !output.empty();
  }

  bool saveJpeg(const String& filename, const std::vector<uint8_t>& jpegData) {
    if (jpegData.empty()) {
      return false;
    }

    String path = String(project::CAPTURE_DIR) + "/" + filename;
    File file = SD.open(path.c_str(), FILE_WRITE);
    if (!file) {
      Serial.println("Failed to open file for writing");
      return false;
    }

    size_t written = file.write(jpegData.data(), jpegData.size());
    file.close();

    if (written != jpegData.size()) {
      Serial.println("Partial write on SD card");
      return false;
    }

    Serial.printf("Saved: %s\n", path.c_str());
    return true;
  }

  String timestampFileName(const String& prefix) {
    return prefix + "_" + String(millis()) + ".jpg";
  }
};
