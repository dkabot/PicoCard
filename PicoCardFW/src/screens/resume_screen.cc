#include "screens/resume_screen.h"

#include <Arduino.h>

#include <cstdint>

#include "ui_helper.h"

namespace picocard {
// Constants for positioning, so they aren't hardcoded mid-statements
const uint8_t kResumeOffsetLarge = 24;
const uint8_t kResumeOffsetMedium = 12;
const uint8_t kResumeOffsetSmall = 4;

ResumeScreen::ResumeScreen(const char* name, const char* headline,
  const char* phone, const char* email1, const char* email2, const char* role1,
  const char* role2, const char* qr_label, const char* qr_url)
    : name_(name),
      headline_(headline),
      phone_(phone),
      email1_(email1),
      email2_(email2),
      role1_(role1),
      role2_(role2),
      qr_label_(qr_label),
      qr_screen_(QRV4Screen(qr_url, name)),
      draw_info_(true) {}

ScreenState ResumeScreen::onSwitchedTo(Screen_EPD& display) {
  // Ignore which state we were on and always start on Info
  draw_info_ = true;
  // This should clear screen and return FLUSH... which this sub-call will
  return ResumeScreen::drawInfo(display);
}

ScreenState ResumeScreen::onUpPressed(Screen_EPD& display) {
  // Up button returns from QR to info page
  if(draw_info_) {
    return ScreenState::UNALTERED;
  }
  else {
    draw_info_ = true;
    return ResumeScreen::drawInfo(display);
  }
}

ScreenState ResumeScreen::onDownPressed(Screen_EPD& display) {
  // Down button changes from info page to QR
  if(draw_info_) {
    draw_info_ = false;
    return ResumeScreen::drawQR(display);
  }
  else {
    return ScreenState::UNALTERED;
  }
}

ScreenState ResumeScreen::drawInfo(Screen_EPD& display) {
  display.clear(); // Always clear the display before starting
  display.setFontSolid(false); // Transparent-background text

  // Draw hints
  drawDownHint(display);
  drawLeftHint(display);
  drawRightHint(display);

  // Draw hint label
  display.selectFont(0); // 8px
  display.gText(displayMidX(display) - stringHalfWidth(display, qr_label_),
   displayMaxY(display) - kLabelPosY - display.characterSizeY(), qr_label_);

  // Draw name
  uint16_t y_pos = kSafeDrawStartY;
  display.selectFont(2); // 16px
  display.gText(kSafeDrawStartX, y_pos, name_); // Text defaults to black on white bg

  // Draw headline
  y_pos += display.characterSizeY() + kResumeOffsetMedium;
  display.gText(kSafeDrawStartX, y_pos, headline_);

  // Draw phone
  y_pos += display.characterSizeY() + kResumeOffsetMedium;
  display.gText(kSafeDrawStartX, y_pos, phone_);

  // Draw email
  y_pos += display.characterSizeY() + kResumeOffsetMedium;
  display.gText(kSafeDrawStartX, y_pos, email1_);
  y_pos += display.characterSizeY() + kResumeOffsetSmall;
  display.gText(kSafeDrawStartX, y_pos, email2_);

  // Draw role
  y_pos += display.characterSizeY() + kResumeOffsetLarge;
  display.selectFont(1); // 12px; change after moving relative to last draw
  display.gText(kSafeDrawStartX, y_pos, role1_);
  y_pos += display.characterSizeY() + kResumeOffsetSmall;
  display.gText(kSafeDrawStartX, y_pos, role2_);

  return ScreenState::FLUSH; // Always end by indicating a display refresh
}

ScreenState ResumeScreen::drawQR(Screen_EPD& display) {
  // Draw the QR screen as it would be if standalone
  ScreenState new_screen_state = qr_screen_.onSwitchedTo(display);
  
  // Draw up hint for our use case here
  drawUpHint(display);

  // We're drawing a hint, so make sure the returned result is at least FLUSH
  return max(new_screen_state, ScreenState::FLUSH);
}
} // namespace picocard