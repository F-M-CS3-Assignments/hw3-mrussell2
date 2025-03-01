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


    string timestr = launchInfo[4];
    cout << timestr << endl;
    vector<string> timeVec = split(timestr, ' ');

    for (int i = 0; i< timeVec.size(); i++){
        cout << timeVec[i] << endl;
    }
    if (timeVec.size()<=3){
        return TimeCode();
    }
    vector<string> MinSec = split(timeVec[2], ':');
    return TimeCode(stoi(MinSec[0]),stoi(MinSec[1]),0 );
    
}

int main(){
    cout << "main entered" << endl;
    ifstream file;

    file.open("Space_Corrected_Short.csv");

    if(!file.is_open()){
        cout << "Could not open the file" << endl;
        return 1;
    }

    vector<TimeCode> Launches;
    string line; // holds line 
    getline(file,line); //skips the header line
    getline(file,line);
    while(!file.fail()){
        cout << line << endl;
        TimeCode tc = parse_line(line);
        Launches.push_back(tc);
        cout << tc.ToString() << endl;
        getline(file,line);
    }

    file.close();

    for (int i = 0; i< Launches.size(); i++){
        cout << Launches[i].ToString() << endl;
    }

    
cout << "SHORT TEST PASSED" << endl;

return 0;
}