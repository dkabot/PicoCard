#include "screens/image_screen.h"

#include "PDLS_Basic.h"

#include "ui_helper.h"

namespace picocard {
// Was originally a hardcoded 2px, but is now relative to kLabelPosY
const uint8_t kImageOffset = kLabelPosY - kHintTriangleHeight;

ImageScreen::ImageScreen(const Image& image, const uint8_t scale_factor, const char* label)
  : image_(image), scale_factor_(scale_factor), label_(label) {}

ScreenState ImageScreen::onSwitchedTo(Screen_EPD& display) {
  display.clear(); // Always clear the display before starting
  display.selectFont(1); // 12px, for legibility
  display.setFontSolid(false); // Transparent-background text

  // Draw hints
  drawLeftHint(display);
  drawRightHint(display);

  if (label_ != nullptr) {
    // Draw label, if there is one
    display.gText(displayMidX(display) - stringHalfWidth(display, label_),
      kLabelPosY, label_);
  }

  // Calculate Image position
  // Centered X
  uint16_t x_pos = displayMidX(display) - image_.get_size_x()
    * scale_factor_ / 2;
  // Centered Y
  uint16_t y_pos = displayMidY(display) - image_.get_size_y()
    * scale_factor_ / 2;

  if (label_ != nullptr) {
    // Non-centered Y, below the label, if there is one
    y_pos = kLabelPosY + display.characterSizeY() + kImageOffset;
  }

  // Draw image
  drawImage(display, x_pos, y_pos, image_, scale_factor_);
  
  return ScreenState::FLUSH; // Always end by indicating a display refresh
}
} // namespace picocard