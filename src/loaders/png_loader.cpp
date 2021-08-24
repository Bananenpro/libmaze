/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <stdexcept>
#include <stdio.h>

#include "../maze.h"
#include "png_loader.h"

// ==================== PUBLIC ====================

Maze PNGLoader::load(const std::string& path)
{
    png_structp png {png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)};
    if (!png)
        throw std::runtime_error("Couldn't create png struct");

    png_infop info {png_create_info_struct(png)};
    if (!info)
        throw std::runtime_error("Couldn't create png info struct");

    png_bytepp rows {readFile(png, info, path)};
    Maze maze {constructMaze(rows, png_get_image_width(png, info), png_get_image_height(png, info))};

    png_destroy_read_struct(&png, &info, nullptr);

    setStage(Stage::FINISHED);

    return maze;
}


// ==================== PRIVATE ====================

Maze PNGLoader::constructMaze(png_bytepp rows, std::size_t width, std::size_t height)
{
    setStage(Stage::WORKING);

    Maze maze((width - 1) / 2, (height - 1) / 2);

    std::size_t loadedCells {};
    for (std::size_t y{0}; y < height; ++y)
    {
        for (std::size_t x{0}; x < width; ++x)
        {
            if (rows[y][x] != 0 && rows[y][x] != 255)
                throw std::runtime_error("Unknown color (only pure black(0) and pure white(255) are allowed)");
            maze.set({x, y}, GridType::ALL, rows[y][x]);

            ++loadedCells;
            updateProgress((float)loadedCells / (float)(width * height));
        }
    }

    bool foundEntrace{};
    bool foundExit{};
    for (std::size_t x{0}; x < maze.width(GridType::ALL); ++x)
    {
        if (maze.get({x, 0}, GridType::ALL))
        {
            maze.setEntrancePos(x, GridType::ALL);
            if (foundEntrace)
                throw std::runtime_error("Multiple entrances are not allowed");
            else
                foundEntrace = true;
        }

        if (maze.get({x, maze.height(GridType::ALL) - 1}, GridType::ALL))
        {
            maze.setExitPos(x, GridType::ALL);
            if (foundExit)
                throw std::runtime_error("Multiple exits are not allowed");
            else
                foundExit = true;
        }
    }

    if (!foundEntrace)
        throw std::runtime_error("No entrance");

    if (!foundExit)
        throw std::runtime_error("No exit");

    return maze;
}

png_bytepp PNGLoader::readFile(png_structp png, png_infop pngInfo, const std::string& path)
{
    setStage(Stage::PREPARING);
    updateProgress(-1);

    png_byte header[8];

    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp)
    {
        throw std::runtime_error("Couldn't open '" + path + "' for reading");
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        throw std::runtime_error("'" + path + "' is not a PNG file");
    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, pngInfo);

    unsigned int height {png_get_image_height(png, pngInfo)};

    png_byte colorType = png_get_color_type(png, pngInfo);
    if (colorType != PNG_COLOR_TYPE_GRAY)
        throw std::runtime_error("Invalid color type (must be PNG_COLOR_TYPE_GRAY)");

    png_byte bitDepth = png_get_bit_depth(png, pngInfo);
    if (bitDepth != 8)
        throw std::runtime_error("Invalid bit depth (must be 8)");

    png_read_update_info(png, pngInfo);

    png_bytepp rows {new png_bytep[height]};
    for (unsigned int y {0}; y < height; ++y)
        rows[y] = new png_byte[png_get_rowbytes(png, pngInfo)];

    png_read_image(png, rows);

    png_read_end(png, pngInfo);

    fclose(fp);

    updateProgress(1);

    return rows;
}
