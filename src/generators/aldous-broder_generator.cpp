/**
 * @author      : Julian Hofmann
 * @created     : 01/09/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <stack>
#include <vector>

#include "../maze.h"
#include "../random.h"
#include "aldous-broder_generator.h"

// ==================== PUBLIC ====================

void AldousBroderGenerator::generate(Maze &maze)
{
    if (maze.size(GridType::CELLS) == 0)
        return;

    try
    {
        maze.clear();

        setStage(STAGE_GENERATING);
        Point currentCell{maze.convertToPoint(random<std::size_t>(0, maze.size(GridType::CELLS)), GridType::CELLS)};

        std::size_t visitedCells{1};
        maze.set(currentCell, GridType::CELLS, true);

        while (visitedCells < maze.size(GridType::CELLS)) 
        {
            std::vector neighbors {maze.getNeighbors(currentCell, false)};
            std::pair neighbor {neighbors[random<std::size_t>(0, neighbors.size() - 1)]};

            if (!maze.get(neighbor.first, GridType::CELLS))
            {
                maze.setWallOfCell(currentCell, neighbor.second, true);
                ++visitedCells;
                maze.set(neighbor.first, GridType::CELLS, true);
                updateProgress(static_cast<float>(visitedCells) / maze.size(GridType::CELLS));
            }
            currentCell = neighbor.first;
        }

        setStage(STAGE_FINISHED);
    } catch (const std::exception&)
    {
        setStage(STAGE_FAILURE);
        throw;
    }
}
