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
            Point p {maze.convertToPoint(i, GridType::CELLS)};
            maze.set(p, GridType::CELLS, true);

            if (p.y > 0)
                maze.setWallOfCell(p, Direction::UP, true);

            if (p.x < maze.width(GridType::CELLS) - 1)
                maze.setWallOfCell(p, Direction::RIGHT, true);

            if (p.y < maze.height(GridType::CELLS) - 1)
                maze.setWallOfCell(p, Direction::DOWN, true);

            if (p.x  > 0)
                maze.setWallOfCell(p, Direction::LEFT, true);
        }

        PNGExporter exporter;

        WHEN("Exporting the maze")
        {
            maze.save(exporter, "maze.png");

            // TODO: Verify the created file
        }
    }
}
