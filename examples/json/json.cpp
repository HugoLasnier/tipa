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

	// token
    const token tk_char = create_lib_token("^([0-9a-zA-Z]{1})");
    const token tk_digit = create_lib_token("^([0-9]{1})");

    //data types
    rule r_anyType;
    rule r_number = *rule(tk_digit);
    rule r_string = rule("\"") >> *rule(tk_char) >> rule("\"");
    rule r_boolean = rule ("true") | rule("false");
    rule r_null = rule("null");

	rule r_array = rule("[")>> *(r_anyType >> rule(",")) >> r_anyType >>rule("]");
	rule key_value = r_string >> rule(":") >> r_anyType;
    rule key_values = *(key_value >> rule(",")) >> key_value;
    rule r_object= (rule("{") >> key_values >> rule("}")) | rule("{") >> rule("}");

    r_anyType = (r_object | r_array | r_null | r_boolean | r_string | r_number);
    rule root = r_object;

    
    //----------------  end of parser specification -------------

    // An example of json file to parse
    std::stringstream sst(
    	"{"
    	"\"aString\" : \"toto\","
    	"\"null\" : null,"
    	"\"Array\" : [1 , [1,2,3]],"
    	"\"aBool\" : true,"
    	"\"aBool2\" : false,"
    	"\"aNumber\" : 1234,"
    	"\"anObject\" : {\"aa\" : \"b\",\"b\" :  {}}"
    	"}"
    );
    
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    std::cout << "Parser status : " << std::boolalpha << f << std::endl;
    if (!f) {
        std::cout << pc.get_formatted_err_msg() << std::endl;
    }
}
