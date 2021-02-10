#ifndef TIPA_SCXML_H
#define TIPA_SCXML_H

#include <string>
#include <iostream>
#include "vector"
#include <tinyparser.hpp>

using namespace tipa;
using namespace std;

class State;

class Event {
private:
    string name;
public:
    const string &getName() const;

    Event(string name_);
};

class Transition {
private:
    Event *event;
    State *state;
public:
    Event *getEvent() const;

    State *getState() const;

    Transition();;

    Transition(Event *event_, State *state_);
};

class State {
private:
    State(const string &id, const Transition &transition);

    string id;
    vector<Transition> transitions;
    vector<State> *states;
    const Transition transition;
public:
    const vector<Transition> &getTransitions() const;

    const string &getId() const;

    State(const string &id, vector<Transition> transitions);

    State(const string id);

    void addTransition(Transition transition);

    void addState(State state);

};

class Context {
public:
    State *state_;
    string event;

    void to(State *state);

    void show() const;

    Context(State *state);

    void work();
};

#endif //TIPA_SCXML_H