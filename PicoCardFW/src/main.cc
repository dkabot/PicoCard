#include <Arduino.h>

#include <cstdint>

// Display library headers: Base SDK, specific display class definition,
// and wider Arduino library for specific usage
#include "PDLS_Common.h"
#include "Pervasive_BWRY_Small.h"
#include "PDLS_Basic.h"

#include "screens/screen.h"
#include "screens/screen_helper.h"

// Everything from inside the namespace that we need to access
using picocard::ScreenState;
using picocard::kScreenCount;
using picocard::current_screen;
using picocard::screens;
using picocard::setupScreens;
using picocard::actOnScreenState;

// Display library definitions
const Board_EXT kDisplayPins = boardRaspberryPiPico_RP2040_EXT3;
// Prototype uses a color display; this will be switched to a B/W for the final
Pervasive_BWRY_Small display_driver = Pervasive_BWRY_Small(eScreen_EPD_152_QS_06, 
    kDisplayPins);
Screen_EPD display = Screen_EPD(&display_driver);
const uint8_t kDisplayOrientation = ORIENTATION_LANDSCAPE;

// Constant for how long to wait upon each loop() iteration
// Screen flushes block the thread, so we don't need a separate delay for them
const uint16_t kLoopDelay = 100; // 0.1s

// Button constants and variables
const uint8_t kButtonCount = 5;
// Button order is select, up, down, left, right; they poll in this order
const uint8_t button_pins[kButtonCount] = { 5, 1, 2, 3, 4 };
PinStatus button_states[kButtonCount] = { HIGH }; // HIGH is, in fact, the default

void setup() {
  // Enable the display
  hV_HAL_begin();
  display.begin();

  // Set up the display
  //display.regenerate();
  display.setOrientation(kDisplayOrientation);

  // Set up the buttons as input
  for (uint8_t button_index = 0; button_index < kButtonCount; button_index++) {
    pinMode(button_pins[button_index], INPUT_PULLUP);
  }

  // Set up the screens
  setupScreens();

  // Initial screen's initial draw
  actOnScreenState(display, screens[current_screen]->onSwitchedTo(display));
  // Initialization complete!
}

void loop() {
  // Enforces a delay after initial draw before the loop starts
  hV_HAL_delayMilliseconds(kLoopDelay);

  // The action we will eventually take once we've checked all inputs
  ScreenState new_screen_state = ScreenState::UNALTERED;

  // Check every button in order
  for (uint8_t button_index = 0; button_index < kButtonCount; button_index++) {
    // Pin numbers are in linear order, but don't start at 0
    uint8_t button_pin = button_pins[button_index];
    // Button is HIGH when not pressed, LOW when pressed
    bool button_pressed = digitalRead(button_pin) == LOW;
    bool button_debouncing = button_states[button_index] == LOW;

    if (button_pressed) {
      if (!button_debouncing) { // Check debounce
        button_states[button_index] = LOW; // Set debounce
        
        // The highest priority action (see ScreenState) is what ultimately occurs
        switch (button_index) {
          case 0: // Select
            // Select happening first is slightly bad UX,
            // but I think it's the most sensible way to handle this UI
            new_screen_state = max(new_screen_state,
              screens[current_screen]->onSelectPressed(display));
            break;
          case 1: // Up
            new_screen_state = max(new_screen_state,
              screens[current_screen]->onUpPressed(display));
            break;
          case 2: // Down
            new_screen_state = max(new_screen_state,
              screens[current_screen]->onDownPressed(display));
            break;
          case 3: // Left
            new_screen_state = max(new_screen_state,
              screens[current_screen]->onLeftPressed(display));
            break;
          case 4: // Right
            new_screen_state = max(new_screen_state, 
              screens[current_screen]->onRightPressed(display));
            break;
        } // switch (button_index)
      } // if (button_debouncing)
    } // if (button_pressed)
    else if (button_debouncing) {
      button_states[button_index] = HIGH; // Clear debounce
    }
  }

  // Reacting to new state is separate so that it can recur if (somehow) needed
  actOnScreenState(display, new_screen_state);
  // Onward to the next loop!
}