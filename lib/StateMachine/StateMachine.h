#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <Arduino.h>

#include "State.h"

class StateMachine {

  private:

  State* current;
  State* next;

  uint32_t lastChange;

  public:

  StateMachine();
  ~StateMachine();

  void update();
  void transitionTo(State&);
  void immediateTransitionTo(State&);

  bool in(State&) const;

  State& getCurrent();

  uint32_t timeInCurrent();

};

#endif // STATE_MACHINE_H_
