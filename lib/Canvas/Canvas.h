#ifndef CANVAS_H_
#define CANVAS_H_

#include <Arduino.h>

class Canvas {

  private:

  uint16_t _width;
  uint16_t _height;

  uint8_t* buffer;

  public:

  Canvas(uint16_t, uint16_t);
  ~Canvas();

  void drawPixel(uint16_t, uint16_t, uint8_t);
  void fillScreen(uint8_t);

  uint8_t* getBuffer() const;

};

#endif // CANVAS_H_
