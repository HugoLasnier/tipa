/**
 * 
*/

#ifndef __JSON_HPP__
#define __JSON_HPP__

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

#include <tinyparser.hpp>

using namespace std;
using namespace tipa;

class Value {
    public:
        virtual string toString();
        virtual ~Value() {}
};

class IntValue : public Value {
private:
    int n;
public: 
    virtual string toString();
    IntValue(int n);
};

class BoolValue : public Value {
private:
    bool b;
public: 
    virtual string toString();
    BoolValue(bool b);
};

class FloatValue : public Value {
private:
    float f;
public: 
    virtual string toString();
    FloatValue(float f);
};

class StringValue : public Value {
private:
    string s;
public:
    virtual string toString();
    StringValue(string s);
};

class NullValue : public Value {
public:
    virtual string toString();
};

class ArrayValue : public Value {
    private:
        vector<shared_ptr<Value>> values;

    public:
        virtual string toString();
        ArrayValue(vector<shared_ptr<Value>> val);
};

class ObjectValue : public Value {
    private:
        map<string, shared_ptr<Value>> keysValues;

    public:

        virtual string toString();

        ObjectValue(map<string, shared_ptr<Value>> kv);
};


class builder {
    stack<ObjectValue> objectsStack;
    stack<string> st1;
    stack< shared_ptr<Value> > st2;
    map<string, shared_ptr<Value>> js;

public:

    void make_Key(parser_context &pc);

    void make_member(parser_context &pc);
    
    void make_StringValue(parser_context &pc);

    void make_NullValue(parser_context &pc);

    void make_IntValue(parser_context &pc);

    void make_FloatValue(parser_context &pc);

    void make_BoolValue(parser_context &pc);

    void make_ArrayValue(parser_context &pc);

    void make_ObjectValue(parser_context &pc);

    void printContent();
};

class json{
public:
    // token
    const token tk_null = create_lib_token("^null");
  	const token tk_true = create_lib_token("^true");
    const token tk_false = create_lib_token("^false");
    const token tk_float = create_lib_token("[+-]?([0-9]*[.])[0-9]+");

    //data types

    rule r_element;
    rule r_elements;
    rule r_number;
    rule r_float;
    rule r_boolean;
    rule r_null;
    rule r_string;
    rule r_key;
	rule r_array;
	rule r_menber;
    rule r_menbers;
    rule r_object;
    rule root;

    json();
    bool parsejs(istream &in);


    /*
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    b.printContent();
    cout << "Parser status : " << boolalpha << f << endl;
    if (!f) {
        cout << pc.get_formatted_err_msg() << endl;
    }*/
};
#endif