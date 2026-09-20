#include "screens/qr_v4_screen.h"

namespace picocard {
// We only need this one constructor
QRV4Screen::QRV4Screen(const char* url, const char* label,
  const uint8_t scale_factor)
  : ImageScreen(qr_image_, scale_factor, label), qr_image_(QRV4Image(url)) {}

} // namespace picocard