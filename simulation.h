#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include "robot.h"

class Board
{
public:
    explicit Board(unsigned int x_len, unsigned int y_len)
        : x_len_(x_len), y_len_(y_len) {}

    bool coordinates_fit(unsigned int x, unsigned int y) const;
private:
    Board();
    const unsigned int x_len_;
    const unsigned int y_len_;
};

class Simulation
{
public:
    explicit Simulation(unsigned int board_xlen, unsigned int board_ylen) :
        robot_(nullptr), board_(board_xlen, board_ylen) {}
    ~Simulation();
    std::string get_report() const;
    void move_robot();
    void turn_robot_left();
    void turn_robot_right();

    void place_robot(unsigned int x, unsigned int y, std::string dir);
    void remove_robot();
private:
    Simulation();
    Robot* robot_;
    const Board board_;
};

#endif // #ifndef SIMULATION_H_
