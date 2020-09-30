#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>

#include <tinyparser.hpp>

using namespace tipa;


/** example of json :

    todo
*/

int main(int argc, char *argv[])
{
    const token tk_char = create_lib_token("^([0-9a-zA-Z]{1})");
    rule r_char = rule(tk_char);
    rule r_string = rule("\"") >> *r_char >> rule("\"");
    rule key_value = r_string >> rule(":") >> r_string;

    rule key_values = *(key_value >> rule(",")) >> key_value;
    rule bracket = (rule("{") >> key_values >> rule("}")) | rule("{") >> rule("}");

    rule root = *(bracket >> rule(",")) >> bracket;



    
    //----------------  end of parser specification -------------

    // An example of json file to parse
    std::stringstream sst(
    	"{"
         "\" key1 \" : \" val1 \","
        "\" key2 \" : \" val2 \","
        "\" key3 \" : \" val3 \""
        "},"
        "{"
        "\" key1 \" : \" val1 \""
        "},"
        "{}"
        
    );
    
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    std::cout << "Parser status : " << std::boolalpha << f << std::endl;
    if (!f) {
        std::cout << pc.get_formatted_err_msg() << std::endl;
    }
}
