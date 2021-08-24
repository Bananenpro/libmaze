/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <catch2/catch.hpp>
#include <iostream>

#include "../../src/maze.h"
#include "../../src/exporters/png_exporter.h"
#include "../../src/loaders/png_loader.h"

SCENARIO("Exporting/loading maze as png")
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
            float exportPreparingProgress{};
            float exportWorkingProgress{};
            bool exportFinished{};

            exporter.addCallback([&exportPreparingProgress, &exportWorkingProgress, &exportFinished](PNGExporter::Stage stage, long millis, float progress)
            {
                REQUIRE(!(progress < 0 || progress > 1));

                switch(stage)
                {
                case PNGExporter::Stage::PREPARING:
                    exportPreparingProgress = progress;
                    break;
                case PNGExporter::Stage::WORKING:
                    exportWorkingProgress = progress;
                    break;
                case PNGExporter::Stage::FINISHED:
                    exportFinished = true;
                    break;
                default:
                    REQUIRE(false);
                }
            });

            maze.save(exporter, "maze.png");

            THEN("All progress callbacks are working")
            {
                REQUIRE(exportPreparingProgress == 1);
                REQUIRE(exportWorkingProgress == 1);
                REQUIRE(exportFinished);
            }

            GIVEN("A PNGLoader object")
            {
                PNGLoader loader;
                WHEN("Loading the maze")
                {
                    float loadPreparingProgress{};
                    float loadWorkingProgress{};
                    bool loadFinished{};

                    loader.addCallback([&loadPreparingProgress, &loadWorkingProgress, &loadFinished](PNGLoader::Stage stage, long millis, float progress)
                    {
                        REQUIRE(!((progress < 0 && progress != -1) || progress > 1));

                        switch(stage)
                        {
                        case PNGLoader::Stage::PREPARING:
                            loadPreparingProgress = progress;
                            break;
                        case PNGLoader::Stage::WORKING:
                            loadWorkingProgress = progress;
                            break;
                        case PNGLoader::Stage::FINISHED:
                            loadFinished = true;
                            break;
                        default:
                            REQUIRE(false);
                        }
                    });

                    Maze loadedMaze {Maze::load(loader, "maze.png")};

                    THEN("All progress callbacks are working")
                    {
                        REQUIRE(loadPreparingProgress == 1);
                        REQUIRE(loadWorkingProgress == 1);
                        REQUIRE(loadFinished);
                    }

                    THEN("The loaded maze is the same as the exported maze")
                    {
                        REQUIRE(maze.width(GridType::ALL) == loadedMaze.width(GridType::ALL));
                        REQUIRE(maze.height(GridType::ALL) == loadedMaze.height(GridType::ALL));

                        bool allCellsSame{true};
                        for (int i{}; i < maze.size(GridType::ALL); ++i)
                        {
                            if (maze.get(i, GridType::ALL) != loadedMaze.get(i, GridType::ALL))
                            {
                                allCellsSame = false;
                                break;
                            }
                        }

                        REQUIRE(allCellsSame);
                    }
                }
            }
        }
    }
}
