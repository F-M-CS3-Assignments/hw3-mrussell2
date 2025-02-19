#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

#include "TimeCode.h"

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

void TimeCode::SetHours(unsigned int hours){
    unsigned int min, sec;
    GetComponents(hours, min, sec);
    t = ComponentsToSeconds(hours, min, sec);
}

void TimeCode::SetMinutes(unsigned int minutes){
    unsigned int hr, sec;
    GetComponents(hr, minutes, sec);
    t = ComponentsToSeconds(hr, minutes, sec);
}

void TimeCode::SetSeconds(unsigned int seconds){
    unsigned int hr, min;
    GetComponents(hr, min, seconds);
    t = ComponentsToSeconds(hr, min, seconds);
}

void TimeCode::reset(){
    t = 0;
}

unsigned int TimeCode::GetHours() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return hr;
}

unsigned int TimeCode::GetMinutes() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return min;
}
unsigned int TimeCode::GetSeconds() const{
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);
    return sec;
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = t/3600;
    min = (t%3600) /60;
    sec = t % 60;
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return (hr*3600) + (min*60) + sec;
}

//Resource for learning to use stringstream : https://www.geeksforgeeks.org/stringstream-c-applications/ 

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

TimeCode TimeCode::operator+(const TimeCode& other) const{
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const{
    if (t < other.t){
        throw std::invalid_argument("Resulting TimeCode cannot be negative.");
    }
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(double a) const{
    if (a<0){
        throw std::invalid_argument("Double cannot be negative.");
    }
    return TimeCode(0, 0, static_cast<unsigned long long int>(t * a));
}

TimeCode TimeCode::operator/(double a) const{
    if (a <=0){
        throw std::invalid_argument("Double cannot be negative or 0.");
    }
    return TimeCode(0, 0, static_cast<unsigned long long int>(t / a));
}

bool TimeCode::operator == (const TimeCode& other) const{
    return t == other.t;
}

bool TimeCode::operator != (const TimeCode& other) const{
    return t != other.t;
}

bool TimeCode::operator < (const TimeCode& other) const{
    return t < other.t;
}

bool TimeCode::operator <= (const TimeCode& other) const{
    return t <= other.t;
}

bool TimeCode::operator > (const TimeCode& other) const{
    return t > other.t;
}

bool TimeCode::operator >= (const TimeCode& other) const{
    return t >= other.t;
}

