#include "robot.h"


Robot::Robot(int x_pos, int y_pos, Direction direction)
{
    x_pos_ = x_pos;
    y_pos_ = y_pos;
    direction_ = direction;
}

void Robot::turn_left()
{
    direction_ = (direction_ + 1) % MAX_DIRECTION;
}

void Robot::turn_right()
{
    direction_ = (direction_ - 1) % MAX_DIRECTION;
}

void calculate_next_pos(int* x, int* y)
{
    switch (direction_) {
        case NORTH:
            *x = x_pos_;
            *y = y_pos_ + 1;
            break;
        case EAST:
            *x = x_pos_ + 1;
            *y = y_pos_;
            break;
        case SOUTH:
            *x = x_pos_;
            *y = y_pos_ - 1;
            break;
        case WEST:
            *x = x_pos_ - 1;
            *y = y_pos_;
            break;
    }
}

void Robot::move()
{
    calculate_next_pos(&x_pos_, &y_pos_);
}
