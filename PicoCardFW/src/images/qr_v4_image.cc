#include "images/qr_v4_image.h"

#include <cstdint>

#include <Arduino.h>
#include "PDLS_Basic.h"

namespace picocard {
// V4 QR codes get buffered and stored as 138 byte arrays
const uint8_t kQRV4Size = qrcodegen_BUFFER_LEN_FOR_VERSION(4);

QRV4Image::QRV4Image(const char* url, qrcodegen_Ecc ecc_level)
  // While QR codes are generally black data on a white background,
  // the background color of the image is black, to make errors obvious
  : Image(kQRV4Bound, kQRV4Bound), image_{ myColours.black } {
  uint8_t temp_buffer[kQRV4Size] = { 0 };
  uint8_t qr_code[kQRV4Size] = { 0 };
  bool success = qrcodegen_encodeText(url, temp_buffer, qr_code,
    ecc_level, 4, 4, qrcodegen_Mask_AUTO, false);
  if(success) {
    // This should always be 33 pixels, but never hurts to make sure...
    uint8_t xy_bound = min(kQRV4Bound, qrcodegen_getSize(qr_code));
    for (u_int8_t y_pixel = 0; y_pixel < xy_bound; y_pixel++) {
      for (uint8_t x_pixel = 0; x_pixel < xy_bound; x_pixel++) {
        bool pixel_is_white = !qrcodegen_getModule(qr_code, x_pixel, y_pixel);
        if (pixel_is_white) {
          // The array is initialized to black, so we only set white pixels
          image_[y_pixel * xy_bound + x_pixel] = myColours.white;
        } // if (pixel_is_white) {
      } // for (x_pixel)
    } // for (y_pixel)
  } // if (success)
  // If the QR generation fails, the image remains black
}

uint16_t& QRV4Image::operator[](int index) {
  // Could check for invalid access here, but have no special error state
  // so leaving it as-is; it'll become evident if you use it wrong anyway
  return image_[index];
}

const uint16_t& QRV4Image::operator[](int index) const {
  // Identical to the above, but disallows modification
  return image_[index];
}
} // namespace picocard