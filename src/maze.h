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
#include "generators/generator.h"
#include "loaders/loader.h"

// ********** Structs/Enums **********

struct Point {
    std::size_t x{};
    std::size_t y{};
};

enum class GridType { ALL, CELLS };

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Maze final
{
  private:
    // holds maze data including cells and walls
    std::vector<bool> mData;

    // number of walls + cells in x direction
    const std::size_t mGridWidth;

    // number of walls + cells in y direction
    const std::size_t mGridHeight;

    // x value of entrance in cell grid
    std::size_t mEntrancePos;

    // x value of exit in cell grid
    std::size_t mExitPos;

  public:
    // ********** Constructors/Destructor **********

    /**
     * @param width number of cells in x direction
     * @param height number of cells in y direction
     */
    Maze(std::size_t width, std::size_t height);
    /**
     * @param width number of cells in x direction
     * @param height number of cells in y direction
     * @param entrancePos x value of entrance in cell grid
     * @param exitPos x value of exit in cell grid
     */
    Maze(std::size_t width, std::size_t height, std::size_t entrancePos, std::size_t exitPos);
    ~Maze();

  private:
    void init();

  public:
    // ********** Converters **********

    std::size_t convertPos(std::size_t pos, GridType targetGridType) const;
    Point convertPoint(const Point &point, GridType targetGridType) const;

    std::size_t convertToPos(const Point &point, GridType gridType) const;
    Point convertToPoint(std::size_t pos, GridType gridType) const;

    // ********** Getters **********

    /**
     * @return true for open wall/active cell
     */
    bool get(std::size_t pos, GridType gridType) const;

    /**
     * @return true for open wall/active cell
     */
    bool get(const Point &point, GridType gridType) const;

    /**
     * @param pos pos of cell in cell grid
     * @return true for open wall
     */
    bool getWallOfCell(std::size_t pos, Direction direction) const;

    /**
     * @param point coords of cell in cell grid
     * @return true for open wall
     */
    bool getWallOfCell(const Point &point, Direction direction) const;

    std::size_t width(GridType gridType) const;
    std::size_t height(GridType gridType) const;
    std::size_t size(GridType gridType) const;

    /**
     * @return x value of entrance in cell grid
     */
    std::size_t entrancePos(GridType gridType) const;

    /**
     * @return x value of exit in cell grid
     */
    std::size_t exitPos(GridType gridType) const;

    /**
     * @return all neighbors of cell in cell grid
     */
    std::vector<std::pair<Point, Direction>> getNeighbors(Point point, bool onlyUnvisited);

    // ********** Setters **********

    /**
     * @param value true for open wall/active cell
     */
    void set(std::size_t pos, GridType gridType, bool value);

    /**
     * @param value true for open wall/active cell
     */
    void set(const Point &point, GridType gridType, bool value);

    /**
     * @param pos pos of cell in cell grid
     * @param value true for open wall
     */
    void setWallOfCell(std::size_t pos, Direction direction, bool value);

    /**
     * @param point coords of cell in cell grid
     * @param value true for open wall
     */
    void setWallOfCell(const Point &point, Direction direction, bool value);

    /**
     * @param pos x value of entrance
     */
    void setEntrancePos(std::size_t pos, GridType gridType);

    /**
     * @param pos x value of exit
     */
    void setExitPos(std::size_t pos, GridType gridType);

    /**
     * clears all cells and walls except the entrance and the exit
     */
    void clear();

    // ********** Other **********

    void save(IExporter &exporter, const std::string &path) const;
    static Maze load(ILoader &loader, const std::string &path);
    void generate(IGenerator &generator);

  private:
    std::size_t getIndexOf(std::size_t pos, GridType gridType) const;
    std::size_t getIndexOf(const Point &point, GridType gridType) const;
    std::size_t getIndexOfWallOfCell(std::size_t pos, Direction direction) const;
    std::size_t getIndexOfWallOfCell(const Point &point, Direction direction) const;
};

#endif /* MAZE_H */
