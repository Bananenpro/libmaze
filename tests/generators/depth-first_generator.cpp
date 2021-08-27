/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <catch2/catch.hpp>

#include "../../src/exporters/png_exporter.h"
#include "../../src/generators/depth-first_generator.h"
#include "../../src/maze.h"

SCENARIO("Generating a maze using the depth-first search algorithm")
{
    GIVEN("An empty maze and a DepthFirstGenerator object")
    {
        Maze maze(10, 10);

        DepthFirstGenerator generator;

        WHEN("Generating the maze")
        {
            float generatingProgress{};
            bool generatingFinished{};

            generator.addCallback([&generatingProgress, &generatingFinished](int stage, long millis, float progress) {
                REQUIRE(progress >= 0);
                REQUIRE(progress <= 1);

                switch (stage) {
                case DepthFirstGenerator::STAGE_GENERATING:
                    generatingProgress = progress;
                case DepthFirstGenerator::STAGE_FINISHED:
                    generatingFinished = true;
                }
            });

            maze.generate(generator);

            THEN("All callbacks are called")
            {
                REQUIRE(generatingProgress == 1);
                REQUIRE(generatingFinished);
            }

            THEN("All cells are active")
            {
                bool allActive{true};
                for (std::size_t i{}; i < maze.size(GridType::CELLS); ++i) {
                    if (!maze.get(i, GridType::CELLS)) {
                        allActive = false;
                    }
                }

                REQUIRE(allActive);
            }
        }
    }
}
