#include "JsonParser.hpp"
#include "test.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    TestHead("IntJsonObj");
    IntJsonObj intobj(3);
    assert(intobj.IsType(JsonObjType::INT));
    assert(intobj.ToInt()==3);
    intobj.Clear();
    assert(intobj.ToInt()==0);
    intobj.Print();
    cout<<endl;

    TestHead("FloatJsonObj");
    FloatJsonObj floatobj(4.1234);
    assert(floatobj.IsType(JsonObjType::FLOAT));
    assert(floatobj.ToFloat()==4.1234f);
    floatobj.Clear();
    assert(floatobj.ToFloat()==0);
    floatobj.Print();
    cout<<endl;

    TestHead("StringJsonObj");
    StringJsonObj strobj("Hello World");
    assert(strobj.IsType(JsonObjType::STRING));
    assert(strobj.ToString()=="Hello World");
    strobj.Print();
    cout<<endl;

    TestHead("BoolJsonObj");
    BoolJsonObj boolobj(true);
    assert(boolobj.IsType(JsonObjType::BOOL));
    assert(boolobj.ToBool());
    boolobj.Print();
    cout<<endl;

    TestHead("NullJsonObj");
    NullJsonObj nullobj;
    assert(nullobj.IsType(JsonObjType::NULL_T));
    assert(nullobj.ToNull()==nullptr);
    nullobj.Print();
    cout<<endl;

    TestHead("ArrayJsonObj");
    ArrayJsonObj arrayobj;
    intobj.SetInt(12);
    floatobj.SetFloat(13.5);
    arrayobj.AddElement(&intobj);
    arrayobj.AddElement(&floatobj);
    arrayobj.AddElement(&strobj);
    assert(arrayobj.IsType(JsonObjType::ARRAY));
    assert(arrayobj.GetElement(0)->ToInt()==12);
    assert(arrayobj.GetElement(1)->ToFloat()==13.5f);
    assert(arrayobj.GetElement(2)->ToString()=="Hello World");
    arrayobj.Print();
    cout<<endl;

    TestHead("ObjectJsonObject");
    ObjectJsonObj objobj;
    objobj.AddKeyValue("int", &intobj);
    objobj.AddKeyValue("float", &floatobj);
    objobj.AddKeyValue("string", &strobj);
    assert(objobj.GetValue("int")->ToInt()==12);
    assert(objobj.GetValue("float")->ToFloat()==13.5f);
    assert(objobj.GetValue("string")->ToString()=="Hello World");
    objobj.Print();
    cout<<endl;

    return 0;
}
