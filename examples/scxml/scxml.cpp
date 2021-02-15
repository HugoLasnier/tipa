#include <string>
#include <iostream>
#include "vector"
#include <scxml.h>

using namespace tipa;
using namespace std;

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
    //r_transition.set_action(std::bind(&builder::make_Transition,&b, _1));
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
}