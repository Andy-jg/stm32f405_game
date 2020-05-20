#ifndef ILI9341_H_
#define ILI9341_H_

#include <Arduino.h>
#include <SPI.h>

#include "command.h"

#include <functional>

#define UpperByte(value) ( (uint8_t)((value) >> 8u) )
#define LowerByte(value) ( (uint8_t)((value) & 0xFFu) )
// #define SwapEndian(value) ( (((value) & 0xFFu) << 8u) | ((value) >> u8) )
#define RGB565(red, green, blue) ( (uint16_t)((red) << 11u) | ((green) << 5u) | (blue) )

typedef std::function<void()> action_t;

class ILI9341 {

  private:

  SPISettings settings;
  SPIClass* bus;

  uint32_t pinCS;
  uint32_t pinDC;

  uint16_t _width;
  uint16_t _height;

  void transact(const action_t&);
  void writeCommand(uint8_t);
  void writeParameters(const uint8_t*, size_t);

  void setCS();
  void unsetCS();
  void setDC();
  void unsetDC();

  public:

  ILI9341(SPIClass*, uint32_t, uint32_t, uint16_t, uint16_t);

  uint16_t width();
  uint16_t height();

  void begin(uint32_t);
  void sendCommand(uint8_t, const uint8_t*, size_t);

  void drawWindow(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t*, uint16_t*);

};

#endif // ILI9341_H_
