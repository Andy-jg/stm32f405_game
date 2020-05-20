#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ILI9341.h>
#include <Canvas.h>
#include <Nunchuk.h>
#include <StateMachine.h>

#include "global.h"

ILI9341 display = ILI9341(&SPI, TFT_CS, TFT_DC, 240, 320);
Canvas canvas = Canvas(display.width(), display.height());

Nunchuk controller;
StateMachine machine;

uint16_t palette[] = {
  RGB565(0, 0, 0),
  RGB565(255, 0, 0),
  RGB565(0, 255, 0),
  RGB565(0, 0, 255),
  RGB565(255, 255, 255)
};
const int paletteSize = sizeof(palette) / sizeof(palette[0]);

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
  uint16_t x, y;
  uint8_t color;

  State state = State(
    []() {
      Serial.println("Enter Test");

      x = display.width() / 2;
      y = display.height() / 2;
      color = 0;
    },
    []() {
      // x += controller.analogX / 8 - 16;
      // y += controller.analogY / 8 - 16;

      // if (controller.buttonZ) color = min(color + 1, paletteSize);
      // if (controller.buttonC) color = max(color - 1, 0);

      canvas.fillScreen(0);
      canvas.drawPixel(x, y, color);

      // delay(100);

      // display.setCursor(0, 0);
      // display.fillRect(
      //   0, 0,
      //   display.width(), 20,
      //   ILI9341_BLACK
      // );
      // display.println("JoyX JoyY AccX AccY AccZ Z C");
      // display.printf(
      //   "%4d %4d %4d %4d %4d %d %d",
      //   controller.analogX,
      //   controller.analogY,
      //   controller.accelerometerX,
      //   controller.accelerometerY,
      //   controller.accelerometerZ,
      //   controller.buttonZ,
      //   controller.buttonC
      // );
    },
    []() {
      Serial.println("Exit Test");
    }
  );
}

void setup() {
  Serial.begin(115200);

  while (!Serial) delay(10);
  // while (!Serial.available()) delay(10);

  Serial.println("Initializing...");

  Wire.begin();

  ControllerConnect::state.addTransition(
    []() { return ControllerConnect::connected; },
    Test::state
  );
  // ControllerConnect::state.addTransition(
  //   []() { return !ControllerConnect::connected; },
  //   Halt::state
  // );
  Test::state.addTransition(
    []() { return !controller.update(); },
    Halt::state
  );

  machine.transitionTo(ControllerConnect::state);
  // machine.transitionTo(Test::state);

  display.begin(48000000);
}

void loop() {
  machine.update();
  display.drawWindow(
    0, 0,
    display.width(), display.height(),
    canvas.getBuffer(), palette
  );
}
