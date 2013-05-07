#ifndef INDIVIDUAL_HH
# define INDIVIDUAL_HH

# include <vector>
# include <iostream>
# include <thread>

class Gene;

class Individual
{
    public:
        Individual ();
        Individual (std::vector<Gene> &genome);
        Individual (const Individual &in);
        Individual (Individual &i1, Individual &i2);
        ~Individual ();
        int score_get () const;
        Gene genome_get (int n) const;
        void mutate (int coef);
        std::thread spawn(int i);
        void evaluate (int i);
        void generate_lua (std::string file);
    private:
        std::vector<Gene> genome_;
        int score_;
};

#endif /* !INDIVIDUAL_HH */
