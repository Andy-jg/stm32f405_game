#include "State.h"

State::State(Action _update) {
  userEnter = 0;
  userUpdate = _update;
  userExit = 0;

  transitions = new LinkedList<Transition*>();
}

State::State(Action _enter, Action _update, Action _exit) {
  userEnter = _enter;
  userUpdate = _update;
  userExit = _exit;

  transitions = new LinkedList<Transition*>();
}

State::~State() {}

void State::enter() {
  if (userEnter) {
    userEnter();
  }
}

State& State::update() {
  if (userUpdate) {
    userUpdate();
  }

  for (int i = 0; i < transitions->size(); i++) {
    if (transitions->get(i)->predicate()) {
      return *transitions->get(i)->state;
    }
  }

  return *this;
}

void State::exit() {
  if (userExit) {
    userExit();
  }
}

void State::addTransition(Predicate predicate, State& state) {
  struct Transition* transition = new Transition {
    predicate,
    &state
  };

  transitions->add(transition);
}
