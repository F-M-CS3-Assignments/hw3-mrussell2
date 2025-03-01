#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#include "TimeCode.h" // include TimeCode class

//helper function to split a string by a delimeter
vector<string> split(string str, char delim){
    vector<string> launchInfo;
    stringstream ss(str);
    string detail;
    while(getline(ss,detail,delim)){
        launchInfo.push_back(detail);
    }
    return launchInfo;
}

//helper function to take line from a string and return the TimeCode found in that line
TimeCode parse_line(string line){
    vector<string> launchInfo = split(line, ',');

    string timestr = launchInfo[3];
    vector<string> timeVec = split(timestr, ' ');
    if (timeVec.size()<=4){
        return TimeCode();
    }
    else{
        
    }

}

int main(){

    return 0;

}