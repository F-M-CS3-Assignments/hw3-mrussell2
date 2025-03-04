#include <iostream> // for cin and cout
#include <fstream> // for opening file
#include <string> // for strings
#include <sstream> // for stringstream
#include <vector> //for vectors

// I READ THE THREE NOTES AT THE TOP OF THE ASSIGNMENT

using namespace std;

#include "TimeCode.h" // include TimeCode class 

//helper function to split a string by a delimeter

vector<string> split(string str, char delim){
    vector<string> launchInfo; // create output vector that will hold strings split from original string
    stringstream ss(str);  // convert string str to stringstream ss
    string detail; 
    while(getline(ss,detail,delim)){ // get each string detail from ss seperated by the delim
        launchInfo.push_back(detail); // add each string detail to launchInfo
    }
    return launchInfo; // return vector of strings
}

//helper function to take line from a string and return the TimeCode found in that line
TimeCode parse_line(string line){
    vector<string> launchInfo = split(line, ','); // use split function to divide up the string making it easier to work with

    // Ensure there are enough columns before accessing index 4
    if (launchInfo.size() <= 4) { // if not enough values in launchInfo return TimeCode with only one second
        return TimeCode(0, 0, 1); // One second is used becuase the launch times do not have seconds and this allows us to 
                                    // later filter out these launches that do not have a TimeCode
    }

    string timestr = launchInfo[4]; // get the 5th string in launchInfo as this is what holds the time code
    vector<string> timeVec = split(timestr, ' '); // split it again as we just want thee time code and not the year or UTC

    if (timeVec.size() < 3 ){
        return TimeCode(0,0,1);
    }
    vector<string> MinSec = split(timeVec[2], ':'); // split the time code into hours and minutes - stored in MinSec vector
    if (MinSec.size() < 2) {
    return TimeCode(); // Handle case where split doesn't give expected output
    }
    return TimeCode(stoi(MinSec[0]),stoi(MinSec[1]),0 ); // return TimeCode 
    
    
}

int main(){
    ifstream file;

    file.open("Space_Corrected.csv"); // open Space_Corrected.csv file

    if(!file.is_open()){ // if file is not open, output that it could not open file and return 1
        cout << "Could not open the file" << endl;
        return 1;
    }

    vector<TimeCode> Launches; // vector that will holds the TimeCodes for launches
    string line; // holds line 
    getline(file,line); //skips the header line

    while(getline(file,line)){ // loop to get each line in the file
        
        TimeCode tc = parse_line(line); // use parse_line to get the TimeCode in that line

        if (!(tc.GetHours() == 0 && tc.GetMinutes() == 0 && tc.GetSeconds() == 1)) { // check if TimeCode is 1 second and if it is do not include it                                                     
            Launches.push_back(tc);                                                // set TimeCode to 1 second if launch did not have TimeCode or was invalid
        }
    }

    file.close(); // close file

// find average and number of data points
    TimeCode total(0,0,0);
    for (TimeCode tc : Launches){ // use for each loop to add each TimeCode tc to the total
        total = total + tc;
    }
    
    TimeCode avg = total / static_cast<double>(Launches.size()); // get the average TimeCode by dividing total by the size
    cout << Launches.size() << " data points." << endl; // print the number of data points 
    cout << "AVERAGE: " << avg.ToString() << endl;  // print the average

return 0;
}