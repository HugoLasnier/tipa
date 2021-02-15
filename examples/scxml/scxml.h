#ifndef TIPA_SCXML_HPP
#define TIPA_SCXML_H

#include <string>
#include <iostream>
#include "vector"
#include <tinyparser.hpp>
#define MAX 10
using namespace tipa;
using namespace std;
class transition;
class event {
    string id;
public:
    const string &getId() const;
};
class state {
public:
    string id;
    vector<state> v_;
    vector<transition> t_;
    state(const string &id) : id(id) {}
};
class transition {
public:
    string id;
    string event;
    state target;
    transition(state target) : target(target) {}
    transition(const string &id, const string &event, const state &target) : id(id), event(event), target(target) {}


    friend ostream &operator<<(ostream &os, const transition &t) {
        os << "event: " << t.event << " target: " << t.target.id;
        return os;
    }
};
class Value {
public:
    virtual string toString();
    virtual ~Value() {}
};
class eValue : public Value {
private:
    event e;
public:
    virtual string toString();
    eValue(event e);
};
class builder {
    stack< shared_ptr<Value> > st;
    stack<string> st1;

public:
    void make_Id(parser_context &pc);
    void make_Event(parser_context &pc);
    void make_target(parser_context &pc);
    void make_Transition(parser_context &pc);
    void make_State(parser_context &pc);
    void make_EofState(parser_context &pc);
    void make_EofTransition(parser_context &pc);
    void printScxml();

};

class scxml {
public:
    rule r_id;
    rule r_event;
    rule r_target;
    rule r_transition;
    rule r_state;
    rule r_eof_state;
    rule r_eof_transition;
    rule r_property;

    rule root;

    scxml();
    bool parsescxml(istream &in);
};
#endif //TIPA_SCXML_HPP