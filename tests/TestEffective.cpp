#include <iostream>
#include "JsonParser.hpp"
#include "test.hpp"
#include <ctime>
using namespace std;

int main(int argc, char** argv){
    if(argc==1)
        return 0;
    time_t t = time(nullptr);
    const int count = 10000;
    cout<<"parsing "<<argv[1]<<" "<<count<<" times..."<<endl;
    for(int i=0;i<count;i++){
        JsonParser parser(ReadJsonFromFile(argv[1]));
    }
    cout<<"use "<<time(nullptr)-t<<" s"<<endl;
    return 0;
}
