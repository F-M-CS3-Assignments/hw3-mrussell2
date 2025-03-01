#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
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
        vector<string> MinSec = split(timeVec[4], ':');
        return TimeCode(stoi(MinSec[0]),stoi(MinSec[1]),0 );
        
    }
    
}

int main(){


    // Testing Split Function
    string s = "a,b,c,d,e";
    vector<string> splitTest = split(s, ',');
    assert(splitTest.size() == 5);
    assert(splitTest[0] == "a");
    assert(splitTest[1] == "b");
    assert(splitTest[2] == "c");
    assert(splitTest[3] == "d");
    assert(splitTest[4] == "e");

    s = "Space Falcon Tesla";
    splitTest = split(s, ' ');
    assert(splitTest.size() == 3);
    assert(splitTest[0] == "Space");
    assert(splitTest[1] == "Falcon");
    assert(splitTest[2] == "Tesla");

    cout << "SPLIT TESTS PASSED!" << endl;

return 0;
}