#ifndef ROBOT_H_
#define ROBOT_H_

enum Direction
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    MAX_DIRECTION = 4,
};

class Robot
{
public:
    explicit Robot(int x_pos, int y_pos, Direction direction);
    void turn_left();
    void turn_right();
    void move();

    void calculate_next_pos(int* x, int* y) const;

    int get_x() const { return x_pos_; }
    int get_y() const { return y_pos_; }
    Direction get_dir() const { return Direction(direction_); }

private:
    Robot();
    int x_pos_;
    int y_pos_;
    unsigned int direction_;
};

#endif // #ifndef ROBOT_H_
