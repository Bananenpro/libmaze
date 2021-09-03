/**
 * @author      : Julian Hofmann
 * @created     : 02/09/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <catch2/catch.hpp>

#include "../../src/exporters/png_exporter.h"
#include "../../src/generators/aldous-broder_generator.h"
#include "../../src/maze.h"

SCENARIO("Generating a maze using the aldous-broder search algorithm")
{
    GIVEN("An empty maze and a AldousBroderGenerator object")
    {
        Maze maze(10, 10);

        AldousBroderGenerator generator;

        WHEN("Generating the maze")
        {
            float generatingProgress{};
            bool generatingFinished{};

            generator.addCallback([&generatingProgress, &generatingFinished](int stage, long millis, float progress) {
                REQUIRE(progress >= 0);
                REQUIRE(progress <= 1);

                switch (stage) {
                case AldousBroderGenerator::STAGE_GENERATING:
                    generatingProgress = progress;
                case AldousBroderGenerator::STAGE_FINISHED:
                    generatingFinished = true;
                }
            });

            maze.generate(generator);
            PNGExporter exporter;
            maze.save(exporter, "aldous-broder.png");

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
