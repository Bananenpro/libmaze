/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <stack>
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

        std::stack<Point> stack{};

        Point currentCell{};
        maze.set(currentCell, GridType::CELLS, true);
        stack.push(currentCell);

        std::size_t visitedCells{1};

        while (!stack.empty()) {
            currentCell = stack.top();
            stack.pop();

            std::vector<std::pair<Point, Direction>> neighbors {maze.getNeighbors(currentCell, true)};

            if (!neighbors.empty()) {
                stack.push(currentCell);

                std::size_t randomIndex {random<std::size_t>(0, neighbors.size() - 1)};
                maze.setWallOfCell(currentCell, neighbors[randomIndex].second, true);

                currentCell = neighbors[randomIndex].first;

                maze.set(currentCell, GridType::CELLS, true);
                ++visitedCells;

                updateProgress((float)visitedCells / maze.size(GridType::CELLS));

                stack.push(currentCell);
            }
        }

        setStage(STAGE_FINISHED);
    } catch (const std::exception &) {
        setStage(STAGE_FAILURE);
        throw;
    }
}
