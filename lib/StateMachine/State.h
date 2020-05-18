#ifndef STATE_H_
#define STATE_H_

#include <Arduino.h>

#include <LinkedList.h>

typedef bool (*Predicate)();
typedef void (*Action)();

struct Transition;

class State {

  private:

  Action userEnter;
  Action userUpdate;
  Action userExit;

  LinkedList<Transition*>* transitions;

  public:

  State(Action);
  State(Action, Action, Action);
  ~State();

  void enter();
  State& update();
  void exit();

  void addTransition(Predicate, State&);

};

struct Transition {
  Predicate predicate;
  State* state;
};

#endif // STATE_H_
