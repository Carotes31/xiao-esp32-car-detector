#include "camera_manager.h"

#include <esp_camera.h>

namespace {

// Pin mapping for the Xiao ESP32-S3 Sense / OV3660 board.
// Validate against your exact revision and adjust if needed.
constexpr camera_config_t kCameraConfig = {
    .pin_pwdn = -1,
    .pin_reset = -1,
    .pin_xclk = 15,
    .pin_sscb_sda = 4,
    .pin_sscb_scl = 5,
    .pin_d7 = 16,
    .pin_d6 = 17,
    .pin_d5 = 18,
    .pin_d4 = 12,
    .pin_d3 = 10,
    .pin_d2 = 8,
    .pin_d1 = 9,
    .pin_d0 = 11,
    .pin_vsync = 6,
    .pin_href = 7,
    .pin_pclk = 13,
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,
    .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_SVGA,
    .jpeg_quality = project::CAMERA_JPEG_QUALITY,
    .fb_count = 2,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

}  // namespace

bool CameraManager::begin() {
  if (initialized_) {
    return true;
  }

  esp_err_t err = esp_camera_init(&kCameraConfig);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    return false;
  }

  sensor_t* sensor = esp_camera_sensor_get();
  if (sensor) {
    sensor->set_framesize(sensor, FRAMESIZE_SVGA);
    sensor->set_quality(sensor, project::CAMERA_JPEG_QUALITY);
  }

  initialized_ = true;
  Serial.println("Camera initialized successfully.");
  return true;
}

bool CameraManager::captureFrame(std::vector<uint8_t>& output) {
  if (!initialized_) {
    return false;
  }

  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return false;
  }

  output.clear();
  output.assign(fb->buf, fb->buf + fb->len);

  esp_camera_fb_return(fb);
  return !output.empty();
}

void CameraManager::stop() {
  if (initialized_) {
    esp_camera_deinit();
    initialized_ = false;
  }
}
