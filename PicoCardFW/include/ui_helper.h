#ifndef PICOCARD_UI_HELPER_H_
#define PICOCARD_UI_HELPER_H_
#include <cstdint>

#include "PDLS_Basic.h"

#include "images/image.h"

namespace picocard {
// The size of the UI hint triangles (based on left/right; invert for up/down)
const uint16_t kHintTriangleHeight = 5;
const uint16_t kHintTriangleHalfLength = 4; // Total length this * 2 + 1
// The coordinates at which a Screen can safely draw and not overlap UI hints
// Both are 0-indexed and therefore 1 higher than apparent at a glance 
const uint16_t kSafeDrawStartX = kHintTriangleHeight + 1; // 2px gap
const uint16_t kSafeDrawStartY = kSafeDrawStartX; // Only x size matters

// Was originally a hardcoded 7px in resume_screen.h,
// but is now more generally useful for positioning top/bottom labels
const uint8_t kLabelPosY = kSafeDrawStartY + 1;

// Helpers, midpoint X/Y of the screen, slightly shortens below functions
uint16_t displayMidX(Screen_EPD& display);
uint16_t displayMidY(Screen_EPD& display);

// Helpers, maximum X/Y you can address, slightly shortens below functions
uint16_t displayMaxX(Screen_EPD& display);
uint16_t displayMaxY(Screen_EPD& display);

// Helpers, calculate the pixel width (or half of it) for a given string
uint16_t stringWidth(Screen_EPD& display, const char* string);
uint16_t stringHalfWidth(Screen_EPD& display, const char* string);

// Helpers, draw "press direction for previous/next" UI hints
void drawUpHint(Screen_EPD& display, const uint16_t color = myColours.black);
void drawDownHint(Screen_EPD& display, const uint16_t color = myColours.black);
void drawLeftHint(Screen_EPD& display, const uint16_t color = myColours.black);
void drawRightHint(Screen_EPD& display, const uint16_t color = myColours.black);

// Draws the given image at the given position and scale
void drawImage(Screen_EPD& display, const uint16_t x_pos, const uint16_t y_pos,
  const Image &image, const uint8_t scale_factor = 1);
} // namespace picocard
#endif // PICOCARD_UI_HELPER_H_