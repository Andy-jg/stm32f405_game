#ifndef ILI9341_H_
#define ILI9341_H_

#include <Arduino.h>
#include <SPI.h>

#include "command.h"

class ILI9341 {

  private:

  SPISettings settings;
  SPIClass* bus;

  uint32_t pinCS;
  uint32_t pinDC;

  uint16_t _width;
  uint16_t _height;

  void setCS();
  void unsetCS();
  void setDC();
  void unsetDC();

  public:

  ILI9341(SPIClass*, uint32_t, uint32_t, uint16_t, uint16_t);

  uint16_t width();
  uint16_t height();

  void begin(uint32_t);
  void sendCommand(command_t*);

  void setWindow(uint16_t, uint16_t, uint16_t, uint16_t);

}

#endif // ILI9341_H_
