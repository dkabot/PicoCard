#ifndef PICOCARD_SCREENS_QR_V4_SCREEN_H_
#define PICOCARD_SCREENS_QR_V4_SCREEN_H_
#include "images/qr_v4_image.h"
#include "screens/image_screen.h"

namespace picocard {
// Displays a QR code (V4)
// No new logic, but this owns its QRV4Image reference
class QRV4Screen : public ImageScreen {
  public:
    // Order is reversed from ImageScreen, as scale factor is likely constant
    QRV4Screen(const char* url, const char* label = nullptr, 
      const uint8_t scale_factor = 5);

  private:
      QRV4Image qr_image_;
};
} // namespace picocard
#endif // PICOCARD_SCREENS_QR_V4_SCREEN_H_