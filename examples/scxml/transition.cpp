#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>

#include <tinyparser.hpp>

using namespace tipa;


/** example of SCXML :
        <transition 
            event="e" 
            cond="x==1" 
            target="s1"
        />
        <transition event="e" target="s2"/>
        <transition event="*" target="s3"/>
*/

int main(int argc, char *argv[])
{
    
    // First the grammar
    // this is an event 
    //Regex For Event
    rule event = rule("event=") >>  rule("\"") >> rule(tk_ident) >> rule("\"");
    // this is an cond 
    //Regex for Condition
    rule cond = rule("cond=") >> rule("\"") >> rule(tk_ident) >> rule("\"");
    // this is an target 
    rule target = rule("target=") >>  rule("\"") >> rule(tk_ident) >> rule("\"");     
   
    // a transition is any event, cond, target(none is required)
    rule property = event | cond | target;
    
    // a button has a name (a identifier), and a device name (another identifier), and a sequence of properties.
    rule transition = rule ("<transition") >> *property >> rule ("/>");
    // the whole file is just a list of buttons
    rule root = *transition;

    // now the data structures we are going to fill
    struct TransitionS {
        std::string event;
        std::string cond;
        std::string target;

        void clear() { event = ""; cond = ""; target = "";}
    };
    std::vector<TransitionS> transitions;

    TransitionS temp;
    // now the parser actions
    // when the parser finds a event, store the values in the temp variable
    event.read_vars(temp.event);
    // same for cond
    cond.read_vars(temp.cond);
    // same for target
    target.read_vars(temp.target);
    
    // when we detect a button, we store the temp variable in the vector of buttons
    transition.set_action([&temp, &transitions](parser_context &pc) {
            std::vector<std::string> v;
            transitions.push_back(temp);
            temp.clear();
        });
    
    //----------------  end of parser specification -------------

    // An example of css file to parse
    std::stringstream sst(
        "<transition\n"
        "event=\"e\"\n"
        "cond=\"x\"\n"
        "target=\"s1\"\n"
        "/>\n"
        "<transition\n"
        "event=\"e\"\n"
        "target=\"s2\"\n"
        "/>\n"
        "<transition\n"
        "event=\"a\"\n"
        "target=\"s3\"\n"
        "/>\n"
        );
    
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    std::cout << "Parser status : " << std::boolalpha << f << std::endl;
    if (!f) {
        std::cout << pc.get_formatted_err_msg() << std::endl;
    }
    
    for (auto x : transitions) {
        std::cout << "-----------" << std::endl;
        std::cout << "event: " << x.event << std::endl;
        std::cout << "cond: " << x.cond << std::endl;
        std::cout << "target: " << x.target << std::endl;

    }    
}
