#include <cstdlib>
#include <ctime>
#include "individual.hh"

int main ()
{
    srand(time(NULL));
    Individual i;
    i.evaluate ();
    return 0;
}
