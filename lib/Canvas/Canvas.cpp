#include "Canvas.h"

Canvas::Canvas(uint16_t width, uint16_t height) : _width(width), _height(height) {
  size_t bytes = width * height;

  if ((buffer = (uint8_t*)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}

Canvas::~Canvas() {
  if (buffer) {
    free(buffer);
  }
}

void Canvas::drawPixel(uint16_t x, uint16_t y, uint8_t color) {
  if (buffer) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) return;

    buffer[x + y * _width] = color;
  }
}

void Canvas::fillScreen(uint8_t color) {
  if (buffer) {
    memset(buffer, color, _width * _height);
  }
}

uint8_t* Canvas::getBuffer() const {
  return buffer;
}
