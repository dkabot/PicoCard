#ifndef PICOCARD_SCREENS_SCREEN_HELPER_H_
#define PICOCARD_SCREENS_SCREEN_HELPER_H_
#include <cstdint>

#include "PDLS_Basic.h"

#include "screens/screen.h"

namespace picocard {
// Screen tracking constants and variables
const uint8_t kScreenCount = 3;
extern int8_t current_screen; // Signed so we can see if it underflows
extern picocard::Screen* screens[kScreenCount];

void setupScreens();
void actOnScreenState(Screen_EPD& display, ScreenState screen_state);
} // namespace picocard
#endif // PICOCARD_SCREENS_SCREEN_HELPER_H_