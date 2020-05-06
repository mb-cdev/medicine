#ifndef LCD_INZ
#define LCD_INZ

#include <Arduino.h>

class LCD
{
    private:
        void execute(bool RS, bool RW, char D0D7);
        char decodeASCIICharacter(char ASCII);
    public:
        void print(char *text);
        void print(char *text, char line);
        void printLines(char *line1, char *line2, char *line3, char *line4);
        void init();
        void setPointerInLine(char line);
        LCD();
};

#endif