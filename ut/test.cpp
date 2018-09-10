#include <string>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define private public  // So test can access and verify private fields
#include "../simulation.h"
#include "../robot.h"

TEST_CASE( "Robot placement", "[robot]" )
{
    Robot robot(0, 0, NORTH);
    REQUIRE(robot.get_x() == 0);
    REQUIRE(robot.get_y() == 0);
    REQUIRE(robot.get_dir() == NORTH);
}

TEST_CASE( "Robot move north", "[robot]" )
{
    Robot robot(0, 0, NORTH);
    robot.move();
    REQUIRE(robot.get_x() == 0);
    REQUIRE(robot.get_y() == 1);
    robot.move();
    REQUIRE(robot.get_y() == 2);
}

TEST_CASE( "Robot rotate left", "[robot]" )
{
    Robot robot(0, 0, NORTH);
    REQUIRE(robot.get_dir() == NORTH);
    robot.turn_left();
    REQUIRE(robot.get_dir() == WEST);
    robot.turn_left();
    REQUIRE(robot.get_dir() == SOUTH);
    robot.turn_left();
    REQUIRE(robot.get_dir() == EAST);
    robot.turn_left();
    REQUIRE(robot.get_dir() == NORTH);
}

TEST_CASE( "Robot rotate right", "[robot]" )
{
    Robot robot(0, 0, NORTH);
    REQUIRE(robot.get_dir() == NORTH);
    robot.turn_right();
    REQUIRE(robot.get_dir() == EAST);
    robot.turn_right();
    REQUIRE(robot.get_dir() == SOUTH);
    robot.turn_right();
    REQUIRE(robot.get_dir() == WEST);
    robot.turn_right();
    REQUIRE(robot.get_dir() == NORTH);
}

TEST_CASE( "Robot move south", "[robot]" )
{
    Robot robot(0, 0, SOUTH);
    robot.move();
    REQUIRE(robot.get_x() == 0);
    REQUIRE(robot.get_y() == -1);
    robot.move();
    REQUIRE(robot.get_y() == -2);
}

TEST_CASE( "Robot move east", "[robot]" )
{
    Robot robot(0, 0, EAST);
    robot.move();
    REQUIRE(robot.get_x() == 1);
    REQUIRE(robot.get_y() == 0);
    robot.move();
    REQUIRE(robot.get_x() == 2);
}

TEST_CASE( "Robot move west", "[robot]" )
{
    Robot robot(0, 0, WEST);
    robot.move();
    REQUIRE(robot.get_x() == -1);
    REQUIRE(robot.get_y() == 0);
    robot.move();
    REQUIRE(robot.get_x() == -2);
}

TEST_CASE( "Place robot", "[simulation]" )
{
    Simulation sim(5, 5);
    REQUIRE(sim.robot_ == nullptr);
    sim.place_robot(2, 3, "NORTH");
    REQUIRE(sim.robot_ != nullptr);
    REQUIRE(sim.robot_->get_x() == 2);
    REQUIRE(sim.robot_->get_y() == 3);
    REQUIRE(sim.robot_->get_dir() == NORTH);

    sim.remove_robot();
    sim.place_robot(2, 3, "EAST");
    REQUIRE(sim.robot_->get_dir() == EAST);
    sim.remove_robot();
    sim.place_robot(2, 3, "SOUTH");
    REQUIRE(sim.robot_->get_dir() == SOUTH);
    sim.remove_robot();
    sim.place_robot(2, 3, "WEST");
    REQUIRE(sim.robot_->get_dir() == WEST);
}

TEST_CASE( "Remove robot", "[simulation]" )
{
    Simulation sim(5, 5);
    sim.place_robot(0, 0, "NORTH");
    REQUIRE(sim.robot_ != nullptr);
    sim.remove_robot();
    REQUIRE(sim.robot_ == nullptr);
}

TEST_CASE( "Place robot (negative)", "[simulation]" )
{
    Simulation sim(5, 5);
    sim.place_robot(6, 3, "NORTH");
    REQUIRE(sim.robot_ == nullptr);
    sim.remove_robot();
    // Test if y is checked correctly
    sim.place_robot(3, 6, "NORTH");
    REQUIRE(sim.robot_ == nullptr);
}

TEST_CASE( "Test reporting robot's position", "[simulation]" )
{
    Simulation sim(5, 5);
    std::string report = sim.get_report();
    REQUIRE("" == report);

    sim.place_robot(5, 5, "EAST");
    report = sim.get_report();
    REQUIRE("5,5,EAST" == report);
}

TEST_CASE( "Test moving out of bounds (should be no reaction)", "[simulation]" )
{
    Simulation sim(5, 5);
    SECTION("Move out of bounds NORTH")
    {
        sim.place_robot(5, 5, "NORTH");
        sim.move_robot();
        REQUIRE(sim.robot_->get_x() == 5);
        REQUIRE(sim.robot_->get_y() == 5);
    }
    SECTION("Move out of bounds EAST")
    {
        sim.place_robot(5, 5, "EAST");
        sim.move_robot();
        REQUIRE(sim.robot_->get_x() == 5);
        REQUIRE(sim.robot_->get_y() == 5);
    }
    SECTION("Move out of bounds SOUTH")
    {
        sim.place_robot(0, 0, "SOUTH");
        sim.move_robot();
        REQUIRE(sim.robot_->get_x() == 0);
        REQUIRE(sim.robot_->get_y() == 0);
    }
    SECTION("Move out of bounds WEST")
    {
        sim.place_robot(0, 0, "WEST");
        sim.move_robot();
        REQUIRE(sim.robot_->get_x() == 0);
        REQUIRE(sim.robot_->get_y() == 0);
    }
}

TEST_CASE( "Test coordinates cheking in Board", "[board]" )
{
    Board board(5, 5);

    SECTION( "Check in bounds" ) {
        auto x_pos = GENERATE(range(0, 6));
        auto y_pos = GENERATE(range(0, 6));
        REQUIRE(board.coordinates_fit(x_pos, y_pos));
    }
    SECTION( "Check both out of bounds" ) {
        auto x_pos = GENERATE(-10, -1, 6, 100);
        auto y_pos = GENERATE(-10, -1, 6, 100);
        REQUIRE(!board.coordinates_fit(x_pos, y_pos));
    }
    SECTION( "Check x out of bounds" ) {
        auto x_pos = GENERATE(-10, -1, 6, 100);
        auto y_pos = 0;
        REQUIRE(!board.coordinates_fit(x_pos, y_pos));
    }
    SECTION( "Check y out of bounds" ) {
        auto x_pos = 0;
        auto y_pos = GENERATE(-10, -1, 6, 100);
        REQUIRE(!board.coordinates_fit(x_pos, y_pos));
    }
}
