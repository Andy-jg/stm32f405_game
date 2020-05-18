#ifndef NUNCHUK_H_
#define NUNCHUK_H_

#include <Arduino.h>
#include <Wire.h>

#include <functional>

#define ADDRESS 0x52
#define DATASIZE 6

typedef std::function<void(uint8_t)> nunchuk_writer_t;
typedef std::function<void(const nunchuk_writer_t&)> nunchuk_action_t;

class Nunchuk {

  private:

  TwoWire* wire;

  bool transmit(const nunchuk_action_t&);
  bool writePointer(uint8_t);
  bool writeRegister(uint8_t, uint8_t);
  bool receiveData(size_t, uint8_t*);

  public:

  int analogX;
  int analogY;

  int accelerometerX;
  int accelerometerY;
  int accelerometerZ;

  bool buttonZ;
  bool buttonC;

  Nunchuk();

  bool begin();
  bool update();
};

#endif // NUNCHUK_H_
