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


/** example of json :

    todo
*/


class Value {
    public:
        virtual string toString(){return "value";};
        virtual ~Value() {}
};

class IntValue : public Value {
private:
    int n;
public: 
    virtual string toString(){ return to_string(this->n);}
    IntValue(int n){ this->n = n; }
};

class BoolValue : public Value {
private:
    bool b;
public: 
    virtual string toString(){ return this->b ? "true" : "false";}
    BoolValue(bool b){ this->b = b; }
};

class FloatValue : public Value {
private:
    float f;
public: 
    virtual string toString(){ return to_string(this->f);}
    FloatValue(float f){this->f = f;}
};

class StringValue : public Value {
private:
    string s;
public:
    virtual string toString(){ return this->s;}
    StringValue(string s){this->s = s;}
};

class NullValue : public Value {
public:
    virtual string toString(){ return "null";}
};

class ArrayValue : public Value {
    private:
        vector<shared_ptr<Value>> values;

    public:
        virtual string toString(){
            vector< shared_ptr<Value> >::iterator itr = values.begin();
            string res = "[";
            while(itr != values.end())
            {
                if(itr != values.begin()) res += ",";
                res += (*itr)->toString();
                itr++;
            }
            res += "]";
            return res;
        }

        
        ArrayValue(vector<shared_ptr<Value>> val){
            this->values = val;
        }
};

class ObjectValue : public Value {
    private:
        map<string, shared_ptr<Value>> keysValues;

    public:

        virtual string toString(){
            string res = "{ ";
            map<string, shared_ptr<Value>>::iterator it;
            for( it = this->keysValues.begin(); it != this->keysValues.end(); it++ ){
                if(it != this->keysValues.begin()) res += ", ";
                res += it->first;
                res += ":";
                res += it-> second->toString();
            }
            return res + " }";
        }

        ObjectValue(map<string, shared_ptr<Value>> kv){
            this->keysValues = kv;
        }
};


class builder {
    stack<ObjectValue> objectsStack;
    stack<string> st1;
    stack< shared_ptr<Value> > st2;
    map<string, shared_ptr<Value>> js;

public:

    void make_Key(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        string v = x[x.size() - 1].second;
        st1.push(v);
    }

    void make_member(parser_context &pc){
        string key = st1.top(); st1.pop();
        auto val = st2.top(); st2.pop();
        js[key] = val;
    }
    
    void make_StringValue(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        string v = x[x.size() - 1].second;
        auto sv = make_shared<StringValue>(v);
        st2.push(sv);
    }

    void make_NullValue(parser_context &pc){
    	auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        string v = x[x.size() - 1].second;
        auto nv = make_shared<NullValue>();
        st2.push(nv);
    }

    void make_IntValue(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        int v = atoi(x[x.size()-1].second.c_str());
        auto iv = make_shared<IntValue>(v);
        st2.push(iv);
    }

    void make_FloatValue(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        float v = stof(x[x.size()-1].second.c_str());
        auto fv = make_shared<FloatValue>(v);
        st2.push(fv);
    }

    void make_BoolValue(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        bool b = "true" == x[x.size() - 1].second;
        auto bv = make_shared<BoolValue>(b);
        st2.push(bv);
    }

    void make_ArrayValue(parser_context &pc){
        auto x = pc.collect_tokens();
        if (x.size() < 1) throw string("Error in collecting variable");
        vector<shared_ptr<Value>> v;
        while(! st2.empty()){
            v.insert(v.begin(), st2.top());
            st2.pop();
        }
        auto nv = make_shared<ArrayValue>(v);
        st2.push(nv);
    }

    void make_ObjectValue(parser_context &pc){
        auto ov = make_shared<ObjectValue>(js);
        st2.push(ov);

    }

    void printContent(){
        map<string, shared_ptr<Value>>::iterator it;

        for( it = js.begin(); it != js.end(); it++ ){
            cout << it->first << ":" << it-> second->toString() << endl;
        }
    }
};

int main(int argc, char *argv[]){

	// token
    const token tk_null = create_lib_token("^null");
  	const token tk_true = create_lib_token("^true");
    const token tk_false = create_lib_token("^false");
    const token tk_float = create_lib_token("[+-]?([0-9]*[.])[0-9]+");

    //data types

    rule r_element;
    rule r_elements;
    rule r_number = rule(tk_int);
    rule r_float = rule(tk_float);
    rule r_boolean = rule (tk_true) | rule(tk_false); // | rule("false");
    rule r_null = rule(tk_null); //rule r_null = rule("null");
    rule r_string = rule("\"") >> rule(tk_ident) >> rule("\"");
    rule r_key = rule("\"") >> rule(tk_ident) >> rule("\"") >> rule(":");
	rule r_array = rule(tk_op_sq)>> r_elements  >> rule(tk_cl_sq);
	rule r_menber = r_key >> r_element;
    rule r_menbers = *(r_menber >> rule(tk_comma)) >> r_menber;
    rule r_object = (rule(tk_op_br) >> r_menbers >> rule(tk_cl_br)) | rule(tk_op_br) >> rule(tk_cl_br);
    r_element = (r_object | r_array | r_null | r_boolean | r_string | r_float | r_number);
    r_elements = r_element >> *(rule(tk_comma) >> r_element);

    rule root =  r_object;
    
    //----------------  end of parser specification -------------

    // An example of json file to parse
    /*stringstream sst(
    	"{"
    	"\"aString\" : \"toto\","
    	"\"null\" : null,"
    	"\"Array\" : [1 , [1,2,3]],"
    	"\"aBool\" : true,"
    	"\"aBool2\" : false,"
    	"\"aNumber\" : 1234,"
    	"\"anObject\" : {\"aa\" : \"b\",\"b\" :  {}}"
    	"}"
    );*/

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

    builder b; 
    using namespace std::placeholders;
    r_null.   set_action(std::bind(&builder::make_NullValue,            &b, _1));
   	r_boolean.   set_action(bind(&builder::make_BoolValue,            &b, _1));
    r_float.   set_action(std::bind(&builder::make_FloatValue,            &b, _1));
    r_number.   set_action(std::bind(&builder::make_IntValue,            &b, _1));
    r_key.   set_action(bind(&builder::make_Key,            &b, _1));
    r_string.   set_action(bind(&builder::make_StringValue,            &b, _1));
    r_menber.   set_action(bind(&builder::make_member,            &b, _1));
    r_array.   set_action(bind(&builder::make_ArrayValue,            &b, _1));
    r_object.  set_action(bind(&builder::make_ObjectValue,            &b, _1));
    
    parser_context pc;
    pc.set_stream(sst);

    bool f = parse_all(root, pc);
    b.printContent();
    cout << "Parser status : " << boolalpha << f << endl;
    if (!f) {
        cout << pc.get_formatted_err_msg() << endl;
    }
}

