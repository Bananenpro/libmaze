/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <stack>
#include <vector>

#include "depth-first_generator.h"
#include "../maze.h"
#include "../random.h"

// ==================== PUBLIC ====================

void DepthFirstGenerator::generate(Maze& maze)
{
    if (maze.size(GridType::CELLS) == 0)
        return;

    try
    {
        setStage(STAGE_GENERATING);

        maze.clear();

        std::stack<Point> stack{};

        Point currentCell {};
        maze.set(currentCell, GridType::CELLS, true);
        stack.push(currentCell);

        std::size_t visitedCells{1};

        while(!stack.empty())
        {
            currentCell = stack.top();
            stack.pop();

            std::vector<Direction> possibleDirections;


            if (currentCell.y > 0 && !maze.get({currentCell.x, currentCell.y - 1}, GridType::CELLS))
                possibleDirections.push_back(Direction::UP);

            if (currentCell.x < maze.width(GridType::CELLS) - 1 && !maze.get({currentCell.x + 1, currentCell.y}, GridType::CELLS))
                possibleDirections.push_back(Direction::RIGHT);

            if (currentCell.y < maze.height(GridType::CELLS) - 1 && !maze.get({currentCell.x, currentCell.y + 1}, GridType::CELLS))
                possibleDirections.push_back(Direction::DOWN);

            if (currentCell.x > 0 && !maze.get({currentCell.x - 1, currentCell.y}, GridType::CELLS))
                possibleDirections.push_back(Direction::LEFT);


            if (!possibleDirections.empty())
            {
                stack.push(currentCell);

                Direction direction {possibleDirections[random<int>(0, possibleDirections.size() - 1)]};

                maze.setWallOfCell(currentCell, direction, true);

                switch(direction)
                {
                case Direction::UP:
                    currentCell = {currentCell.x, currentCell.y - 1};
                    break;
                case Direction::RIGHT:
                    currentCell = {currentCell.x + 1, currentCell.y};
                    break;
                case Direction::DOWN:
                    currentCell = {currentCell.x, currentCell.y + 1};
                    break;
                case Direction::LEFT:
                    currentCell = {currentCell.x - 1, currentCell.y};
                    break;
                }

                maze.set(currentCell, GridType::CELLS, true);
                ++visitedCells;

                updateProgress((float)visitedCells / maze.size(GridType::CELLS));

                stack.push(currentCell);
            }
        }

        setStage(STAGE_FINISHED);
    } catch (const std::exception&)
    {
        setStage(STAGE_FAILURE);
        throw;
    }
}
