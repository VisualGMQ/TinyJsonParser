#include <iostream>
#include <fstream>
#include "JsonParser.hpp"
#include "test.hpp"
using namespace std;

int main(int argc, char** argv){
    for(int i=1;i<argc;i++){
        string jsontext = ReadJsonFromFile(argv[i]);
        cout<<endl<<"parse file "<<argv[i]<<endl;
        JsonParser parser(jsontext);
        JsonObject* root = parser.GetRoot();
        root->Print();
        cout<<endl;
    }
    return 0;
}
