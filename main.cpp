#include <iostream>
#include <regex>
#include <cstdio>
#include "simulation.h"

#define BOARD_X_LEN 5
#define BOARD_Y_LEN 5
#define MAX_CMD_SIZE 256
static char cmd_buff[MAX_CMD_SIZE];

static const std::regex place_regex("^PLACE\\s+(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*([A-Z]+)\\s*$");
static const std::regex move_regex("^MOVE\\s*$");
static const std::regex report_regex("^REPORT\\s*");
static const std::regex left_regex("^LEFT\\s*");
static const std::regex right_regex("^RIGHT\\s*");

static std::smatch base_match;

static const std::string help =
    "Toy robot simulation program.\n"
    "usage: toy_robot [-h] [--help] [-f INPUTFILE]\n\n"
    "When ran w/o arguments, accepts commands from standard input.\n\n"
    "optional arguments:\n"
    " -h, --help    show this help message and exit\n"
    " -f INPUTFILE  read commands from INPUTFILE and execute\n";

int main(int argc, char** argv)
{
    Simulation sim(BOARD_X_LEN, BOARD_Y_LEN);
    const char* cmd = nullptr;
    FILE * input = stdin;
    // Parse arguments
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
    {
        std::cout << help << std::endl;
        return 0;
    }

    if (argc == 3 && std::string(argv[1]) == "-f")
    {
        input = fopen(argv[2], "r");
        if (!input)
        {
            std::cerr << "Cannot open file:" << argv[2] << std::endl;
            return 1;
        }
    }
    else if (argc != 1)
    {
        // Unrecognized arguments - print help and exit.
        std::cerr << "Unrecognized arguments" << std::endl << std::endl;
        std::cout << help << std::endl;
        return 2;
    }
    // Process
    do
    {
        cmd = fgets(cmd_buff, MAX_CMD_SIZE, input);
        if (cmd)
        {
            std::string cmd_s(cmd);
            // Match PLACE X, Y, DIR
            if (std::regex_match(cmd_s, base_match, place_regex))
            {
                int x = stoi(base_match[1].str());
                int y = stoi(base_match[2].str());
                sim.place_robot(x, y, base_match[3].str());
                continue;
            }
            // Match MOVE
            if (std::regex_match(cmd_s, base_match, move_regex))
            {
                sim.move_robot();
                continue;
            }
            // Match LEFT
            if (std::regex_match(cmd_s, base_match, left_regex))
            {
                sim.turn_robot_left();
                continue;
            }
            // Match RIGHT
            if (std::regex_match(cmd_s, base_match, right_regex))
            {
                sim.turn_robot_right();
                continue;
            }
            // Match REPORT
            if (std::regex_match(cmd_s, base_match, report_regex))
            {
                std::string report = sim.get_report();
                if (report != "")
                {
                    std::cout << report << std::endl;
                }
                continue;
            }
        }
    } while (cmd);

    if (input != stdin)
    {
        fclose(input);
    }
    return 0;
}
