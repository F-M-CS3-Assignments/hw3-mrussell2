#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <sstream>
#include <vector>


// I READ THE THREE NOTES AT THE TOP OF THE ASSIGNMENT

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

    // Ensure there are enough columns before accessing index 4
    if (launchInfo.size() <= 4) {
        return TimeCode(0, 0, 1); // Use an invalid TimeCode indicator
    }

    string timestr = launchInfo[4];
    
    vector<string> timeVec = split(timestr, ' ');

    if (timeVec.size() < 3 ){
        return TimeCode(0,0,1);
    }
    vector<string> MinSec = split(timeVec[2], ':');

    return TimeCode(stoi(MinSec[0]),stoi(MinSec[1]),0 );
    
    
}

int main(){
    ifstream file;

    file.open("Space_Corrected.csv");

    if(!file.is_open()){
        cout << "Could not open the file" << endl;
        return 1;
    }

    vector<TimeCode> Launches;
    string line; // holds line 
    getline(file,line); //skips the header line

   
    while(getline(file,line)){
        
        TimeCode tc = parse_line(line);

        if (!(tc.GetHours() == 0 && tc.GetMinutes() == 0 && tc.GetSeconds() == 1)) {
            Launches.push_back(tc);
        }

        
        
    }

    file.close();

// find average and number of data points
    TimeCode total(0,0,0);
    for (TimeCode tc : Launches){
        total = total + tc;
    }
    
    TimeCode avg = total / static_cast<double>(Launches.size());
    cout << Launches.size() << " data points." << endl;
    cout << "AVERAGE: " << avg.ToString() << endl;

return 0;
}