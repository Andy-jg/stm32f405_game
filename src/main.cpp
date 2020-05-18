#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ILI9341.h>
#include <StateMachine.h>
#include <Nunchuk.h>

#include "global.h"

ILI9341 display = ILI9341(&SPI2, TFT_CS, TFT_DC, 240, 320);

Nunchuk controller;
StateMachine machine;

namespace Halt {
  State state = State(
    []() {
      Serial.println("Enter Halt");
    },
    NULL,
    []() {
      Serial.println("Exit Halt");
    }
  );
}

namespace ControllerConnect {
  bool connected;

  State state = State(
    []() {
      Serial.println("Enter ControllerConnect");
    },
    []() {
      connected = controller.begin();
    },
    []() {
      Serial.println("Exit ControllerConnect");
    }
  );
}

namespace Test {
  State state = State(
    []() {
      Serial.println("Enter Test");
    },
    []() {
      delay(100);

      display.setCursor(0, 0);
      display.fillRect(
        0, 0,
        display.width(), 20,
        ILI9341_BLACK
      );
      display.println("JoyX JoyY AccX AccY AccZ Z C");
      display.printf(
        "%4d %4d %4d %4d %4d %d %d",
        controller.analogX,
        controller.analogY,
        controller.accelerometerX,
        controller.accelerometerY,
        controller.accelerometerZ,
        controller.buttonZ,
        controller.buttonC
      );
    },
    []() {
      Serial.println("Exit Test");
    }
  );
}

void setup() {
  Serial.begin(115200);

  // while (!Serial) delay(10);
  // while (!Serial.available()) delay(10);

  Serial.println("Initializing...");

  Wire.begin();

  ControllerConnect::state.addTransition(
    []() { return ControllerConnect::connected; },
    Test::state
  );
  ControllerConnect::state.addTransition(
    []() { return !ControllerConnect::connected; },
    Halt::state
  );
  Test::state.addTransition(
    []() { return !controller.update(); },
    Halt::state
  );

  machine.transitionTo(ControllerConnect::state);

  display.begin(48000000);
}

void loop() {
  machine.update();
}
