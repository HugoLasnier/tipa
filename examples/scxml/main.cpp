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
<<<<<<< HEAD
            "<state id=\"une\">\n"
            "<transition event=\"e1\"target=\"s1\"\n"
            "</transition>\n"
            "<state id=\"deux\">\n"
            "<transition event=\"e2\"target=\"s2\"\n"
            "</transition>\n"
            "</state>\n"
            "<state id=\"trois\">\n"
            "<transition event=\"e3\"target=\"s3\"\n"
            "</transition>\n"
            "</state>\n"
            "</state>\n"
            "<state id=\"quatre\">\n"
            "<transition event=\"e4\"target=\"s4\"\n"
            "</transition>\n"
=======
            "<state id=\"s\">\n"
            "<transition event=\"e1\"target=\"s1\"\n"
            "</transition>\n"
            "<state id=\"m\">\n"
            "<transition event=\"e2\"target=\"s2\"\n"
            "</transition>\n"
            "</state>\n"
>>>>>>> acc808fe418c53b8eb95feb5263f74d6484f88ba
            "</state>\n"
    );
    scxml sc = scxml();
    sc.parsescxml(sst);
}