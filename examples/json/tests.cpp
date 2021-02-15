#include <fstream>
#include <sstream>
#include <iostream>

#include "json.hpp"
#include <tinyparser.hpp>

using namespace std;

stringstream readFile(string filename){
    ifstream file( filename);
    stringstream sst;
    if ( file ){
        sst << file.rdbuf();
        file.close();
        return sst;
    }
    return sst;
}


void timeTest(string filename){
  json js = json();
  stringstream sst = readFile(filename);
  clock_t t = clock();
  js.parsejs(sst);
  cout << filename;
  printf("\ntest for Time taken: %.4fs\n", (float)(clock() - t)/CLOCKS_PER_SEC);
  printf("\n");
}

int main(int argc, char *argv[]){
  timeTest("example.txt");
  timeTest("foo.txt");
  return 0;
}