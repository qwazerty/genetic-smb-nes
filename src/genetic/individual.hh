#ifndef INDIVIDUAL_HH
# define INDIVIDUAL_HH

# include <vector>

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
        void mutate ();
        void evaluate ();
    private:
        std::vector<Gene> genome_;
        int score_;
        void generate_lua_ ();
};

#endif /* !INDIVIDUAL_HH */
