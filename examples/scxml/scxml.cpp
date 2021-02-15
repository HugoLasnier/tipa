#include <string>
#include <iostream>
#include "vector"
#include <scxml.h>

using namespace tipa;
using namespace std;
<<<<<<< HEAD
void event::setId(const string &id) {
    event::id = id;
}

const string &event::getId() const {
    return id;
}

string Value::toString(){return "value";}

void builder::make_Id(parser_context &pc) {
    depth++;
    //cout << "entering new State" << endl;
    //cout << "depth is : " << depth << endl;
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    //cout << "My Id :" << v << endl;
    father = current_s;
    current_s = v;
    tab_s[nb_s].id = v;
    tab_s[nb_s].father = father;
    nb_s++;
    //vec_s.push_back()
}
void builder::make_Event(parser_context &pc) {
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    //cout << "My Event : " << v <<endl;
    st1.push(v);
    tab_t[nb_t].e = v;
}
void builder::make_target(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    //cout << "My Target : " << v << endl;
    tab_t[nb_t].t = v;
    //st1.push(v);
}
void builder::make_State(parser_context &pc) {
    //auto x = pc.collect_tokens();
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second.c_str();
    //int v = x[x.size()-1].second.size();
    //cout << v;
    //st1.push(v);
}
void builder::make_Transition(parser_context &pc) {
    //cout << "END of Transition" << endl;
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second;
    //cout << v;
    //st1.push(v);
    tab_t[nb_t].o = current_s;
    nb_t++;

}
void builder::make_EofState(parser_context &pc) {
    depth--;
    current_s = father;
    //cout << "END of State" << endl;
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second;
    //cout << v;
    //st1.push(v);
}
void builder::make_EofTransition(parser_context &pc){
    //cout << "END of Transition" << endl;
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second;
    //cout << v;
    //st1.push(v);
}
void builder::printScxml() {
    cout << "---Les States---" << endl;
    for(int i=0;i<nb_s;i++) {
        //cout << "state n : " << i+1 << endl;
        cout << "id : " << tab_s[i].id;
        cout << "|| father : " << tab_s[i].father << endl;
    }
    cout << "---Les Transitions---" << endl;
    for(int i=0;i<nb_t;i++) {
        //cout << "transition n : " << i+1 << endl;
        cout << "origin : " << tab_t[i].o;
        cout << "|| event : " << tab_t[i].e;
        cout << "|| target : " << tab_t[i].t << endl;
    }
    //cout << "depth is :" << depth << endl;
=======

string Value::toString(){return "value";}

void builder::make_Id(parser_context &pc) {
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    cout << "My Id :" << v << endl;
}
void builder::make_Event(parser_context &pc) {
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    cout << "My Event : " << v <<endl;
    st1.push(v);
}
void builder::make_target(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size()-1].second;
    cout << "My Target : " << v << endl;
    st1.push(v);
}
void builder::make_State(parser_context &pc) {
    //auto x = pc.collect_tokens();
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second.c_str();
    //int v = x[x.size()-1].second.size();
    //cout << v;
    //st1.push(v);
}
void builder::make_Transition(parser_context &pc) {
    cout << "END of Transition" << endl;
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second;
    //cout << v;
    //st1.push(v);
}
void builder::make_EofState(parser_context &pc) {
    cout << "END of State" << endl;
    //if (x.size() < 1) throw string("Error in collecting variable");
    //string v = x[x.size()-1].second;
    //cout << v;
    //st1.push(v);
}
void builder::make_EofTransition(parser_context &pc) {
    cout << "End of transition " << endl;
}
void builder::printScxml() {
>>>>>>> acc808fe418c53b8eb95feb5263f74d6484f88ba
}

scxml::scxml(){
    r_id = rule("id=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_event = rule("event=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_target = rule("target=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_transition = rule("<transition") >> r_event >> r_target >> r_eof_transition;
    r_property = r_transition | r_state;
    r_eof_state = rule("</state>");
    r_eof_transition = rule("</transition>");
    r_state = rule("<state ") >> r_id >> rule(">") >> *r_property >> r_eof_state;;
    root =  *r_state;
}

bool scxml::parsescxml(istream &in){
    builder b;
    using namespace std::placeholders;
    r_id.set_action(std::bind(&builder::make_Id,&b, _1));
    r_event.set_action(std::bind(&builder::make_Event,&b, _1));
    r_target.set_action(std::bind(&builder::make_target,&b, _1));
<<<<<<< HEAD
    r_transition.set_action(std::bind(&builder::make_Transition,&b, _1));
=======
    //r_transition.set_action(std::bind(&builder::make_Transition,&b, _1));
>>>>>>> acc808fe418c53b8eb95feb5263f74d6484f88ba
    r_state.set_action(std::bind(&builder::make_State,&b, _1));
    r_eof_state.set_action(std::bind(&builder::make_EofState,&b, _1));
    r_eof_transition.set_action(std::bind(&builder::make_EofTransition,&b, _1));
    parser_context pc;
    pc.set_stream(in);
    bool f = parse_all(root, pc);
    b.printScxml();
    cout << "Parser status : " << boolalpha << f << endl;
    if (!f) {
        cout << pc.get_formatted_err_msg() << endl;
    }
    return f;
<<<<<<< HEAD
}


=======
}
>>>>>>> acc808fe418c53b8eb95feb5263f74d6484f88ba
