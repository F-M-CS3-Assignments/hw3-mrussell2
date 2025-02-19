#include <iostream> //provides cout
#include <sstream> // provides stringstream

using namespace std;

//AUTHOR: MAX RUSSELL

#include "TimeCode.h"  // include header file

//implement constructor, set t = to seconds for given hr, min, sec
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

//set t = to given TimeCode
TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

//set the hours equal to value that is taken in and ensure is non-negative
void TimeCode::SetHours(unsigned int hours){
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hours, min, sec);
}

//set the minutes equal to the value that is taken in, ensure minutes is < 60 and not negative
void TimeCode::SetMinutes(unsigned int minutes){
    unsigned int hr, min, sec;

    if (minutes >= 60){
        throw std::invalid_argument("Minutes must be less than 60: "+ to_string(minutes)); // throws error when minutes is >= 60
    }

    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hr, minutes, sec);
}
//set the seconds equal to the value that is taken in, ensure minutes is < 60 and not negative
void TimeCode::SetSeconds(unsigned int seconds){
    unsigned int hr, min, sec;

    if (seconds >= 60){
        throw std::invalid_argument("Seconds must be less than 60: " + to_string(seconds)); // throws error when seconds is >= 60
    }
    GetComponents(hr, min, sec);
    t = ComponentsToSeconds(hr, min, seconds);
}

//resets TimeCode
void TimeCode::reset(){
    t = 0;
}

//Returns the hours using GetComponents
unsigned int TimeCode::GetHours() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return hr;
}

//Returns the minutes using GetComponents
unsigned int TimeCode::GetMinutes() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return min;
}

//Returns the seconds using GetComponents
unsigned int TimeCode::GetSeconds() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return sec;
}

//GetComponents uses pass by reference to take in hr, min, sec and assign these variables with their correct number
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = t/3600;
    min = (t%3600) /60;
    sec = t % 60;
}

//Converts input hr, min, sec to seconds 
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return (hr*3600) + (min*60) + sec;
}

//Resource for learning to use stringstream : https://www.geeksforgeeks.org/stringstream-c-applications/ 
//Prints TimeCode in " 0:0:0 " format
string TimeCode::ToString() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);

    stringstream hrs, mins, secs;
    string h,m,s;

    hrs << hr;
    mins << min;
    secs << sec;

    hrs >> h; 
    mins >> m; 
    secs >> s;

    return h + ":" + m + ":" + s;
}

//overloads addition operator, allowing addition of two time codes
TimeCode TimeCode::operator+(const TimeCode& other) const{
    return TimeCode(0, 0, t + other.t);
}

//overloads subtraction operator, allowing subtraction of two time codes
TimeCode TimeCode::operator-(const TimeCode& other) const{
    if (t < other.t){
        throw std::invalid_argument("Resulting TimeCode cannot be negative.");
    }
    return TimeCode(0, 0, t - other.t);
}

//overloads multiplication operator, allowing multiplication of a time code and a double
TimeCode TimeCode::operator*(double a) const{
    if (a<0){
        throw std::invalid_argument("Double cannot be negative.");
    }
    return TimeCode(0, 0, static_cast<unsigned long long int>(t * a));
}

//overloads division operator, allowing division of a time code and a double
TimeCode TimeCode::operator/(double a) const{
    if (a <=0){
        throw std::invalid_argument("Double cannot be negative or 0.");
    }
    return TimeCode(0, 0, static_cast<unsigned long long int>(t / a));
}

// overloads == operator, allowing us to see if two TimeCodes are equal
bool TimeCode::operator == (const TimeCode& other) const{
    return t == other.t;
}

// overloads != operator, allowing us to see if two TimeCodes are not equal
bool TimeCode::operator != (const TimeCode& other) const{
    return t != other.t;
}

// overloads < operator, allowing us to see if our TimeCode is less than the other TimeCode
bool TimeCode::operator < (const TimeCode& other) const{
    return t < other.t;
}

// overloads <= operator, allowing us to see if our TimeCode is less than or equal to the other TimeCode
bool TimeCode::operator <= (const TimeCode& other) const{
    return t <= other.t;
}

// overloads > operator, allowing us to see if our TimeCode is greater than the other TimeCode
bool TimeCode::operator > (const TimeCode& other) const{
    return t > other.t;
}

// overloads >= operator, allowing us to see if our TimeCode is greater than or equal to the other TimeCode
bool TimeCode::operator >= (const TimeCode& other) const{
    return t >= other.t;
}

