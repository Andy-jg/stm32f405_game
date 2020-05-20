#include "ILI9341.h"

ILI9341::ILI9341(
  SPIClass* spi,
  uint32_t cs,
  uint32_t dc,
  uint16_t width,
  uint16_t height
) :
  bus(spi),
  pinCS(cs),
  pinDC(dc),
  _width(width),
  _height(height)
{}

uint16_t ILI9341::width() {
  return _width;
}

uint16_t ILI9341::height() {
  return _height;
}

void ILI9341::begin(uint32_t frequency) {
  pinMode(pinCS, OUTPUT);
  pinMode(pinDC, OUTPUT);

  setCS();
  setDC();

  settings = SPISettings(
    frequency,
    MSBFIRST,
    SPI_MODE0
  );

  size_t commandCount = sizeof(initializationCommands) / sizeof(initializationCommands[0]);

  for (size_t i = 0; i < commandCount; i++) {
    const command_t command = initializationCommands[i];

    sendCommand(command.code, command.parameters, command.length);
  }
}

void ILI9341::sendCommand(uint8_t code, const uint8_t* parameters, size_t length) {
  transact(
    [&]() {
      writeCommand(code);
      writeParameters(parameters, length);
    }
  );

  if (length & 0x10) delay(150);
}

void ILI9341::drawWindow(
  uint16_t originX,
  uint16_t originY,
  uint16_t width,
  uint16_t height,
  uint8_t* buffer,
  uint16_t* palette
) {
  if (width > _width || height > _height) return;

  uint16_t destinationX = originX + width - 1;
  uint16_t destinationY = originY + height - 1;

  transact(
    [&]() {
      writeCommand(COLUMN_ADDRESS_SET);
      bus->transfer16(originX);
      bus->transfer16(destinationX);
    }
  );
  transact(
    [&]() {
      writeCommand(PAGE_ADDRESS_SET);
      bus->transfer16(originY);
      bus->transfer16(destinationY);
    }
  );
  transact(
    [&]() {
      writeCommand(MEMORY_WRITE);

      uint32_t length = width * height;

      for (size_t i = 0; i < length; i++) {
        uint16_t color = palette[buffer[i]];

        bus->transfer16(color);
      }
    }
  );
}

void ILI9341::transact(const action_t& action) {
  bus->beginTransaction(settings);
  unsetCS();

  action();

  setCS();
  bus->endTransaction();
}

void ILI9341::writeCommand(uint8_t code) {
  unsetDC();

  bus->transfer(code);
}

void ILI9341::writeParameters(const uint8_t* parameters, size_t length) {
  setDC();

  for (uint8_t i = 0; i < (length & 0x0F); i++) {
    bus->transfer(parameters[i]);
  }
}

void ILI9341::setCS() {
  digitalWrite(pinCS, HIGH);
}

void ILI9341::unsetCS() {
  digitalWrite(pinCS, LOW);
}

void ILI9341::setDC() {
  digitalWrite(pinDC, HIGH);
}

void ILI9341::unsetDC() {
  digitalWrite(pinDC, LOW);
}
