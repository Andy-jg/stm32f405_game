#include "Nunchuk.h"

Nunchuk::Nunchuk() : wire(&Wire) {}

bool Nunchuk::begin() {
  if (!writeRegister(0xF0, 0x55)) return false;

  delay(10);

  if (!writeRegister(0xFB, 0x00)) return false;

  delay(20);

  return update();
}

bool Nunchuk::update() {
  uint8_t data[DATASIZE];

  if (!receiveData(DATASIZE, data)) return false;

  analogX = data[0];
  analogY = data[1];

  accelerometerX = (data[2] << 2) | ((data[5] >> 2) & 0b11);
  accelerometerX = (data[3] << 2) | ((data[5] >> 4) & 0b11);
  accelerometerX = (data[4] << 2) | ((data[5] >> 6) & 0b11);

  buttonZ = !((data[5] >> 0) & 0b01);
  buttonC = !((data[5] >> 1) & 0b01);

  return true;
}

bool Nunchuk::transmit(const nunchuk_action_t& action) {
  wire->beginTransmission(ADDRESS);

  action([&](uint8_t data) { wire->write(data); });

  return wire->endTransmission() == 0;
}

bool Nunchuk::writePointer(uint8_t pointer) {
  return transmit(
    [&](const nunchuk_writer_t& write) {
      write(pointer);
    }
  );
}

bool Nunchuk::writeRegister(uint8_t deviceRegister, uint8_t value) {
  return transmit(
    [&](const nunchuk_writer_t& write) {
      write(deviceRegister);
      write(value);
    }
  );
}

bool Nunchuk::receiveData(size_t requestSize, uint8_t* data) {
  if (!writePointer(0x00)) return false;

  delayMicroseconds(175);

  uint8_t bytesRead = wire->readBytes(
    data,
    wire->requestFrom(ADDRESS, requestSize)
  );

  return bytesRead == requestSize;
}
