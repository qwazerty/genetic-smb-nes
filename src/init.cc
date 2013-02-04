#include <cstdlib>
#include <ctime>
#include <iostream>
#include "population.hh"

int main ()
{
    srand(time(NULL));
    Population p (6);
    p.sort ();
    while (true)
    {
        p.next_gen ();
        p.sort ();
    }
    return 0;
}
