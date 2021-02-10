#include <string>
#include <iostream>
#include "vector"
#include <scxml.h>

using namespace tipa;
using namespace std;

Event::Event(string name_) : name(name_) {}

const string &Event::getName() const {
    return name;
}

Event *Transition::getEvent() const {
    return event;
}

State *Transition::getState() const {
    return state;
}

Transition::Transition(Event *event_, State *state_) : event(event_), state(state_) {}

Transition::Transition() {}


const vector<Transition> &State::getTransitions() const {
    return transitions;
}

const string &State::getId() const {
    return id;
}

State::State(const string &id, const Transition &transition) : id(id), transition(transition) {}

State::State(const string id) : id(id) {}

void State::addTransition(Transition transition) {
    this->transitions.push_back(transition);
}

void State::addState(State state) {
    this->states->push_back(state);
}


void Context::to(State *state) {
    cout << "Changing State" << endl;
    this->state_ = state;
}

void Context::show() const {
    cout << "Current state : " << this->state_->getId() << endl;
}

Context::Context(State *state) {
    this->state_ = state;
}

void Context::work() {
    this->show();
    cout << "Enter an Event : ";
    cin >> event;
    if(event == "quit") exit;
    else {


    for (int i = 0; i < this->state_->getTransitions().size(); i++) {
        if (this->state_->getTransitions().at(i).getEvent()->getName() == event) {
            cout << "Current State : " << this->state_->getId() << endl
                 << "Target State : " << this->state_->getTransitions().at(i).getState()->getId() << endl;
            this->to(this->state_->getTransitions().at(i).getState());
        }
    }
    this->work();
    }
}
