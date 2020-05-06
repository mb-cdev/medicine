#ifndef DATERTC_IN
#define DATERTC_IN

#include <Wire.h>
#include <Arduino.h>
#include <stdio.h>

class DateRTC{

    char I2CAddress;
    void refreshMinutes();
    void refreshHours();
    void refreshDay();
    void refreshMonth();
    void refreshYear();
    
public:
    
    struct Date{
        char year = 0x0;
        char day = 0x0;
        char month = 0x0;

        char hour = 0x0;
        char minute = 0x0;
    }currentDate;
    
    DateRTC(char I2CAddress);
    void init();
    void refresh();
    void setHour(char hour);
    void setMinute(char minute);
    void setDay(char minute);
    void setMonth(char month);
    void setYear(char year);
    void resetSeconds();
    char *getDateInASCII();
    char *getI2CAddress();
};
#endif