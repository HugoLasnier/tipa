#include <scxml.h>

using namespace tipa;
using namespace std;

int main() {
    stringstream sst(
            "<state id=\"une\">\n"
            "<transition event=\"e1\"target=\"s1\"\n"
            "</transition>\n"
            "<transition event=\"e6\"target=\"s6\"\n"
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
            "<transition event=\"e5\"target=\"s5\"\n"
            "</transition>\n"
            "</state>\n"
    );
    scxml sc = scxml();
    sc.parsescxml(sst);
}