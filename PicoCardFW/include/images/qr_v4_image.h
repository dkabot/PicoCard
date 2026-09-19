#ifndef PICOCARD_IMAGES_QR_V4_IMAGE_H_
#define PICOCARD_IMAGES_QR_V4_IMAGE_H_
#include "image.h"

namespace picocard {
// Resultant image size of a V4 QR code is always 33x33 pixels
const uint8_t kQRV4Bound = 33;
const uint16_t kQRV4PixelCount = kQRV4Bound * kQRV4Bound; // 1,089 pixels total

class QRV4Image : public Image {
  public:
    // Constructs an Image that either contains the QR code of the given url,
    // or is black (in the event of an error while generating the code)
    QRV4Image(const char* url);
    uint16_t& operator[](int index) override;
    const uint16_t& operator[](int index) const override;

  private:
    uint16_t image_[kQRV4PixelCount];
};
} // namespace picocard
#endif // PICOCARD_IMAGES_QR_V4_IMAGE_H_