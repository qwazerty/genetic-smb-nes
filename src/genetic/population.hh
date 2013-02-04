#ifndef POPULATION_HH
# define POPULATION_HH

# include <list>
# include "individual.hh"

class Population
{
    public:
        Population (int max);
        ~Population ();
        void sort ();
        void next_gen ();
    private:
        std::list<Individual> generation_;
        int max_gen_;
};

#endif /* !POPULATION_HH */
