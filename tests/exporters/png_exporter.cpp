/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <catch2/catch.hpp>

#include "../../src/maze.h"
#include "../../src/exporters/png_exporter.h"

SCENARIO("Exporting maze")
{
    GIVEN("A maze and a PNGExporter object")
    {
        Maze maze(10, 10);

        for (std::size_t i{0}; i < maze.size(GridType::CELLS); ++i)
        {
            maze.set(i, GridType::CELLS, true);
            maze.setWallOfCell(i, Direction::UP, true);
            maze.setWallOfCell(i, Direction::RIGHT, true);
            maze.setWallOfCell(i, Direction::LEFT, true);
            maze.setWallOfCell(i, Direction::DOWN, true);
        }

        PNGExporter exporter;

        WHEN("Exporting the maze")
        {
            maze.save(exporter, "maze.png");

            // TODO: Verify the created file
        }
    }
}
