#include <string>
#include <iostream>
#include "vector"
#include <tinyparser.hpp>
#include <scxml.h>
#include <sstream>
using namespace tipa;
using namespace std;
int main() {
    stringstream sst(
            "<state id=\"s\">\n"
            "<transition event=\"e1\"target=\"s1\"\n"
            "</transition>\n"
            "<state id=\"m\">\n"
            "<transition event=\"e2\"target=\"s2\"\n"
            "</transition>\n"
            "</state>\n"
            "</state>\n"
    );
    scxml sc = scxml();
    sc.parsescxml(sst);
}