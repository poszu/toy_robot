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

    void calculate_next_pos(int* x, int* y);


private:
    Robot();
    int x_pos_;
    int y_pos_;
    unsigned int direction_;
};
