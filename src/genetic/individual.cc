#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <csignal>
#include "gene.hh"
#include "individual.hh"

Individual::Individual ()
{
    for (int i = 0; i < 1000; ++i)
        genome_.push_back (Gene ());
}

Individual::Individual (std::vector<Gene> &genome)
{
    for (Gene &g : genome)
        g.evolve ();
}

Individual::~Individual ()
{
}

void Individual::generate_lua ()
{
    std::ofstream ofs ("smb.lua");

    ofs << "savestate.load(savestate.object(1))" << std::endl
        << "local level = memory.readbyte(0x0760)" << std::endl
        << "newlevel = level" << std::endl
        << "state = 0" << std::endl << std::endl
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
        << "    emu.print(\"score:\" .. score .. \"\")" << std::endl
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
        << "while (newlevel == level and (not (state == 11))) do" << std::endl
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

int Individual::evaluate ()
{
    generate_lua ();
    int fd[2];
    pid_t pid;
    pipe(fd);
    if ((pid = fork ()) == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        if (execl ("/usr/bin/fceux", "fceux", "Super Mario Bros.zip",
            "--loadlua", "smb.lua", NULL) == -1)
            perror ("fork");
    }
    else
    {
        close(fd[1]);
        char reading_buf[1];
        std::string res;
        while(read(fd[0], reading_buf, 1) > 0)
        {
            std::cout << "Read !!!" << std::endl;
            res += reading_buf;
            if (res.find("score"))
            {
                std::cout << "KILL !!!" << std::endl;
                kill (pid, SIGKILL);
            }
        }
        close(fd[0]);
        /* FIXME: Add pipe to get score */
    }
    return 0;
}
