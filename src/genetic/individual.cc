#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <csignal>
#include "gene.hh"
#include "individual.hh"

Individual::Individual ()
{
    for (int i = 0; i < 1000; ++i)
        genome_.push_back (Gene ());
    evaluate ();
}

Individual::Individual (std::vector<Gene> &genome)
{
    for (Gene &g : genome)
        g.evolve ();
}

Individual::Individual (const Individual &in)
{
    for (int i = 0; i < 1000; ++i)
        genome_.push_back (in.genome_get (i));
    score_ = in.score_get ();
}

Individual::Individual (Individual &i1, Individual &i2)
{
    for (int i = 0; i < 1000; ++i)
    {
        if (rand () % 2 == 0)
            genome_.push_back (i1.genome_get (i));
        else
            genome_.push_back (i2.genome_get (i));
    }
    evaluate ();
}

Individual::~Individual ()
{
}

int Individual::score_get () const
{
    return score_;
}

Gene Individual::genome_get (int n) const
{
    return genome_[n];
}

void Individual::mutate ()
{
    for (int i = 0; i < 1000; ++i)
    {
        if (rand () % 100 == 0)
            genome_[i].evolve ();
    }
}

void Individual::generate_lua_ ()
{
    std::ofstream ofs ("smb.lua");

    ofs << "savestate.load(savestate.object(1))" << std::endl
        << "emu.speedmode(\"maximum\")" << std::endl
        << "local level = memory.readbyte(0x0760)" << std::endl
        << "newlevel = level" << std::endl
        << "state = 8" << std::endl << std::endl
        << "function on_exit ()" << std::endl
        << "    emu.softreset()" << std::endl
        << "end" << std::endl
        << "emu.registerexit(on_exit)" << std::endl
        << "function print_score ()" << std::endl
        << "    local score =" << std::endl
        << "          (memory.readbyte(0x07dd) * 1000000)" << std::endl
        << "        + (memory.readbyte(0x07de) * 100000)" << std::endl
        << "        + (memory.readbyte(0x07df) * 10000)" << std::endl
        << "        + (memory.readbyte(0x07e0) * 1000)" << std::endl
        << "        + (memory.readbyte(0x07e1) * 100)" << std::endl
        << "        + (memory.readbyte(0x07e2) * 10)" << std::endl
        << "        .. \"\"" << std::endl
        << "    emu.print(\"<score>\" .. score .. \"</score>\")" << std::endl
        << "end" << std::endl << std::endl;

    int i = 0;
    ofs << "table = {}" << std::endl;
    for (Gene &g : genome_)
    {
        ofs << "table[" << i << "] = " << g.extract () << std::endl;
        ++i;
    }

    ofs << std::endl
        << "local i = 0" << std::endl
        << "local j = 0" << std::endl
        << "while (newlevel == level and (not (state == 11 or state == 0)))"
        << " do" << std::endl
        << "    newlevel = memory.readbyte(0x0760)" << std::endl
        << "    state = memory.readbyte(0x000e)" << std::endl
        << "    joypad.set(1, table[i % 1000])" << std::endl
        << "    emu.frameadvance()" << std::endl
        << "    j = (j + 1) % 10" << std::endl
        << "    if (j == 0) then" << std::endl
        << "        i = i + 1" << std::endl
        << "    end" << std::endl
        << "end" << std::endl
        << "print_score ()" << std::endl;
}

void Individual::evaluate ()
{
    int result = 0;
    int fd[2];
    pid_t pid;

    generate_lua_ ();
    pipe(fd);
    if ((pid = fork ()) == 0)
    {
        close (fd[0]);
        dup2 (fd[1], STDOUT_FILENO);
        execl ("/usr/bin/unbuffer", "unbuffer", "/usr/bin/fceux",
            "Super Mario Bros.zip", "--loadlua", "smb.lua", NULL);
        perror ("fork");
    }
    else
    {
        close (fd[1]);
        char buf[1];
        std::string res;
        while(read(fd[0], buf, 1) > 0)
        {
            res.push_back (buf[0]);
            if (res.find ("</score>") != std::string::npos)
            {
                kill (pid, SIGKILL);
                res.erase (0, res.find ("<score>") + 7);
                res.erase (res.find ("</score>"));
                std::stringstream strs (res);
                if (!(strs >> result))
                    result = 0;
            }
        }
        close (fd[0]);
    }
    score_ = result;
    std::cout << "Current test: " << score_ << std::endl;
}
