#include "StateMachine.h"

StateMachine::StateMachine() {
  current = 0;
  next = 0;
  lastChange = 0;
}

StateMachine::~StateMachine() {}

void StateMachine::update() {
  if (current != next) {
    immediateTransitionTo(*next);
  }

  next = &current->update();
}

void StateMachine::transitionTo(State& state) {
  next = &state;
}

void StateMachine::immediateTransitionTo(State& state) {
  if (current) current->exit();

  current = next = &state;
  lastChange = millis();

  current->enter();
}

bool StateMachine::in(State& state) const {
  return &state == current;
}

State& StateMachine::getCurrent() {
  return *current;
}

uint32_t StateMachine::timeInCurrent() {
  return millis() - lastChange;
}
