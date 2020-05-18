#include "ILI9341.h"

ILI9341::ILI9341(SPIClass* spi, uint8_t cs, uint8_t dc, uint16_t w, uint16_t h) :
  bus(spi),
  pinCS(cs),
  pinDC(dc),
  _width(w),
  _height(h)
{}

uint16_t ILI9341::width() {
  return _width;
}

uint16_t ILI9341::height() {
  return _height;
}

void ILI9341::begin(uint32_t frequency) {
  pinMode(pinSC, OUTPUT);
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
    command_t* command = &initializationCommands[i];

    sendCommand(command);
  }
}

void ILI9341::sendCommand(command_t* command) {
  bus->beginTransaction(settings);
  unsetSC();

  unsetDC();
  bus->transfer(command->code);

  setDC();
  for (uint8_t i = 0; i < command->length & 0x0F; i++) {
    bus->transfer(command->parameters[i]);
  }

  setCS();
  bus->endTransaction();

  if (command->length & 0x10) delay(150);
}

void ILI9341::setWindow(
  uint16_t originX,
  uint16_t originY,
  uint16_t width,
  uint16_t height
) {
  uint16_t destinationX = originX + width - 1
  uint16_t destinationY = originY + height - 1;

  sendCommand({
    COLUMN_ADDRESS_SET,
    4,
    {
      originX >> 8,
      originX & 0xFF,
      destinationX >> 8,
      destinationX & 0xFF
    }
  });
  sendCommand({
    PAGE_ADDRESS_SET,
    4,
    {
      originY >> 8,
      originY & 0xFF,
      destinationY >> 8,
      destinationY & 0xFF
    }
  });
}

void ILI9341::setCS() {
  digitalWrite(pinSC, HIGH);
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
