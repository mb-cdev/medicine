#include <LCD.h>

char LCD::decodeASCIICharacter(char ASCII){
    switch(ASCII)
    {
        case '-':
            return 0b00101101;
        case '*':
            return 0b01111110;
        case '?':
            return 0b00111111;
        case '!':
            return 0b00100001;
        case '.':
            return 0b00101110;
        case ':':
            return 0b00111010;
        case '0':
            return 0b00110000;
        case '1':
            return 0b00110001;
        case '2':
            return 0b00110010;
        case '3':
            return 0b00110011;
        case '4':
            return 0b00110100;
        case '5':
            return 0b00110101;
        case '6':
            return 0b00110110;
        case '7':
            return 0b00110111;
        case '8':
            return 0b00111000;
        case '9':
            return 0b00111001;
        case 'A':
        case 'a':
            return 0b01000001;
        case 'B':
        case 'b':
            return 0b01000010;
        case 'C':
        case 'c':
            return 0b01000011;
        case 'D':
        case 'd':
            return 0b01000100;
        case 'E':
        case 'e':
            return 0b01000101;
        case 'F':
        case 'f':
            return 0b01000110;
        case 'G':
        case 'g':
            return 0b01000111;
        case 'H':
        case 'h':
            return 0b01001000;
        case 'I':
        case 'i':
            return 0b01001001;
        case 'J':
        case 'j':
            return 0b01001010;
        case 'K':
        case 'k':
            return 0b01001011;
        case 'L':
        case 'l':
            return 0b01001100;
        case 'M':
        case 'm':
            return 0b01001101;
        case 'N':
        case 'n':
            return 0b01001110;
        case 'O':
        case 'o':
            return 0b01001111;
        case 'P':
        case 'p':
            return 0b01010000;
        case 'Q':
        case 'q':
            return 0b01010001;
        case 'R':
        case 'r':
            return 0b01010010;
        case 'S':
        case 's':
            return 0b01010011;
        case 'T':
        case 't':
            return 0b01010100;
        case 'U':
        case 'u':
            return 0b01010101;
        case 'V':
        case 'v':
            return 0b01010110;
        case 'W':
        case 'w':
            return 0b01010111;
        case 'X':
        case 'x':
            return 0b01011000;
        case 'Y':
        case 'y':
            return 0b01011001;
        case 'Z':
        case 'z':
            return 0b01011010;
        case ' ':
            return 0b00100000;
        default:
            return 0b00111111;
    }
}


void LCD::setPointerInLine(char line){
   /**
    * Clear pointers
    * */
    execute(0,0,0b10000000);
    execute(1,0,decodeASCIICharacter(' '));
    execute(0,0,0b11000000);
    execute(1,0,decodeASCIICharacter(' '));
    execute(0,0,0b10010100);
    execute(1,0,decodeASCIICharacter(' '));
    execute(0,0,0b11010100);
    execute(1,0,decodeASCIICharacter(' '));
            
    switch(line){
        case 0b00000001:
            execute(0,0,0b10000000);
            execute(1,0,decodeASCIICharacter('*'));
        break;
        case 0b00000010:
            execute(0,0,0b11000000);
            execute(1,0,decodeASCIICharacter('*'));
        break;
        case 0b00000011:
            execute(0,0,0b10010100);
            execute(1,0,decodeASCIICharacter('*'));
        break;
        case 0b00000100:
            execute(0,0,0b11010100);
            execute(1,0,decodeASCIICharacter('*'));
        break;
    }
}

void LCD::printLines(char *line1, char *line2, char *line3, char *line4){
    //reset display
    execute(0,0,0b00000001);
    print(line1);
    execute(0,0,0b11000000); //address line 2
    print(line2);
    execute(0,0,0b10010100); //address line 3
    print(line3);
    execute(0,0,0b11010100); //address line 4
    print(line4);
}

void LCD::print(char *text){
    //SPACE FOR POINTER
    execute(1,0,0b00100000);
    
    for(int i = 0; i<=18;i++){
        if(!bool(text[i])){
            break;
        }   
        execute(1,0,decodeASCIICharacter(text[i]));
    }
}

void LCD::print(char *text, char line)
{
     switch(line){
        case 0b00000001:
            execute(0,0,0b10000000);
        break;
        case 0b00000010:
            execute(0,0,0b11000000);
        break;
        case 0b00000011:
            execute(0,0,0b10010100);
        break;
        case 0b00000100:
            execute(0,0,0b11010100);
        break;
    }
    
    print(text);
}

void LCD::init(){ 
    //set 8-bit interface
    execute(0,0,0b00110000);
    delay(5);
    //set 8-bit interface
    execute(0,0,0b00110000);
    delayMicroseconds(120);
    //set 8-bit interface
    execute(0,0,0b00110000);
    delay(2);
    //Function set - number of display lines and character font
    execute(0,0,0b00111100);
    delay(2);
    // Display off
    execute(0,0,0b00001000);
    delay(1);
    // Display clear
    execute(0,0,0b00000001);
    delay(1);
    // Entry mode set
    execute(0,0,0b00000110);
    delay(1);
    // Display on
    execute(0,0,0b00001100);
    delay(1);
}



void LCD::execute(bool RS, bool RW, char D0D7){
    char operation = 0x0;
    PORTB &= 0b11111000;
  
    if(RS){
        operation |= 0b00000100;
    }

    if(RW){
        operation |= 0b00000010;
    }

  
    PORTD = D0D7;

    //set E to 1
    operation |= 0b00000001;
    
    PORTB |= operation;
    delayMicroseconds(50);
    
    //set E to 0
    operation &= 0b11111110;
    PORTB &= operation | 0b11111000;
    delay(4.5);
}

/******
 * PORT - PIN => DESTINATION
 * 
 * LCD: 
 * PORTD - D0-D7 LCD
 * PORTB - 0 => E, 1 => RW, 2 => RS
 * 
 * */

LCD::LCD(){
    DDRD = 0b11111111;
    DDRB |= 0b00000111;
}