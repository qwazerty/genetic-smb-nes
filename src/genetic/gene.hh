#ifndef GENE_HH
# define GENE_HH

typedef enum LR_KEY
{
    LR_NONE,
    RIGHT,
    LEFT
} e_lr_key;

typedef enum UD_KEY
{
    UD_NONE,
    UP,
    DOWN
} e_ud_key;

class Gene
{
    public:
        Gene ();
        ~Gene ();
        void evolve ();
        std::string extract ();
    private:
        e_lr_key lr_arrow_;
        e_ud_key ud_arrow_;
        bool a_button_;
        bool b_button_;
};

#endif /* !GENE_HH */
