#include <iostream>
#include <map>
#include "simulation.h"

using namespace std;

static const map<string, Direction> dir_map {
    {"NORTH", NORTH},
    {"EAST", EAST},
    {"SOUTH", SOUTH},
    {"WEST", WEST},
};

bool direction_ok(string dir)
{
    auto it = dir_map.find(dir);
    return it != dir_map.end();
}

string direction_to_str(Direction dir)
{
    switch (dir)
    {
        case NORTH: return "NORTH";
        case EAST: return "EAST";
        case SOUTH: return "SOUTH";
        case WEST: return "WEST";
        default: return "";
    }
}

Direction direction_to_enum(const string& dir_s)
{
    return dir_map.find(dir_s)->second;
}

bool Board::coordinates_fit(unsigned int x, unsigned int y) const
{
    return (x <= x_len_) && (y <= y_len_);
}

Simulation::~Simulation()
{
    if (robot_)
    {
        delete robot_;
    }
}

string Simulation::get_report() const
{
    string report = "";
    if (robot_)
    {
        report = to_string(robot_->get_x()) + "," + to_string(robot_->get_y()) + ",";
        report += direction_to_str(robot_->get_dir());
    }
    return report;
}

void Simulation::move_robot()
{
    if (robot_)
    {
        int x, y;
        robot_->calculate_next_pos(&x, &y);
        if (board_.coordinates_fit(x, y))
        {
            robot_->move();
        }
    }
}

void Simulation::turn_robot_left()
{
    if (robot_)
    {
        robot_->turn_left();
    }
}

void Simulation::turn_robot_right()
{
    if (robot_)
    {
        robot_->turn_right();
    }
}

void Simulation::place_robot(unsigned int x, unsigned int y, string dir)
{
    if (robot_ == nullptr)
    {
        if (board_.coordinates_fit(x, y) && direction_ok(dir))
        {
            Direction dir_e = direction_to_enum(dir);
            robot_ = new Robot(x, y, dir_e);
        }
    }
}

void Simulation::remove_robot()
{
    if (robot_)
    {
        delete robot_;
        robot_ = nullptr;
    }
}
