#include "screens/screen_helper.h"

#include "resume_info.h"
#include "screens/qr_v4_screen.h"
#include "screens/resume_screen.h"

namespace picocard {
int8_t current_screen = 0;
picocard::Screen* screens[kScreenCount] = { 0 };

void setupScreens() {
  // First two screens are the contact info of the creators
  screens[0] = new ResumeScreen(kResumeName_1, kResumeHeadline_1,
  kResumePhone_1, kResumeEmail1_1, kResumeEmail2_1, kResumeRole1_1,
  kResumeRole2_1, kResumeQRLabel_1, kResumeQRURL_1);

  screens[1] = new ResumeScreen(kResumeName_2, kResumeHeadline_2,
  kResumePhone_2, kResumeEmail1_2, kResumeEmail2_2, kResumeRole1_2,
  kResumeRole2_2, kResumeQRLabel_2, kResumeQRURL_2);

  screens[2] = new QRV4Screen("https://github.com/dkabot/PicoCard", "Check out the code!");

  // More screens forthcoming...?
}

void actOnScreenState(Screen_EPD& display, ScreenState screen_state) {
switch (screen_state) {
  case ScreenState::UNALTERED:
    // Do nothing
    break;
  
  case ScreenState::FLUSH:
    // Update screen state, but do nothing else
    display.flush();
    break;

  case ScreenState::PREVIOUS_SCREEN:
    // Decrement screen index, looping if necessary
    current_screen -= 1;
    if (current_screen < 0) {
      current_screen = kScreenCount - 1;
    }

    // Perform the initial draw of the new screen
    actOnScreenState(display, screens[current_screen]->onSwitchedTo(display));
    break;

  case ScreenState::NEXT_SCREEN:
    // Increment screen index, looping if necessary
    current_screen += 1;
    if (current_screen >= kScreenCount) {
      current_screen = 0;
    }

    // Perform the initial draw of the new screen
    actOnScreenState(display, screens[current_screen]->onSwitchedTo(display));
    break;
}
// Nothing else to do here
}
}