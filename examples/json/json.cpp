#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

#include <json.hpp>
#include <tinyparser.hpp>

using namespace std;
using namespace tipa;

/** example of json :

    todo
*/

string Value::toString(){return "value";}

string IntValue::toString(){return to_string(this->n);}

IntValue::IntValue(int n){this->n = n;}

string BoolValue::toString(){return this->b ? "true" : "false";}

BoolValue::BoolValue(bool b){ this->b = b; }

string FloatValue::toString(){return to_string(this->f);}

FloatValue::FloatValue(float f){this->f = f;}

string StringValue::toString(){ return this->s;}
StringValue::StringValue(string s){this->s = s;}

string NullValue::toString(){ return "null";}

string ArrayValue::toString(){
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

ArrayValue::ArrayValue(vector<shared_ptr<Value>> val){this->values = val;}

string ObjectValue::toString(){
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

ObjectValue::ObjectValue(map<string, shared_ptr<Value>> kv){
    this->keysValues = kv;
}


void builder::make_Key(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    st1.push(v);
}

void builder::make_member(parser_context &pc){
    string key = st1.top(); st1.pop();
    auto val = st2.top(); st2.pop();
    js[key] = val;
}
    
void builder::make_StringValue(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    auto sv = make_shared<StringValue>(v);
    st2.push(sv);
}

void builder::make_NullValue(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    string v = x[x.size() - 1].second;
    auto nv = make_shared<NullValue>();
    st2.push(nv);
}

void builder::make_IntValue(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    int v = atoi(x[x.size()-1].second.c_str());
    auto iv = make_shared<IntValue>(v);
    st2.push(iv);
}

void builder::make_FloatValue(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    float v = stof(x[x.size()-1].second.c_str());
    auto fv = make_shared<FloatValue>(v);
    st2.push(fv);
}

void builder::make_BoolValue(parser_context &pc){
    auto x = pc.collect_tokens();
    if (x.size() < 1) throw string("Error in collecting variable");
    bool b = "true" == x[x.size() - 1].second;
    auto bv = make_shared<BoolValue>(b);
    st2.push(bv);
}

void builder::make_ArrayValue(parser_context &pc){
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

void builder::make_ObjectValue(parser_context &pc){
    auto ov = make_shared<ObjectValue>(js);
    st2.push(ov);
}

void builder::printContent(){
    map<string, shared_ptr<Value>>::iterator it;
    for( it = js.begin(); it != js.end(); it++ ){
        cout << it->first << ":" << it-> second->toString() << endl;
    }
}


//int main(int argc, char *argv[]){

json::json(){
    r_number = rule(tk_int);
    r_float = rule(tk_float);
    r_boolean = rule (tk_true) | rule(tk_false); // | rule("false");
    r_null = rule(tk_null); //rule r_null = rule("null");
    r_string = rule("\"") >> rule(tk_ident) >> rule("\"");
    r_key = rule("\"") >> rule(tk_ident) >> rule("\"") >> rule(":");
	r_array = rule(tk_op_sq)>> r_elements  >> rule(tk_cl_sq);
	r_menber = r_key >> r_element;
    r_menbers = *(r_menber >> rule(tk_comma)) >> r_menber;
    r_object = (rule(tk_op_br) >> r_menbers >> rule(tk_cl_br)) | rule(tk_op_br) >> rule(tk_cl_br);
    r_element = (r_object | r_array | r_null | r_boolean | r_string | r_float | r_number);
    r_elements = r_element >> *(rule(tk_comma) >> r_element);
    root =  r_object;
}

bool json::parsejs(istream &in){

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
    pc.set_stream(in);

    bool f = parse_all(root, pc);
    b.printContent();
    cout << "Parser status : " << boolalpha << f << endl;
    if (!f) {
        cout << pc.get_formatted_err_msg() << endl;
    }
    return f;
}
