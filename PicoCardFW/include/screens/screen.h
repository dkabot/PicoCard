#ifndef PICOCARD_SCREENS_SCREEN_H_
#define PICOCARD_SCREENS_SCREEN_H_
#include "PDLS_Basic.h"

namespace picocard {
enum class ScreenState {
  // Numerical values for comparison; higher values take precedence
  UNALTERED = 0, // Calling function can proceed with no further action
  FLUSH = 1, // Calling function should refresh the screen
  PREVIOUS_SCREEN = 2, // Calling function should advance one screen
  NEXT_SCREEN = 3 // Calling function should go back one screen
};

class Screen {
  public:
  // Likely calls clear() at the start and returns FLUSH
  virtual ScreenState onSwitchedTo(Screen_EPD& display) = 0; 

  // May do anything, though at some point left/right should change screens
  virtual ScreenState onSelectPressed(Screen_EPD& display);
  virtual ScreenState onUpPressed(Screen_EPD& display);
  virtual ScreenState onDownPressed(Screen_EPD& display);
  virtual ScreenState onLeftPressed(Screen_EPD& display);
  virtual ScreenState onRightPressed(Screen_EPD& display);
};

// Default implementations
// UP/DOWN/SELECT do nothing and LEFT/RIGHT change screens
inline ScreenState Screen::onSelectPressed(Screen_EPD& display) {
 return ScreenState::UNALTERED;
}
inline ScreenState Screen::onUpPressed(Screen_EPD& display) {
 return ScreenState::UNALTERED;
}
inline ScreenState Screen::onDownPressed(Screen_EPD& display) {
 return ScreenState::UNALTERED;
}
inline ScreenState Screen::onLeftPressed(Screen_EPD& display) {
 return ScreenState::PREVIOUS_SCREEN;
}
inline ScreenState Screen::onRightPressed(Screen_EPD& display) {
 return ScreenState::NEXT_SCREEN;
}
} // namespace picocard
#endif // PICOCARD_SCREENS_SCREEN_H_