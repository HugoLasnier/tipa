/*
  Copyright 2015-2018 Giuseppe Lipari
  email: giuseppe.lipari@univ-lille.fr
  
  This file is part of TiPa.

  TiPa is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  TiPa is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.
  
  You should have received a copy of the GNU General Public License
  along with TiPa. If not, see <http://www.gnu.org/licenses/>
 */

#include "catch.hpp"

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>

#include <json.hpp>
#include <tinyparser.hpp>

#include <stack>
#include <fstream>
#include <memory>
#include <tuple>
#include <map>

using namespace std;
using namespace tipa;

TEST_CASE("test that a json file is corectly", "[action]")
{
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

   //json js = json();
   //js.parsejs(sst);

}