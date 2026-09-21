#ifndef PICOCARD_SCREENS_QR_V4_SCREEN_H_
#define PICOCARD_SCREENS_QR_V4_SCREEN_H_
#include "qrcodegen.h"

#include "images/qr_v4_image.h"
#include "screens/image_screen.h"

namespace picocard {
// The seemingly-best scale factor for 200x200 with room for UI elements
// 6x fits, but is 198x198
const uint8_t kQRV4ScaleFactor = 5;

// Displays a QR code (V4)
// No new logic, but this owns its QRV4Image reference
class QRV4Screen : public ImageScreen {
  public:
    // Order differs from ImageScreen, as ECC level needs to be specifiable
    // and scale factor is likely constant
    QRV4Screen(const char* url, const char* label = nullptr,
      qrcodegen_Ecc ecc_level = qrcodegen_Ecc_HIGH,
      const uint8_t scale_factor = kQRV4ScaleFactor);

  private:
      QRV4Image qr_image_;
};
} // namespace picocard
#endif // PICOCARD_SCREENS_QR_V4_SCREEN_H_