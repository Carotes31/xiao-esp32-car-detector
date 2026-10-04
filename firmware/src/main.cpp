#include <Arduino.h>
#include <vector>
#include "camera_manager.h"
#include "sd_manager.h"
#include "config.h"

// Forward declaration
float runEdgeImpulse(const std::vector<uint8_t>& imageBuffer);

// Global instances
CameraManager camera;
SdManager sd;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n=== ESP32-S3 Luxury Car Detector ===");
  Serial.println("Starting initialization...");

  // Initialize camera
  if (!camera.begin()) {
    Serial.println("ERROR: Camera initialization failed!");
    return;
  }
  Serial.println("✓ Camera initialized");

  // Initialize SD card
  if (!sd.begin()) {
    Serial.println("WARNING: SD card initialization failed - continuing without SD storage");
  } else {
    Serial.println("✓ SD card initialized");
  }

  Serial.println("=== Ready for capture ===\n");
}

void loop() {
  // Placeholder main loop
  // Later this will:
  // 1. Capture a frame
  // 2. Run Edge Impulse inference
  // 3. If confidence > threshold, trigger burst capture
  // 4. Save to SD + log event
  
  delay(1000);
  Serial.println("Loop running...");
}
