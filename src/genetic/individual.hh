#ifndef INDIVIDUAL_HH
# define INDIVIDUAL_HH

# include <vector>

class Gene;

class Individual
{
    public:
        Individual ();
        Individual (std::vector<Gene> &genome);
        ~Individual ();
        int evaluate ();
    private:
        std::vector<Gene> genome_;
        void generate_lua ();
};

#endif /* !INDIVIDUAL_HH */
