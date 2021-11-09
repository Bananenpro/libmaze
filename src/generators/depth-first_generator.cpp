/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <vector>

#include "../maze.h"
#include "../random.h"
#include "depth-first_generator.h"

// ==================== PUBLIC ====================

void DepthFirstGenerator::generate(Maze &maze)
{
    if (maze.size(GridType::CELLS) == 0)
        return;

    try {
        setStage(STAGE_GENERATING);

        maze.clear();

        std::vector<Point> stack{};
        stack.reserve(maze.size(GridType::ALL) / 2);

        Point currentCell{};
        maze.set(currentCell, GridType::CELLS, true);
        stack.push_back(currentCell);

        std::size_t visitedCells{1};

        while (!stack.empty()) {
            currentCell = stack[stack.size() - 1];
            stack.pop_back();

            std::vector<std::pair<Point, Direction>> neighbors {maze.getNeighbors(currentCell, true)};

            if (!neighbors.empty()) {
                stack.push_back(currentCell);

                std::size_t randomIndex {random<std::size_t>(0, neighbors.size() - 1)};
                maze.setWallOfCell(currentCell, neighbors[randomIndex].second, true);

                currentCell = neighbors[randomIndex].first;

                maze.set(currentCell, GridType::CELLS, true);
                ++visitedCells;

                updateProgress((float)visitedCells / maze.size(GridType::CELLS));

                stack.push_back(currentCell);
            }
        }

        setStage(STAGE_FINISHED);
    } catch (const std::exception &) {
        setStage(STAGE_FAILURE);
        throw;
    }
}
