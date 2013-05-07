#include <iostream>
#include <thread>
#include <vector>
#include "individual.hh"
#include "gene.hh"
#include "population.hh"

Population::Population (int max)
{
    for (int i = 0; i < max; ++i)
    {
        generation_.push_back (Individual ());
    }
    max_gen_ = max;
    int j = 0;
    std::vector<std::thread> threads = std::vector<std::thread>();
    for (Individual& i : generation_)
    {
        threads.push_back(i.spawn(j));
        ++j;
    }
    for (std::thread& t : threads)
    {
        t.join();
    }
}

Population::~Population ()
{
}

bool compare_individual (Individual &first, Individual &second)
{
    return (first.score_get () > second.score_get ());
}

void Population::sort ()
{
    generation_.sort (compare_individual);
}

void Population::next_gen ()
{
    bool i2_init = true;
    std::list<Individual>::iterator i1 = generation_.begin ();
    std::list<Individual>::iterator i2 = generation_.begin ();
    std::list<Individual>::iterator it;
    size_t i = 0;
    for (it = generation_.begin (); it != generation_.end (); ++it)
    {
        if (i == generation_.size () / 2)
            break;
        if (it->score_get () > i1->score_get ())
            i1 = it;
        ++i;
    }
    for (it = generation_.begin (); it != generation_.end (); ++it)
    {
        if (i < generation_.size () / 2)
            continue;
        if (i2_init)
        {
            if (it != i1)
            {
                i2 = it;
                i2_init = false;
            }
            continue;
        }
        if (it->score_get () > i2->score_get ())
            i2 = it;
        ++i;
    }
    std::cout << "Best 1: " << i1->score_get () << std::endl;
    i1->generate_lua ("best_1.lua");
    std::cout << "Best 2: " << i2->score_get () << std::endl;
    i2->generate_lua ("best_2.lua");
    std::list<Individual> new_gen;
    for (int i = 0; i < max_gen_; ++i)
    {
        if (i < max_gen_ / 2)
            new_gen.push_back (Individual (*i1, *i2));
        else
            new_gen.push_back (Individual (*i2, *i1));
    }
    int j = 0;
    std::vector<std::thread> threads = std::vector<std::thread>();
    for (Individual& i : new_gen)
    {
        i.mutate (20);
        threads.push_back(i.spawn(j));
        ++j;
    }
    for (std::thread& t : threads)
    {
        t.join();
    }
    new_gen.push_back (Individual (*i1));
    new_gen.push_back (Individual (*i2));
    generation_.clear ();
    generation_ = new_gen;
}
