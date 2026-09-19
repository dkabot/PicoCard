#include "ui_helper.h"

#include <cstring>

namespace picocard {
// Helpers, midpoint X/Y of the screen, slightly shortens below functions
uint16_t displayMidX(Screen_EPD& display) {
  return display.screenSizeX() / 2;
}
uint16_t displayMidY(Screen_EPD& display) {
  return display.screenSizeY() / 2;
}

// Helpers, maximum X/Y you can address, slightly shortens below functions
uint16_t displayMaxX(Screen_EPD& display) {
  return display.screenSizeX() - 1;
}
uint16_t displayMaxY(Screen_EPD& display) {
  return display.screenSizeY() - 1;
}

// Helpers, (half of) string length in pixels
// Terminal is a monospaced font, so we need the display for its current size
uint16_t stringWidth(Screen_EPD& display, const char* string) {
  return strlen(string) * display.characterSizeX(string[0]); // First char
}
uint16_t stringHalfWidth(Screen_EPD& display, const char* string) {
  return stringWidth(display, string) / 2;
}

// Helper, draws a "press up for previous page" UI hint
void drawUpHint(Screen_EPD& display, const uint16_t color) {
  display.setPenSolid(true); // Can't check this externally...

  // Start at (mid_x, 0), to (mid_x + half_length, height)
  // and (mid_x - half_length, height)
  uint16_t start_x_pos = displayMidX(display);
  uint16_t start_y_pos = 0;
  uint16_t mid_x_pos = displayMidX(display) + kHintTriangleHalfLength;
  uint16_t mid_end_y_pos = kHintTriangleHeight;
  uint16_t end_x_pos = displayMidX(display) - kHintTriangleHalfLength;
  display.triangle(start_x_pos, start_y_pos, mid_x_pos, mid_end_y_pos,
    end_x_pos, mid_end_y_pos, color);
}

// Helper, draws a "press down for next page" UI hint
void drawDownHint(Screen_EPD& display, const uint16_t color) {
  display.setPenSolid(true); // Can't check this externally...

  // Start at (mid_x, max_y), to (mid_x + half_length, max_y - height)
  // and (mid_x - half_length, max_y - height)
  uint16_t start_x_pos = displayMidX(display);
  uint16_t start_y_pos = displayMaxY(display);
  uint16_t mid_x_pos = displayMidX(display) + kHintTriangleHalfLength;
  uint16_t mid_end_y_pos = displayMaxY(display) - kHintTriangleHeight;
  uint16_t end_x_pos = displayMidX(display) - kHintTriangleHalfLength;
  display.triangle(start_x_pos, start_y_pos, mid_x_pos, mid_end_y_pos,
    end_x_pos, mid_end_y_pos, color);
}

// Helper, draws a "press left for previous screen" UI hint
void drawLeftHint(Screen_EPD& display, const uint16_t color) {
  display.setPenSolid(true); // Can't check this externally...

  // Start at (0, mid_y), go to (height, mid_y + half_length)
  // and (height, mid_y - half_length)
  uint16_t start_x_pos = 0;
  uint16_t start_y_pos = displayMidY(display);
  uint16_t mid_end_x_pos = kHintTriangleHeight;
  uint16_t mid_y_pos = displayMidY(display) + kHintTriangleHalfLength;
  uint16_t end_y_pos = displayMidY(display) - kHintTriangleHalfLength;
  display.triangle(start_x_pos, start_y_pos, mid_end_x_pos, mid_y_pos,
    mid_end_x_pos, end_y_pos, color);
}

// Helper, draws a "press right for next screen" UI hint
void drawRightHint(Screen_EPD& display, const uint16_t color) {
  display.setPenSolid(true); // Can't check this externally...

  // Start at (max_x, mid_y), go to (max_x - height, mid_y + half_length)
  // and (max_x - height, mid_y - half_length)
  uint16_t start_x_pos = displayMaxX(display);
  uint16_t start_y_pos = displayMidY(display);
  uint16_t mid_end_x_pos = displayMaxX(display) - kHintTriangleHeight;
  uint16_t mid_y_pos = displayMidY(display) + kHintTriangleHalfLength;
  uint16_t end_y_pos = displayMidY(display) - kHintTriangleHalfLength;
  display.triangle(start_x_pos, start_y_pos, mid_end_x_pos, mid_y_pos,
    mid_end_x_pos, end_y_pos, color);
}

// Draws an image from a given array at the given scale
void drawImage(Screen_EPD& display, const uint16_t x_pos, const uint16_t y_pos,
  const Image &image, const uint8_t scale_factor) {
    if (scale_factor < 1) {
    // 0 scale should just do nothing and negative would be undefined
    return;
  }

  display.setPenSolid(true); // Can't check this externally...

  for (uint16_t current_pixel = 0;
     current_pixel < image.get_size_x() * image.get_size_y(); current_pixel++)
     {
    // The (un-scaled) pixel we're addressing
    uint8_t x_pixel = current_pixel % image.get_size_x();
    uint8_t y_pixel = current_pixel / image.get_size_y();
    
    // The scaled start/end positions for said pixel
    uint16_t start_x_pos = x_pos + scale_factor * x_pixel;
    uint16_t start_y_pos = y_pos + scale_factor * y_pixel;
    uint16_t end_x_pos = start_x_pos + (scale_factor - 1);
    uint16_t end_y_pos = start_y_pos + (scale_factor - 1);
    display.rectangle(start_x_pos, start_y_pos, end_x_pos, end_y_pos,
      image[current_pixel]);
  }
}
}