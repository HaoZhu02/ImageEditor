#include "utilities.h"


// Limiter Functions
int limit0_255(int num)
{
    if(num < 0)
    {
        return 0;
    }

    if(num > 255)
    {
        return 255;
    }

    else{
        return num;
    }
}

int limitm100_100(int num)
{
    if(num < -100)
    {
        return -100;
    }

    if(num > 100)
    {
        return 100;
    }

    else{
        return num;
    }
}

int limit0_100(int num)
{
    if(num < 0)
    {
        return 0;
    }

    if(num > 100)
    {
        return 100;
    }

    else{
        return num;
    }
}
