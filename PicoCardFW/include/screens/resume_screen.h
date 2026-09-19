#ifndef PICOCARD_SCREENS_RESUME_SCREEN_H_
#define PICOCARD_SCREENS_RESUME_SCREEN_H_
#include "screens/screen.h"
#include "images/qr_v4_image.h"

namespace picocard {
class ResumeScreen : public Screen {
  public:
    ResumeScreen(const char* name, const char* headline, const char* phone,
      const char* email1, const char* email2, const char* desc1,
      const char* desc2, const char* qr_label, const char* qr_url);

    ScreenState onSwitchedTo(Screen_EPD& display) override;
    ScreenState onUpPressed(Screen_EPD& display) override;
    ScreenState onDownPressed(Screen_EPD& display) override;
    // Doesn't need specific left/right button behavior

  private:
    ScreenState drawInfo(Screen_EPD& display);
    ScreenState drawQR(Screen_EPD& display);

    // Style guide calls for separate lines for pointer declarations
    const char* name_;
    const char* headline_;
    const char* phone_;
    const char* email1_;
    const char* email2_;
    const char* role1_;
    const char* role2_;
    const char* qr_label_;
    const QRV4Image qr_image_;

    bool draw_info_;

};
} // namespace picocard
#endif // PICOCARD_SCREENS_RESUME_SCREEN_H_