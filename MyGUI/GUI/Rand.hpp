#include <time.h>
#include <iostream>

template <typename type>
type Rand(type min, type max)
{
    static bool timeNull = 0;

    if(!timeNull)
    {
        srand(time(NULL));

        timeNull = 1;
    }

    if(min > max)
    {
        std::swap(min, max);
    }

    return (rand() % (max - min + 1) + min);
}
