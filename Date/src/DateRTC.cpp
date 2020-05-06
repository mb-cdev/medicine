#include <DateRTC.h>

char *DateRTC::getI2CAddress(){
    return I2CAddress;
}

DateRTC::DateRTC(char i){
    I2CAddress = i;
}

void DateRTC::refreshMinutes(){
    Wire.requestFrom(I2CAddress,1,(uint32_t)1,(uint8_t)1,true);
    if(!Wire.available()){
        return;
    }
    char r = Wire.read();
    currentDate.minute = (10*(r >> 4)+(r & 0b00001111));
}

void DateRTC::refreshHours(){
    Wire.requestFrom(I2CAddress,1,(uint32_t)2,(uint8_t)1,true);
    if(!Wire.available()){
        return;
    }
    char r = Wire.read();
    currentDate.hour = (10*(r >> 4)+(r & 0b00001111));
}

void DateRTC::refreshDay(){
    Wire.requestFrom(I2CAddress,1,(uint32_t)4,(uint8_t)1,true);
    if(!Wire.available()){
        return;
    }
    char r = Wire.read();
    currentDate.day = (10*(r >> 4)+(r & 0b00001111));
}

void DateRTC::refreshMonth(){
    Wire.requestFrom(I2CAddress,1,(uint32_t)5,(uint8_t)1,true);
    if(!Wire.available()){
        return;
    }
    char r = Wire.read();
    currentDate.month = (10*(r >> 4)+(r & 0b00001111));
}

void DateRTC::refreshYear(){
    Wire.requestFrom(I2CAddress,1,(uint32_t)6,(uint8_t)1,true);
    if(!Wire.available()){
        return;
    }
    char r = Wire.read();
    currentDate.year = (10*(r >> 4)+(r & 0b00001111));
}

void DateRTC::refresh(){
    refreshMinutes();
    refreshHours();
    refreshDay();
    refreshMonth();
    refreshYear();
}

char *DateRTC::getDateInASCII(){
    static char ascii[17] = "";
    
    sprintf(ascii, "%02d:%02d %02d-%02d-2%03d", currentDate.hour, currentDate.minute, currentDate.day, currentDate.month, currentDate.year);
    return ascii;
}

void DateRTC::init(){
    refresh();
}

void DateRTC::setHour(char hour)
{
    char upper = (hour/0b1010);
    char lower = hour - (hour/0b1010)*0b1010;
    char bcd = 0x0;
    bcd = (upper << 4 | lower) & 0b00111111;
    
    
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x2);
    Wire.write(bcd);
    Wire.endTransmission();
}

void DateRTC::setMinute(char minute){
    char upper = (minute/0b1010);
    char lower = minute - (minute/0b1010)*0b1010;
    char bcd = 0x0;
    bcd = (upper << 4 | lower);
    
    
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x1);
    Wire.write(bcd);
    Wire.endTransmission();
}

void DateRTC::resetSeconds(){
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.endTransmission();
}



void DateRTC::setDay(char day){
    char upper = (day/0b1010);
    char lower = day - (day/0b1010)*0b1010;
    char bcd = 0x0;
    bcd = (upper << 4 | lower);
    
    
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x4);
    Wire.write(bcd);
    Wire.endTransmission();
}


void DateRTC::setMonth(char month){
    char upper = (month/0b1010);
    char lower = month - (month/0b1010)*0b1010;
    char bcd = 0x0;
    bcd = (upper << 4 | lower);
    
    
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x5);
    Wire.write(bcd);
    Wire.endTransmission();
}


void DateRTC::setYear(char year){
    char upper = (year/0b1010);
    char lower = year - (year/0b1010)*0b1010;
    char bcd = 0x0;
    bcd = (upper << 4 | lower);
    
    
    Wire.beginTransmission(I2CAddress);
    Wire.write(0x6);
    Wire.write(bcd);
    Wire.endTransmission();
}