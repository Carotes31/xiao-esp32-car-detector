#include "edge_impulse_runner.h"

#include <Arduino.h>

// Placeholder inference runner.
// Replace this with the C++ code emitted by Edge Impulse after training.
// This scaffold keeps the pipeline working while the model is not yet integrated.
float runEdgeImpulse(const std::vector<uint8_t>& imageBuffer) {
  if (imageBuffer.empty()) {
    return 0.0f;
  }

  // A simple placeholder that allows the basic pipeline to run without a real model.
  // In a real implementation, call the generated producer and return the confidence.
  return 0.05f;
}
