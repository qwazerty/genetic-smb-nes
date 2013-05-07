#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include "population.hh"
#include "variables.hh"

int main ()
{
    int gen = 0;
    srand(time(NULL));
    std::cout << "Starting in 5 secondes..." << std::endl;
    sleep(5);
    std::cout << "===================" << std::endl;
    std::cout << "Generation: " << gen << std::endl;
    Population p(POPULATION);
    p.sort();
    while (true)
    {
        ++gen;
        std::cout << "===================" << std::endl;
        std::cout << "Generation: " << gen << std::endl;
        p.next_gen();
        p.sort();
    }
    return 0;
}
