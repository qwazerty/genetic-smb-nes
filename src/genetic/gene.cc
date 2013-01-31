#include <string>
#include <cstdlib>
#include "gene.hh"

Gene::Gene ()
{
    lr_arrow_ = static_cast<e_lr_key>(rand () % 2);
    ud_arrow_ = static_cast<e_ud_key>(rand () % 3);
    a_button_ = rand () % 2;
    b_button_ = rand () % 2;
}

Gene::~Gene ()
{
}

void Gene::evolve ()
{
    if (rand () % 100 == 0)
        lr_arrow_ = static_cast<e_lr_key>(rand () % 2);
    if (rand () % 100 == 0)
        ud_arrow_ = static_cast<e_ud_key>(rand () % 3);
    if (rand () % 100 == 0)
        a_button_ = rand () % 2;
    if (rand () % 100 == 0)
        b_button_ = rand () % 2;
}

std::string Gene::extract ()
{
    std::string data = "{";
    bool comma = false;
    if (lr_arrow_ != LR_NONE)
    {
        comma = true;
        if (lr_arrow_ == LEFT)
            data += "left=true";
        else
            data += "right=true";
    }
    if (ud_arrow_ != UD_NONE)
    {
        data += comma ? ", " : "";
        comma = true;
        if (ud_arrow_ == UP)
            data += "up=true";
        else
            data += "down=true";
    }
    if (a_button_)
    {
        data += comma ? ", " : "";
        comma = true;
        data += "A=true";
    }
    if (b_button_)
    {
        data += comma ? ", " : "";
        comma = true;
        data += "B=true";
    }
    data += "}";
    return data;
}
