#ifndef GLOBALS_INZ
#define GLOBALS_INZ

const static int MAX_MODULES = 4;
enum class MODULE_AXIS {X = 0, Y = 1};
const char MODULE_AXIS_NAMES[2][2]= {{'X','\0'},{'Y','\0'}};


struct execute_time{
    char year = 0x0;
    char month = 0x0;
    char day = 0x0;
        
    char hour = 0x0;
    char minute = 0x0;
};

struct module{
    char address = 0x0;
};    

struct container{
    char module_address_x = 0x0;
    char module_address_y = 0x0;
    bool executed = true;
    struct execute_time time = {};
};

#endif