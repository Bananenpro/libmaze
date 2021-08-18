/**
 * @author      : Julian Hofmann
 * @created     : 14/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <exception>
#include <catch2/catch.hpp>

#include "../src/maze.h"

SCENARIO("Creating maze", "[maze]")
{
    WHEN("The maze is created with small width and height")
    {
        Maze maze(10, 15);

        THEN("It has the correct cell grid size")
        {
            REQUIRE(maze.width(GridType::CELLS) == 10);
            REQUIRE(maze.height(GridType::CELLS) == 15);
            REQUIRE(maze.size(GridType::CELLS) == 150);
        }

        THEN("It has the correct grid size")
        {
            REQUIRE(maze.width(GridType::ALL) == 21);
            REQUIRE(maze.height(GridType::ALL) == 31);
            REQUIRE(maze.size(GridType::ALL) == 651);
        }

        THEN("All cells and walls are off")
        {
            bool all_off = true;

            for (std::size_t i = 0; i < maze.size(GridType::ALL); ++i)
            {
                if(maze.get(i, GridType::ALL))
                {
                    all_off = false;
                }
            }

            REQUIRE(all_off);
        }
    }

    WHEN("The maze is created with width and height of zero")
    {
        Maze maze(0, 0);

        THEN("It has a cell grid size of zero")
        {
            REQUIRE(maze.width(GridType::CELLS) == 0);
            REQUIRE(maze.height(GridType::CELLS) == 0);
            REQUIRE(maze.size(GridType::CELLS) == 0);
        }

        THEN("It has a grid size of zero")
        {
            REQUIRE(maze.width(GridType::ALL) == 0);
            REQUIRE(maze.height(GridType::ALL) == 0);
            REQUIRE(maze.size(GridType::ALL) == 0);
        }
    }
}

SCENARIO("Converting pos <-> point", "[maze]")
{
    GIVEN("An empty maze of size 3x2")
    {
        Maze maze(3, 2);

        WHEN("Converting complete grid positions to complete grid points")
        {
            Point point1 {maze.convertToPoint(0, GridType::ALL)};
            Point point2 {maze.convertToPoint(17, GridType::ALL)};

            THEN("The created points point to the same locations")
            {
                REQUIRE(point1.x == 0);
                REQUIRE(point1.y == 0);

                REQUIRE(point2.x == 3);
                REQUIRE(point2.y == 2);
            }
        }

        WHEN("Converting complete grid points to complete grid positions")
        {
            std::size_t pos1 {maze.convertToPos({0, 0}, GridType::ALL)};
            std::size_t pos2 {maze.convertToPos({3, 2}, GridType::ALL)};


            THEN("The created points point to the same locations")
            {
                REQUIRE(pos1 == 0);
                REQUIRE(pos2 == 17);
            }
        }

        WHEN("Converting cell grid positions to cell grid points")
        {
            Point point1 {maze.convertToPoint(0, GridType::CELLS)};
            Point point2 {maze.convertToPoint(1, GridType::CELLS)};
            Point point3 {maze.convertToPoint(5, GridType::CELLS)};

            THEN("The created points point to the same locations")
            {
                REQUIRE(point1.x == 0);
                REQUIRE(point1.y == 0);

                REQUIRE(point2.x == 1);
                REQUIRE(point2.y == 0);

                REQUIRE(point3.x == 2);
                REQUIRE(point3.y == 1);
            }
        }

        WHEN("Converting cell grid points to cell grid positions")
        {
            std::size_t pos1 {maze.convertToPos({0, 0}, GridType::CELLS)};
            std::size_t pos2 {maze.convertToPos({1, 0}, GridType::CELLS)};
            std::size_t pos3 {maze.convertToPos({2, 1}, GridType::CELLS)};


            THEN("The created points point to the same locations")
            {
                REQUIRE(pos1 == 0);
                REQUIRE(pos2 == 1);
                REQUIRE(pos3 == 5);
            }
        }
    }
}

SCENARIO("Converting cell grid <-> complete grid")
{
    GIVEN("An empty maze of size 3x2")
    {
        Maze maze(3, 2);

        WHEN("Converting cell grid positions to complete grid positions")
        {
            std::size_t pos1 {maze.convertPos(0, GridType::ALL)};
            std::size_t pos2 {maze.convertPos(2, GridType::ALL)};
            std::size_t pos3 {maze.convertPos(5, GridType::ALL)};

            THEN("The created positions point to the same locations")
            {
                REQUIRE(pos1 == 8);
                REQUIRE(pos2 == 12);
                REQUIRE(pos3 == 26);
            }
        }

        WHEN("Converting cell grid points to complete grid points")
        {
            Point point1 {maze.convertPoint({0, 0}, GridType::ALL)};
            Point point2 {maze.convertPoint({2, 0}, GridType::ALL)};
            Point point3 {maze.convertPoint({2, 1}, GridType::ALL)};

            THEN("The created points point to the same locations")
            {
                REQUIRE(point1.x == 1);
                REQUIRE(point1.y == 1);

                REQUIRE(point2.x == 5);
                REQUIRE(point2.y == 1);

                REQUIRE(point3.x == 5);
                REQUIRE(point3.y == 3);
            }
        }

        WHEN("Converting complete grid positions to valid cell grid positions")
        {
            std::size_t pos1 {maze.convertPos(8, GridType::CELLS)};
            std::size_t pos2 {maze.convertPos(12, GridType::CELLS)};
            std::size_t pos3 {maze.convertPos(26, GridType::CELLS)};

            THEN("The created positions point to the same locations")
            {
                REQUIRE(pos1 == 0);
                REQUIRE(pos2 == 2);
                REQUIRE(pos3 == 5);
            }
        }

        WHEN("Converting complete grid points to valid cell grid points")
        {
            Point point1 {maze.convertPoint({1, 1}, GridType::CELLS)};
            Point point2 {maze.convertPoint({5, 1}, GridType::CELLS)};
            Point point3 {maze.convertPoint({5, 3}, GridType::CELLS)};

            THEN("The created positions point to the same locations")
            {
                REQUIRE(point1.x == 0);
                REQUIRE(point1.y == 0);

                REQUIRE(point2.x == 2);
                REQUIRE(point2.y == 0);

                REQUIRE(point3.x == 2);
                REQUIRE(point3.y == 1);
            }
        }

        WHEN("Converting complete grid positions to invalid cell grid positions")
        {
            bool exception1{};
            try {maze.convertPos(0, GridType::CELLS);} catch(const std::invalid_argument&) {exception1 = true;}

            bool exception2{};
            try {maze.convertPos(1, GridType::CELLS);} catch(const std::invalid_argument&) {exception2 = true;}

            bool exception3{};
            try {maze.convertPos(11, GridType::CELLS);} catch(const std::invalid_argument&) {exception3 = true;}


            THEN("Invalid argument exceptions are thrown")
            {
                REQUIRE(exception1);
                REQUIRE(exception2);
                REQUIRE(exception3);
            }
        }

        WHEN("Converting complete grid points to invalid cell grid points")
        {
            bool exception1{};
            try {maze.convertPoint({0,0}, GridType::CELLS);} catch(const std::invalid_argument&) {exception1 = true;}

            bool exception2{};
            try {maze.convertPoint({1, 0}, GridType::CELLS);} catch(const std::invalid_argument&) {exception2 = true;}

            bool exception3{};
            try {maze.convertPoint({4, 1}, GridType::CELLS);} catch(const std::invalid_argument&) {exception3 = true;}

            THEN("Invalid argument exceptions are thrown")
            {
                REQUIRE(exception1);
                REQUIRE(exception2);
                REQUIRE(exception3);
            }
        }

        WHEN("Converting out of range cell grid position to complete grid position")
        {
            bool exception{};
            try {maze.convertPos(6, GridType::ALL);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }

        WHEN("Converting out of range complete grid position to cell grid position")
        {
            bool exception{};
            try {maze.convertPos(36, GridType::CELLS);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }

        WHEN("Converting out of range cell grid point to complete grid point")
        {
            bool exception{};
            try {maze.convertPoint({3, 2}, GridType::ALL);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }

        WHEN("Converting out of range complete grid point to cell grid point")
        {
            bool exception{};
            try {maze.convertPoint({7, 5}, GridType::CELLS);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }

        WHEN("Converting out of range cell grid position to cell grid point")
        {
            bool exception{};
            try {maze.convertToPoint(6, GridType::CELLS);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }

        WHEN("Converting out of range cell grid point to cell grid position")
        {
            bool exception{};
            try {maze.convertToPos({3, 2}, GridType::CELLS);} catch (const std::out_of_range&) {exception = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception);
            }
        }
    }
}

SCENARIO("Changing maze data", "[maze]")
{
    GIVEN("An empty 3x2 maze")
    {
        Maze maze(3, 2);

        WHEN("Changing cells by cell grid position")
        {
            REQUIRE(!maze.get(0, GridType::CELLS));
            maze.set({0, 0}, GridType::CELLS, true);
            REQUIRE(maze.get(0, GridType::CELLS));
            maze.set(0, GridType::CELLS, false);
            REQUIRE(!maze.get(0, GridType::CELLS));

            REQUIRE(!maze.get(5, GridType::CELLS));
            maze.set(5, GridType::CELLS, true);
            REQUIRE(maze.get(5, GridType::CELLS));
            maze.set(5, GridType::CELLS, false);
            REQUIRE(!maze.get(5, GridType::CELLS));
        }

        WHEN("Changing cells by cell grid point")
        {
            REQUIRE(!maze.get({0, 0}, GridType::CELLS));
            maze.set({0, 0}, GridType::CELLS, true);
            REQUIRE(maze.get({0, 0}, GridType::CELLS));
            maze.set({0, 0}, GridType::CELLS, false);
            REQUIRE(!maze.get({0, 0}, GridType::CELLS));

            REQUIRE(!maze.get({2, 1}, GridType::CELLS));
            maze.set({2, 1}, GridType::CELLS, true);
            REQUIRE(maze.get({2, 1}, GridType::CELLS));
            maze.set({2, 1}, GridType::CELLS, false);
            REQUIRE(!maze.get({2, 1}, GridType::CELLS));
        }

        WHEN("Changing cells by total grid position")
        {
            REQUIRE(!maze.get(8, GridType::ALL));
            maze.set(8, GridType::ALL, true);
            REQUIRE(maze.get(8, GridType::ALL));
            maze.set(8, GridType::ALL, false);
            REQUIRE(!maze.get(8, GridType::ALL));

            REQUIRE(!maze.get(26, GridType::ALL));
            maze.set(26, GridType::ALL, true);
            REQUIRE(maze.get(26, GridType::ALL));
            maze.set(26, GridType::ALL, false);
            REQUIRE(!maze.get(26, GridType::ALL));
        }

        WHEN("Changing cells by total grid point")
        {
            REQUIRE(!maze.get({1, 1}, GridType::ALL));
            maze.set({1, 1}, GridType::ALL, true);
            REQUIRE(maze.get({1, 1}, GridType::ALL));
            maze.set({1, 1}, GridType::ALL, false);
            REQUIRE(!maze.get({1, 1}, GridType::ALL));

            REQUIRE(!maze.get({5, 3}, GridType::ALL));
            maze.set({5, 3}, GridType::ALL, true);
            REQUIRE(maze.get({5, 3}, GridType::ALL));
            maze.set({5, 3}, GridType::ALL, false);
            REQUIRE(!maze.get({5, 3}, GridType::ALL));
        }

        WHEN("Changing walls of cells")
        {
            REQUIRE(!maze.getWallOfCell({0, 0}, Direction::RIGHT));
            maze.setWallOfCell({0, 0}, Direction::RIGHT, true);
            REQUIRE(maze.getWallOfCell({0, 0}, Direction::RIGHT));
            REQUIRE(maze.getWallOfCell({1, 0}, Direction::LEFT));
            REQUIRE(maze.get(9, GridType::ALL));
            maze.setWallOfCell({1, 0}, Direction::LEFT, false);
            REQUIRE(!maze.getWallOfCell({0, 0}, Direction::RIGHT));
            REQUIRE(!maze.get(9, GridType::ALL));

            REQUIRE(!maze.getWallOfCell({0, 0}, Direction::BOTTOM));
            maze.setWallOfCell({0, 0}, Direction::BOTTOM, true);
            REQUIRE(maze.getWallOfCell({0, 0}, Direction::BOTTOM));
            REQUIRE(maze.getWallOfCell({0, 1}, Direction::TOP));
            REQUIRE(maze.get(15, GridType::ALL));
            maze.setWallOfCell({0, 1}, Direction::TOP, false);
            REQUIRE(!maze.getWallOfCell({0, 0}, Direction::BOTTOM));
            REQUIRE(!maze.get(15, GridType::ALL));

            REQUIRE(!maze.getWallOfCell(0, Direction::LEFT));
            maze.setWallOfCell({0, 0}, Direction::LEFT, true);
            REQUIRE(maze.getWallOfCell(0, Direction::LEFT));

            REQUIRE(!maze.getWallOfCell(5, Direction::RIGHT));
            maze.setWallOfCell({2, 1}, Direction::RIGHT, true);
            REQUIRE(maze.getWallOfCell(5, Direction::RIGHT));
        }

        WHEN("Changing out of range cells by cell grid point")
        {
            bool exception1{};
            try {maze.set({3, 0}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception1 = true;}
            bool exception2{};
            try {maze.set({0, 2}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception2 = true;}
            bool exception3{};
            try {maze.set({3, 2}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception3 = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception1);
                REQUIRE(exception2);
                REQUIRE(exception3);
            }
        }

        WHEN("Changing out of bounds cells by complete grid point")
        {
            bool exception1{};
            try {maze.set({7, 0}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception1 = true;}
            bool exception2{};
            try {maze.set({0, 5}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception2 = true;}
            bool exception3{};
            try {maze.set({7, 5}, GridType::CELLS, true);} catch(const std::out_of_range&) {exception3 = true;}

            THEN("An out of range exception is thrown")
            {
                REQUIRE(exception1);
                REQUIRE(exception2);
                REQUIRE(exception3);
            }
        }
    }
}
