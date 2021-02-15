#ifndef TIPA_SCXML_HPP
#define TIPA_SCXML_H

#include <string>
#include <sstream>
#include <iostream>
#include "vector"
#include <tinyparser.hpp>


#define N 10
using namespace tipa;
using namespace std;

class t;

class s {
public:
    string father;
    string id;
    //t *tab[];
};

class t {
public:
    string o;
    string e;
    string t;
};

class e {
public:
    string e;
};

class builder {
    int depth = 0;
    string current_s = "none";
    string father = "none";
    int nb_s = 0;
    s tab_s[N];
    t tab_t[N];
    int nb_t = 0;
    stack<string> st1;
public:
    void make_Id(parser_context &pc);

    void make_Event(parser_context &pc);

    void make_target(parser_context &pc);

    void make_Transition(parser_context &pc);

    void make_EofState(parser_context &pc);

    void printScxml();

    void stateChart();

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