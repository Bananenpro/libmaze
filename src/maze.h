/**
 * @author      : Julian Hofmann
 * @created     : 14/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef MAZE_H
#define MAZE_H

// ********** Includes **********

#include <vector>

#include "exporters/exporter.h"


// ********** Structs/Enums **********

struct Point
{
    std::size_t x{};
    std::size_t y{};
};

enum class GridType
{
    ALL, CELLS
};

enum class Direction
{
    TOP, RIGHT, BOTTOM, LEFT
};

class Maze final
{
private:
    // holds maze data including cells and walls
    std::vector<bool> mData;

    // number of walls + cells in x direction
    std::size_t mGridWidth;

    // number of walls + cells in y direction
    std::size_t mGridHeight;

public:

    // ********** Constructors/Destructor **********

    /**
     * @param width number of cells in x direction
     * @param height number of cells in y direction
     */
    Maze(std::size_t width, std::size_t height);
    ~Maze();


    // ********** Converters **********

    std::size_t convertPos(std::size_t pos, GridType targetGridType) const;
    Point convertPoint(const Point& point, GridType targetGridType) const;

    std::size_t convertToPos(const Point& point, GridType gridType) const;
    Point convertToPoint(std::size_t pos, GridType gridType) const;


    // ********** Getters **********

    /**
     * @return true for open wall/active cell
     */
    bool get(std::size_t pos, GridType gridType) const;

    /**
     * @return true for open wall/active cell
     */
    bool get(const Point& point, GridType gridType) const;

    /**
     * @param pos pos of cell in cell grid
     * @return true for open wall
     */
    bool getWallOfCell(std::size_t pos, Direction direction) const;

    /**
     * @param point coords of cell in cell grid
     * @return true for open wall
     */
    bool getWallOfCell(const Point& point, Direction direction) const;

    std::size_t width(GridType gridType) const;
    std::size_t height(GridType gridType) const;
    std::size_t size(GridType gridType) const;

    
    // ********** Setters **********

    /**
     * @param value true for open wall/active cell
     */
    void set(std::size_t pos, GridType gridType, bool value);

    /**
     * @param value true for open wall/active cell
     */
    void set(const Point& point, GridType gridType, bool value);

    /**
     * @param pos pos of cell in cell grid
     * @param value true for open wall
     */
    void setWallOfCell(std::size_t pos, Direction direction, bool value);

    /**
     * @param point coords of cell in cell grid
     * @param value true for open wall
     */
    void setWallOfCell(const Point& point, Direction direction, bool value);

    // ********** Other **********
    
    void save(IExporter& exporter, const std::string& path) const;

private:
    std::size_t getIndexOf(std::size_t pos, GridType gridType) const;
    std::size_t getIndexOf(const Point& point, GridType gridType) const;
    std::size_t getIndexOfWallOfCell(std::size_t pos, Direction direction) const;
    std::size_t getIndexOfWallOfCell(const Point& point, Direction direction) const;
};

#endif /* MAZE_H */
