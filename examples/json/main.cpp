#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

#include "json.hpp"
#include <tinyparser.hpp>

using namespace std;
using namespace tipa;

int main(int argc, char *argv[]){

    stringstream sst(
        "{"
        "\"anObject\" : {\"a\" : 14, \"b\": 15},"
        "\"Array\" : [ [1,2,3], 4, 8 ],"
        "\"Array2\" : [ [99, 100]],"
        "\"aString\" : \"Hello\","
        "\"a1\" : 1,"
        "\"b2\" : 25,"
        "\"c3\" : 3,"
        "\"booleanKey\" : true,"
        "\"bkey2\" : false,"
        "\"nullKey\" : null,"
        "\"Pi\" : 3.14"
        "}"
    );


    json js = json();
    js.parsejs(sst);
}