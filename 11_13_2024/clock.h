#ifndef CLOCK_H
#define CLOCK_H
// #pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

enum amPmType
{
    AM,
    PM
};
enum clockFormatType
{
    TWELVE = 12,
    TWENTYFOUR = 24
};
const amPmType times[] = {AM, PM};
const clockFormatType formats[] = {TWELVE, TWENTYFOUR};
const std::string amPmToStr[] = {"AM", "PM"};
const std::string clockFormatToStr[] = {"12 hour clock", "24 hour clock"};

class clockType
{
public:
    // clockType();
    clockType(int h = 0, int m = 0, int s = 0, std::string = "PM", clockFormatType = TWENTYFOUR);
    // clockType(int h, int m);
    void setTime(int h, int m, int s, std::string = "PM");

    void getTime(int &, int &, int &) const;
    int getHour() const;
    void setHour(int h);

    void incrementSeconds();
    void incrementMinutes();
    void incrementHours();

    bool operator==(const clockType &) const;
    // friend bool operator==(const clockType &, const clockType &);
    friend clockType operator+(const int, const clockType &);
    clockType operator+(const int);
    friend std::ostream &operator<<(std::ostream &, const clockType &);
    static int count;

private:
    int hr;
    int min;
    int sec;
    amPmType timeOfDay;
    clockFormatType format;
    bool equalTime(const clockType &) const;
    std::string tostring() const;
};
#endif