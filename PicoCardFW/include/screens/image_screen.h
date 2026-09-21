#ifndef PICOCARD_SCREENS_IMAGE_SCREEN_H_
#define PICOCARD_SCREENS_IMAGE_SCREEN_H_
#include "screens/screen.h"
#include "images/image.h"

namespace picocard {
// Displays an integer-scaled Image, with an optional label
class ImageScreen : public Screen {
  public:
    ImageScreen(const Image& image, const uint8_t scale_factor = 1,
      const char* label = nullptr);
    ScreenState onSwitchedTo(Screen_EPD& display) override;
    // Doesn't need special button behavior whatsoever

  private:
    // A reference isn't great here, but an Image can't be instantiated;
    // I think it's best to leave this, and extend ImageScreen where possible
    const Image& image_;
    const uint8_t scale_factor_;
    const char* label_;
};
} // namespace picocard
#endif // PICOCARD_SCREENS_IMAGE_SCREEN_H_