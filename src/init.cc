#include <cstdlib>
#include <ctime>
#include <iostream>
#include "population.hh"

int main ()
{
    int gen = 0;
    srand(time(NULL));
    std::cout << "===================" << std::endl;
    std::cout << "Generation: " << gen << std::endl;
    Population p (12);
    p.sort ();
    while (true)
    {
        ++gen;
        std::cout << "===================" << std::endl;
        std::cout << "Generation: " << gen << std::endl;
        p.next_gen ();
        p.sort ();
    }
    return 0;
}
