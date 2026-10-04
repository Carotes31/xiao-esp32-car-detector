# Project plan

## Phase 1 — Hardware and firmware base

- Confirm the Xiao ESP32-S3 Sense camera pinout and SD card wiring
- Validate the OV3660 with SVGA (800x600)
- Get the board booting from PlatformIO
- Mount and test the SD card
- Verify the access point and preview endpoints

## Phase 2 — Data collection

- Build a compact dataset of luxury cars, hypercars, sports cars, and negatives
- Include multiple angles, light conditions, and blur scenarios
- Label classes clearly in Edge Impulse
- Keep the dataset balanced to avoid false positives

## Phase 3 — Edge Impulse model

- Create an Edge Impulse project
- Import training images
- Create an impulse using image classification or object detection if needed
- Train and test the model
- Export the C++ library

## Phase 4 — Model integration

- Replace the placeholder inference logic in `edge_impulse_runner.cpp`
- Add a safe confidence threshold (for example 0.75)
- Trigger a burst capture on positive detections only
- Save the best frames plus any metadata

## Phase 5 — Capture logic

- Capture a short burst on each trigger
- Keep the burst short enough to avoid memory overflow
- Save JPGs in `/captures/`
- Append log entries with timestamp and confidence

## Phase 6 — WiFi live preview

- Confirm that `/snapshot` returns a single frame
- Confirm that `/stream` works as a basic MJPEG stream
- Test from a phone or laptop on the local network

## Phase 7 — Outdoor deployment

- Test the system behind a window facing the street
- Verify exposure and lens focus
- Adjust threshold and burst count based on real traffic
- Add a waterproof enclosure and stable power source

## Phase 8 — Tuning and refinement

- Reduce false positives from buses, trucks, and non-luxury cars
- Improve the capture trigger logic
- Consider a secondary validation step before saving a burst
- Add a motion trigger or motion-detection prefilter

## Recommended first milestone

For the first version, aim for:

- SVGA camera capture
- 5–10 image burst on detection
- SD card storage
- Local WiFi preview
- Single positive class: “luxury car”

This keeps the project realistic and manageable while you validate the concept.
