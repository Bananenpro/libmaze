/**
 * @author      : Julian Hofmann
 * @created     : 14/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <stdexcept>
#include <string_view>

#include "maze.h"


// =================== PUBLIC ====================


// ********** Constructors/Destructor **********

Maze::Maze(std::size_t width, std::size_t height) 
    : mData{}, mGridWidth{2 * width + 1}, mGridHeight{2 * height + 1}
{
    if (width == 0)
        mGridWidth = 0;

    if (height == 0)
        mGridHeight = 0;

    mData.resize(size(GridType::ALL));
}

Maze::~Maze()
{}


// ********** Converters **********

std::size_t Maze::convertPos(std::size_t pos, GridType targetGridType) const
{
    switch (targetGridType)
    {
        case GridType::ALL:
            if (pos >= size(GridType::CELLS))
                throw std::out_of_range("Pos is not in maze");
            return convertToPos(convertPoint(convertToPoint(pos, GridType::CELLS), GridType::ALL), GridType::ALL);
        case GridType::CELLS:
            if (pos >= size(GridType::ALL))
                throw std::out_of_range("Pos is not in maze");
            return convertToPos(convertPoint(convertToPoint(pos, GridType::ALL), GridType::CELLS), GridType::CELLS);
        default:
            throw std::invalid_argument("Unknown grid type");
    }
}

Point Maze::convertPoint(const Point& point, GridType targetGridType) const
{
    switch (targetGridType)
    {
        case GridType::ALL:
            if (point.x >= width(GridType::CELLS) || point.y >= height(GridType::CELLS))
                throw std::out_of_range("Point is not in maze");
            return {point.x * 2 + 1, point.y * 2 + 1};
        case GridType::CELLS:
            if (point.x >= width(GridType::ALL) || point.y >= height(GridType::ALL))
                throw std::out_of_range("Point is not in maze");
            if (point.x % 2 == 0 || point.y == 0)
                throw std::invalid_argument("Point is not a cell");
            return {(point.x - 1) / 2, (point.y - 1) / 2};
        default:
            throw std::invalid_argument("Unknown grid type");
    }
}

std::size_t Maze::convertToPos(const Point& point, GridType gridType) const
{
    if (point.x >= width(gridType) || point.y >= height(gridType))
        throw std::out_of_range("Point not in maze");
    return point.y * width(gridType) + point.x;
}

Point Maze::convertToPoint(std::size_t pos, GridType gridType) const
{
    if (pos >= size(gridType))
        throw std::out_of_range("Pos not in maze");

    if (pos == 0)
        return {0, 0};
    
    return {pos % width(gridType), pos / width(gridType)};
}


// ********** Getters **********

bool Maze::get(std::size_t pos, GridType gridType) const
{
    return mData.at(getIndexOf(pos, gridType));
}

bool Maze::get(const Point& point, GridType gridType) const
{
    return mData.at(getIndexOf(point, gridType));
}

bool Maze::getWallOfCell(std::size_t pos, Direction direction) const
{
    return mData.at(getIndexOfWallOfCell(pos, direction));
}

bool Maze::getWallOfCell(const Point& point, Direction direction) const
{
    return mData.at(getIndexOfWallOfCell(point, direction));
}

std::size_t Maze::width(GridType gridType) const
{
    switch(gridType)
    {
    case GridType::ALL:
        return mGridWidth;
    case GridType::CELLS:
        if (mGridWidth == 0)
            return 0;
        return (mGridWidth - 1) / 2;
    }

    throw std::invalid_argument("Unknown grid type");
}

std::size_t Maze::height(GridType gridType) const
{
    switch(gridType)
    {
    case GridType::ALL:
        return mGridHeight;
    case GridType::CELLS:
        if (mGridHeight == 0)
            return 0;
        return (mGridHeight - 1) / 2;
    }

    throw std::invalid_argument("Unknown grid type");
}

std::size_t Maze::size(GridType gridType) const
{
    return width(gridType) * height(gridType);
}


// ********** Setters **********

void Maze::set(std::size_t pos, GridType gridType, bool value)
{
    mData.at(getIndexOf(pos, gridType)) = value;
}

void Maze::set(const Point& point, GridType gridType, bool value)
{
    mData.at(getIndexOf(point, gridType)) = value;
}

void Maze::setWallOfCell(std::size_t pos, Direction direction, bool value)
{
    mData.at(getIndexOfWallOfCell(pos, direction)) = value;
}

void Maze::setWallOfCell(const Point& point, Direction direction, bool value)
{
    mData.at(getIndexOfWallOfCell(point, direction)) = value;
}


// ********** Other **********

void Maze::save(IExporter& exporter, const std::string& path) const
{
    exporter.save(*this, path);
}

// ==================== PRIVATE ====================


// ********** Get Index **********

std::size_t Maze::getIndexOf(std::size_t pos, GridType gridType) const
{
    switch(gridType)
    {
        case GridType::ALL:
            return pos;
        case GridType::CELLS:
            return convertPos(pos, GridType::ALL);
        default:
            throw std::invalid_argument("Unknown grid type");
    }
}

std::size_t Maze::getIndexOf(const Point& point, GridType gridType) const
{
    return getIndexOf(convertToPos(point, gridType), gridType);
}

std::size_t Maze::getIndexOfWallOfCell(std::size_t pos, Direction direction) const
{
    return getIndexOfWallOfCell(convertToPoint(pos, GridType::CELLS), direction);
}

std::size_t Maze::getIndexOfWallOfCell(const Point& point, Direction direction) const
{
    Point totalPoint {convertPoint(point, GridType::ALL)};
    switch (direction)
    {
        case Direction::UP:
            return getIndexOf({totalPoint.x, totalPoint.y - 1}, GridType::ALL);
        case Direction::RIGHT:
            return getIndexOf({totalPoint.x + 1, totalPoint.y}, GridType::ALL);
        case Direction::DOWN:
            return getIndexOf({totalPoint.x, totalPoint.y + 1}, GridType::ALL);
        case Direction::LEFT:
            return getIndexOf({totalPoint.x - 1, totalPoint.y}, GridType::ALL);
        default:
            throw std::invalid_argument("Unknown direction");
    }
}
