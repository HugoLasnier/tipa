#include <string>
#include <iostream>
#include "vector"
#include <tinyparser.hpp>
#include <scxml.h>
#include <sstream>

using namespace tipa;
using namespace std;

int main() {
    rule event = rule("event=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    rule cond = rule("cond=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    rule target = rule("target=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    rule id = rule("id=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    // a transition is any event, cond, target(none is required)
    rule property = event | cond | target;
    // a transitions has a sequence of properties.
    rule transition = rule("<transition") >> *property >> rule("/>");
    // a state is a list of transition.
    rule state = rule("<state ") >> id >> rule (">") >> *transition >> rule("</state>");

    // the whole file is just a list of transitions
    //rule root = *transition;
    rule root = *state;
    struct Transitions {
        std::string event;
        std::string cond;
        std::string target;

        void clear() {
            event = "";
            cond = "";
            target = "";
        }
    };
    struct States {
        std::string id;
        void clear () {
            id = "";
        }
        bool know() {
            return id!="";
        }
    };
    std::vector<Transitions> transitions;
    std::vector<State> states;
    States tmp;
    Transitions temp;
    auto *s = new State("s");
    // now the parser actions
    // when the parser finds an event, store the values in the temp variable
    id.read_vars(tmp.id);
    cout << "l id :" << tmp.id << endl;
    if(tmp.know()) {
        cout << "entering the condition " << endl;
        //auto *nb.at(n) = new State(tmp.id);
        auto *s1 = new State(tmp.id);
        event.read_vars(temp.event);
        target.read_vars(temp.target);
        transition.set_action([&temp, &transitions](parser_context &pc) {
            transitions.push_back(temp);
            temp.clear();
        });
        for (const auto &x : transitions) {
            s1->addTransition(*new Transition(new Event(x.event), new State(x.target)));
        }
        s->addState(*s1);
    }

    event.read_vars(temp.event);
    //cout << "l'event : "<< temp.event<<endl;
    // same for cond
    //cond.read_vars(temp.cond);
    // same for target
    target.read_vars(temp.target);
    // when we detect a button, we store the temp variable in the vector of buttons
    transition.set_action([&temp, &transitions](parser_context &pc) {
        //std::vector<std::string> v;
        transitions.push_back(temp);
        temp.clear();
    });
    /*
    state.set_action([&transitions,&states](parser_context &pc) {
        states.push_back(transitions);
    }
     */
    // now the data structures we are going to fill
    std::stringstream sst(
            "<state id=\"s\">\n"
            "<transition\n"
            "event=\"e1\"\n"
            "target=\"s1\"\n"
            "/>\n"
            "<transition\n"
            "event=\"e2\"\n"
            "target=\"s2\"\n"
            "/>\n"
            "<transition\n"
            "event=\"e3\"\n"
            "target=\"s3\"\n"
            "/>\n"
            "</state>"
    );
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    std::cout << "Parser status : " << std::boolalpha << f << std::endl;
    if (!f) {
        std::cout << pc.get_formatted_err_msg() << std::endl;
    }


    //auto *s = new State("s");
    cout << "la taille : " << transitions.size() << endl;


    /*
    for (const auto &x : transitions) {
        std::cout << "-----------" << std::endl;
        std::cout << "event: " << x.event << std::endl;
        //std::cout << "cond: " << x.cond << std::endl;
        std::cout << "target: " << x.target << std::endl;
        s->addTransition(*new Transition(new Event(x.event), new State(x.target)));
    }
     */
    auto *ct = new Context(s);
    ct->work();
}