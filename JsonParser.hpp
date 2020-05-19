#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <initializer_list>
#include <cmath>
#include <map>
#include <exception>
using namespace std;

enum class JsonObjType{
    UNKNOWN,
    INT,
    FLOAT,
    STRING,
    BOOL,
    NULL_T,
    ARRAY,
    OBJECT
};

static void PrintSomeTabs(int tab_num){
    for(int i=0;i<tab_num;i++)
        cout<<"\t";
}

class JsonParseException : public logic_error{
public:
    JsonParseException(const string msg):logic_error(msg){}
};

class JsonObject{
public:
    virtual bool IsType(JsonObjType type){
        return type==JsonObjType::UNKNOWN;
    }

    virtual int ToInt(){ throw JsonParseException("unmatched type"); }
    virtual float ToFloat(){ throw JsonParseException("unmatched type"); }
    virtual string ToString(){ throw JsonParseException("unmatched type"); }
    virtual bool ToBool(){ throw JsonParseException("unmatched type"); }
    virtual nullptr_t ToNull(){ throw JsonParseException("unmatched type"); }
    virtual vector<JsonObject*>& ToVector(){ throw JsonParseException("unmatched type"); }
    virtual map<string, JsonObject*>& ToMap(){ throw JsonParseException("unmatched type"); }

    virtual void SetInt(int i){ throw JsonParseException("unmatched type"); }
    virtual void SetBool(bool b){ throw JsonParseException("unmatched type"); }
    virtual void SetString(string s){ throw JsonParseException("unmatched type"); }
    virtual void SetFloat(float f){ throw JsonParseException("unmatched type"); }
    virtual void AddElement(JsonObject* obj){ throw JsonParseException("unmatched type"); }
    virtual void AddKeyValue(string key, JsonObject* obj){ throw JsonParseException("unmatched type"); }
    virtual void Clear(){ throw JsonParseException(" unmatched type"); }

    virtual size_t GetSize(){ throw JsonParseException("unmatched type"); }
    virtual JsonObject* GetElement(int idx){ throw JsonParseException("unmatched type"); }
    virtual JsonObject* GetValue(string key){ throw JsonParseException("unmatched type"); }

    virtual void Print(int tab_num = 0){ throw JsonParseException("unmatched type"); }
};

class IntJsonObj: public JsonObject{
public:
    IntJsonObj():value(0){}
    IntJsonObj(int i):value(i){}
    int ToInt() override{ return value; }
    void SetInt(int i) override { value = i; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::INT; }
    int Get(){ return value; }
    void Clear() override { value = 0; }
    void Print(int tab_num = 0) override { 
        PrintSomeTabs(tab_num);
        cout<<value; 
    }
private:
    int value;
};

class FloatJsonObj: public JsonObject{
public:
    FloatJsonObj():value(0){}
    FloatJsonObj(float f):value(f){}
    float ToFloat() override{ return value; }
    void SetFloat(float f) override { value = f; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::FLOAT; }
    float Get(){ return value; }
    void Clear() override { value = 0; }
    void Print(int tab_num = 0) override {
        PrintSomeTabs(tab_num);
        cout<<value; 
    }
private:
    float value;
};

class BoolJsonObj: public JsonObject{
public:
    BoolJsonObj():value(false){}
    BoolJsonObj(bool b):value(b){}
    bool ToBool() override{ return value; }
    void SetBool(bool b) override { value = b; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::BOOL; }
    bool Get(){ return value; }
    void Clear() override { value = false; }
    void Print(int tab_num = 0) override {
        PrintSomeTabs(tab_num);
        cout<<boolalpha<<value; 
    }
private:
    bool value;
};

class StringJsonObj: public JsonObject{
public:
    StringJsonObj() = default;
    StringJsonObj(string s):value(s){}
    string ToString() override { return value; }
    void SetString(string s) override { value = s; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::STRING; }
    string Get(){ return value; }
    void Clear() override { value.clear(); }
    void Print(int tab_num = 0) override {
        PrintSomeTabs(tab_num);
        cout<<"\""<<value<<"\""; 
    }
private:
    string value;

};

class NullJsonObj: public JsonObject{
public:
    NullJsonObj() = default;
    nullptr_t ToNull() override { return nullptr; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::NULL_T; }
    nullptr_t Get(){ return nullptr; }
    void Clear() override {}
    void Print(int tab_num = 0) override {
        PrintSomeTabs(tab_num);
        cout<<"null"; 
    }
};

class ObjectJsonObj;
class ArrayJsonObj;

JsonObject* CopyToPtr(JsonObject* obj);
void ReleaseJsonObj(JsonObject* obj);

class ArrayJsonObj: public JsonObject{
public:
    ArrayJsonObj() = default;
    ArrayJsonObj(vector<JsonObject*> objects){
        for(JsonObject* obj : objects)
            AddElement(obj);
    }
    ArrayJsonObj(initializer_list<JsonObject*> objects){
        for(auto it=objects.begin();it!=objects.end();it++)
            AddElement(*it);
    }
    ArrayJsonObj(const ArrayJsonObj& oth){
        for(JsonObject* obj : oth.objs)
            AddElement(obj);
    }
    vector<JsonObject*>& ToVector() override { return objs; }
    bool IsType(JsonObjType type) override { return type==JsonObjType::ARRAY; }
    void AddElement(JsonObject* obj) override {
        if(obj->IsType(JsonObjType::ARRAY)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::BOOL)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::FLOAT)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::INT)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::NULL_T)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::STRING)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::ARRAY)){
            objs.push_back(CopyToPtr(obj));
        }else if(obj->IsType(JsonObjType::OBJECT)){
            objs.push_back(CopyToPtr(obj));
        }
    }
    vector<JsonObject*>& Get(){ return objs; }
    size_t GetSize() override {
        return objs.size();
    }
    JsonObject* GetElement(int idx) override{
        return objs.at(idx);
    }
    void Clear() override{
        for(JsonObject* obj : objs){
            ReleaseJsonObj(obj);
        }
        objs.clear();
    }
    void Print(int tab_num = 0) override {
        PrintSomeTabs(tab_num);
        cout<<"[ ";
        for(JsonObject* obj : objs){
            obj->Print();
            cout<<", ";
        }
        cout<<" ]";
    }
    ~ArrayJsonObj(){
        Clear();
    }
private:
    vector<JsonObject*> objs;
};

class ObjectJsonObj: public JsonObject{
    public:
        ObjectJsonObj() = default;
        ObjectJsonObj(map<string, JsonObject*>& objs){
            for(auto it=objs.begin();it!=objs.end();it++)
                AddKeyValue(it->first, it->second);
        }
        void Clear() override {
            for(auto it=objs.begin();it!=objs.end();it++)
                ReleaseJsonObj(it->second);
            objs.clear();
        }
        map<string, JsonObject*>& ToMap() override { return objs; }
        bool IsType(JsonObjType type) override { return type==JsonObjType::OBJECT; }
        JsonObject* GetValue(string key) override { return objs.at(key); }
        void AddKeyValue(string key, JsonObject* obj) override {
            if(obj->IsType(JsonObjType::ARRAY)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::BOOL)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::FLOAT)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::INT)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::NULL_T)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::STRING)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::ARRAY)){
                objs[key] = CopyToPtr(obj);
            }else if(obj->IsType(JsonObjType::OBJECT)){
                objs[key] = CopyToPtr(obj);
            }
        }
        size_t GetSize() override { return objs.size(); }
        void Print(int tab_num = 0) override {
            PrintSomeTabs(tab_num);
            cout<<"{"<<endl;
            for(auto it=objs.begin();it!=objs.end();it++){
                PrintSomeTabs(tab_num+1);
                cout<<"'"<<it->first<<"' : ";
                it->second->Print();
                cout<<","<<endl;
            }
            PrintSomeTabs(tab_num);
            cout<<"}";
        }
        ~ObjectJsonObj(){
            Clear();
        }
    private:
        map<string, JsonObject*> objs;
};

JsonObject* CopyToPtr(JsonObject* obj){
    if(obj->IsType(JsonObjType::NULL_T)){
        return new NullJsonObj;
    }else if(obj->IsType(JsonObjType::BOOL)){
        return new BoolJsonObj(obj->ToBool());
    }else if(obj->IsType(JsonObjType::INT)){
        return new IntJsonObj(obj->ToInt());
    }else if(obj->IsType(JsonObjType::FLOAT)){
        return new FloatJsonObj(obj->ToFloat());
    }else if(obj->IsType(JsonObjType::STRING)){
        return new StringJsonObj(obj->ToString());
    }else if(obj->IsType(JsonObjType::ARRAY)){
        return new ArrayJsonObj(obj->ToVector());
    }else if(obj->IsType(JsonObjType::OBJECT)){
        return new ObjectJsonObj(obj->ToMap());
    }
}

void ReleaseJsonObj(JsonObject* obj){
    if(obj->IsType(JsonObjType::ARRAY))
        delete (ArrayJsonObj*)obj;
    else if(obj->IsType(JsonObjType::INT))
        delete (IntJsonObj*)obj;
    else if(obj->IsType(JsonObjType::FLOAT))
        delete (FloatJsonObj*)obj;
    else if(obj->IsType(JsonObjType::OBJECT))
        delete (ObjectJsonObj*)obj;
    else if(obj->IsType(JsonObjType::BOOL))
        delete (BoolJsonObj*)obj;
    else if(obj->IsType(JsonObjType::STRING))
        delete (StringJsonObj*)obj;
    else if(obj->IsType(JsonObjType::NULL_T))
        delete (NullJsonObj*)obj;
    else if(obj->IsType(JsonObjType::UNKNOWN))
        delete obj;
}

class JsonParser{
public:
    JsonParser():root(nullptr){};
    JsonParser(string text):cur_pos(0),root(nullptr){
        Parse(text);
    }
    void Parse(string json_context){
        context = json_context;
        if(root)
            delete root;
        root = parse();
    }
    JsonObject* GetRoot(){ return root; }
    ~JsonParser(){
        if(root->IsType(JsonObjType::ARRAY))
            delete (ArrayJsonObj*)root;
        else if(root->IsType(JsonObjType::INT))
            delete (IntJsonObj*)root;
        else if(root->IsType(JsonObjType::FLOAT))
            delete (FloatJsonObj*)root;
        else if(root->IsType(JsonObjType::OBJECT))
            delete (ObjectJsonObj*)root;
        else if(root->IsType(JsonObjType::BOOL))
            delete (BoolJsonObj*)root;
        else if(root->IsType(JsonObjType::STRING))
            delete (StringJsonObj*)root;
        else if(root->IsType(JsonObjType::NULL_T))
            delete (NullJsonObj*)root;
        else if(root->IsType(JsonObjType::UNKNOWN))
            delete root;
    }
private:
    int cur_pos;
    string context;
    JsonObject* root;
    char cur_char(){ 
        if(cur_pos>=context.size())
            return EOF;
        return context.at(cur_pos); 
    }
    char next(int step = 1){ 
        cur_pos+=step; 
        if(cur_pos>=context.size()){
            return EOF;
        }
        //cout<<"call next:"<<context.at(cur_pos-step)<<endl;
        return context.at(cur_pos-step);
    }
    void back(int step = 1){ 
        cur_pos-=step; 
        if(cur_pos<0)
            cur_pos = 0;
    }
    void ignoreWhiteChar(){
        //cout<<endl<<"ignored white char"<<endl;
        char c = cur_char();
        while(true){
            if(c==EOF)
                break;
            if(c==' '||c=='\n'||c=='\r'||c=='\t'){
                next();
                c = cur_char();
            }else{
                break;
            }
        }
    }
    int parseInt(){
        //cout<<endl<<"parse Int"<<endl;
        int num = 0;
        char sign = 1;
        char c = next();
        if(c=='-'){
            sign = -1;
            c = next();
        }
        while(c>='0' && c<='9'){
            num = num*10+(c-'0');
            c = next();
        }
        back();
        return num*sign;
    }
    float parseFloatPortion(char sign){
        //cout<<endl<<"parse Float"<<endl;
        float float_portion = 0;
        char c = next();
        int bits = 0;
        while(c>='0' && c<='9'){
            bits++;
            float_portion = float_portion*10+(c-'0');
            c = next();
        }
        back();
        return sign*float_portion/pow(10, bits);
    }
    string parseString(){
        //cout<<endl<<"parse String"<<endl;
        next(); //ignore left " or '
        string str = ""; 
        char c = next();
        while(c!='"'){
            str += c;
            c = next();
        }
        return str;
    }
    bool parseBool(){
        //cout<<endl<<"parse Bool"<<endl;
        char c = cur_char();
        if(c=='t'){
        if(next()=='t' && next()=='r' && next()=='u' && next()=='e')
            return true;
        }else if(c=='f'){
            if(next()=='f' && next()=='a' && next()=='l' && next()=='s' && next()=='e')
                return false;
        }
        throw JsonParseException("parse bool failed");
    }
    NullJsonObj* parseNull(){
        //cout<<endl<<"parse Null"<<endl;
        if(next()=='n' && next()=='u' && next()=='l' && next()=='l')
            return new NullJsonObj();
        throw JsonParseException("pase null failed");
    }
    ArrayJsonObj* parseArray(){
        //cout<<endl<<"parse Array"<<endl;
        ArrayJsonObj* arrobj = new ArrayJsonObj;
        next(); //ignore left [
        char c = cur_char();
        while(c!=']'){
            ignoreWhiteChar();
            JsonObject* obj = parse();
            arrobj->AddElement(obj);
            //cout<<"parsed element in Array:";
            //obj->Print();
            //cout<<endl;
            ignoreWhiteChar();
            if(cur_char()==','){
                next();
            }
            c = cur_char();
        }
        next();
        return arrobj;
    }
    ObjectJsonObj* parseObject(){
        next(); //ignore left {
        char c = cur_char();
        ObjectJsonObj* obj = new ObjectJsonObj;
        while(c!='}'){
            ignoreWhiteChar();
            string key = parseString();
            ignoreWhiteChar();
            if(cur_char()==':')
                next();
            ignoreWhiteChar();
            JsonObject* value = parse();
            obj->AddKeyValue(key, value);
            ignoreWhiteChar();
            if(cur_char()==',')
                next();
            ignoreWhiteChar();
            c = cur_char();
        }
        next();
        return obj;
    }
    JsonObject* parse(){
        unsigned int state = 0;
        JsonObject* obj = nullptr;
        char c;
        while(1){
            switch(state){
                case 0: //judge current space
                    c = cur_char();
                    if(c==EOF)
                        throw JsonParseException("parse failed, exists format error");
                    if(c==' '||c=='\n'||c=='\r'||c=='\t')
                        state = 1;
                    if(c=='-'||c=='+'||(c>='0'&&c<='9'))
                        state = 2;
                    else if(c=='t' || c=='f')
                        state = 3;
                    else if(c=='"')
                        state = 4;
                    else if(c=='[')
                        state = 5;
                    else if(c=='{')
                        state = 6;
                    else if(c=='n')
                        state = 7;
                    else
                        throw JsonParseException(string("parsed unexcept char ")+c);
                    break;
                case 1: //ignore all white char
                    ignoreWhiteChar();
                    break;
                case 2:{ //is number;
                    int int_portion = parseInt();
                    if(next()=='.'){
                        float float_portion = parseFloatPortion(int_portion>=0?1:-1);
                        return new FloatJsonObj(int_portion+float_portion);
                    }else
                        return new IntJsonObj(int_portion);
                    break;
                       }
                case 3: //is bool;
                    return new BoolJsonObj(parseBool());
                case 4: //is string;
                    return new StringJsonObj(parseString());
                case 5: //is array
                    return parseArray();
                case 6: //is object
                    return parseObject();
                case 7: //is null
                    return parseNull();
            }
        }
        return nullptr;
    }
};

#endif
