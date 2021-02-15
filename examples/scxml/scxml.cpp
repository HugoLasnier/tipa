#include <scxml.h>

using namespace tipa;
using namespace std;

void builder::make_Id(parser_context &pc) {
    depth++;
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    father = current_s;
    current_s = v;
    tab_s[nb_s].id = v;
    tab_s[nb_s].father = father;
    nb_s++;
}

void builder::make_Event(parser_context &pc) {
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    st1.push(v);
    tab_t[nb_t].e = v;
}

void builder::make_target(parser_context &pc) {
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    tab_t[nb_t].t = v;
}

void builder::make_Transition(parser_context &pc) {
    tab_t[nb_t].o = current_s;
    nb_t++;

}

void builder::make_EofState(parser_context &pc) {
    depth--;
    current_s = father;
}

void builder::printScxml() {
    cout << "---Les States---" << endl;
    for (int i = 0; i < nb_s; i++) {
        cout << "id : " << tab_s[i].id;
        cout << " || father : " << tab_s[i].father << endl;
    }
    cout << "---Les Transitions---" << endl;
    for (int i = 0; i < nb_t; i++) {
        cout << "origin : " << tab_t[i].o;
        cout << " || event : " << tab_t[i].e;
        cout << " || target : " << tab_t[i].t << endl;
    }
    cout << "---StateCharts---" << endl;
    for (int i = 0; i < nb_s; i++) {
        cout << "id : " << tab_s[i].id;
        cout << " || father : " << tab_s[i].father << endl;
        for (int j = 0; j < nb_t; j++) {
            if (tab_t[j].o == tab_s[i].id) {
                cout << "event : " << tab_t[j].e;
                cout << " target : " << tab_t[j].t << endl;
            }
        }
    }
}

void builder::stateChart() {
    string val;
    cout << "---Hello---" << endl << "please Enter value of id of the state : ";
    cin >> val;
    for (int i = 0; i < nb_s; ++i) {
        if (val == tab_s[i].id) {
            cout << "Welcome Sir" << endl;
            cout << "You are in " << endl;
            cout << "id : " << tab_s[i].id;
            cout << " || father : " << tab_s[i].father << endl;
            cout << "Here are the Transition : " << endl;
            for (int j = 0; j < nb_t; j++) {
                if (tab_t[j].o == tab_s[i].id) {
                    cout << "event : " << tab_t[j].e;
                    cout << " target : " << tab_t[j].t << endl;
                }
            }
            cout << "choose One from the follwing : ";
            cin >> val;
            for (int j = 0; j < nb_t; j++) {
                if (tab_t[j].o == tab_s[i].id && tab_t[j].e == val) {
                    cout << "You are in taget : " << tab_t[j].t << endl;
                }
            }
        }
    }
    cout << "End of the Program Thank You !";
}

scxml::scxml() {
    r_id = rule("id=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_event = rule("event=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_target = rule("target=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    r_transition = rule("<transition") >> r_event >> r_target >> r_eof_transition;
    r_property = r_transition | r_state;
    r_eof_state = rule("</state>");
    r_eof_transition = rule("</transition>");
    r_state = rule("<state ") >> r_id >> rule(">") >> *r_property >> r_eof_state;;
    root = *r_state;
}

bool scxml::parsescxml(istream &in) {
    builder b;
    using namespace std::placeholders;
    r_id.set_action(std::bind(&builder::make_Id, &b, _1));
    r_event.set_action(std::bind(&builder::make_Event, &b, _1));
    r_target.set_action(std::bind(&builder::make_target, &b, _1));
    r_transition.set_action(std::bind(&builder::make_Transition, &b, _1));
    r_state.set_action(std::bind(&builder::make_State, &b, _1));
    r_eof_state.set_action(std::bind(&builder::make_EofState, &b, _1));
    r_eof_transition.set_action(std::bind(&builder::make_EofTransition, &b, _1));
    parser_context pc;
    pc.set_stream(in);
    bool f = parse_all(root, pc);
    cout << "Parser status : " << boolalpha << f << endl;
    if (!f) {
        cout << pc.get_formatted_err_msg() << endl;
    }
    b.printScxml();
    b.stateChart();
    return f;
}