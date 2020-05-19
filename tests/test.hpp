#ifndef TEST_HPP
#define TEST_HPP
#include <iostream>
#include <string>
using namespace std;

#define assertm(exp, msg) assert((msg, exp))
#define TestHead(msg) cout<<"Begin Test "<<msg<<endl

static string ReadJsonFromFile(string filename){
    ifstream file(filename);
    if(file.fail()){
        cerr<<filename<<" not found"<<endl;
        exit(0);
    }
    string str((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    return str;
}

#endif
