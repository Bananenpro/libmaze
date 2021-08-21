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
#include "png_exporter.h"

// ==================== PUBLIC ====================

void PNGExporter::save(const Maze &maze, const std::string& path)
{
    png_structp png {nullptr};
    png_infop info {nullptr};


    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png)
    {
        throw std::runtime_error("Couldn't create png struct");
    }

    info = png_create_info_struct(png);
    if (!info)
    {
        throw std::runtime_error("Couldn't create png info struct");
    }

    png_set_compression_level(png, static_cast<int>(mCompression));
    png_set_IHDR(png, info, maze.width(GridType::ALL), maze.height(GridType::ALL), 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_bytepp rows {nullptr};

    try
    {
        rows = generatePixelData(maze);
        write(png, info, rows, path);

        setStage(Stage::FINISHED);
    }
    catch (const std::exception&)
    {
        for(std::size_t y{0}; y < maze.height(GridType::ALL); ++y)
        {
            delete[] rows[y];
        }
        delete[] rows;

        throw;
    }
}


// ********** Getters **********

PNGExporter::Compression PNGExporter::compression() const
{
    return mCompression;
}


// ********** Setters **********

void PNGExporter::setCompression(Compression compression)
{
    mCompression = compression;
}


// ==================== PRIVATE ====================

png_bytepp PNGExporter::generatePixelData(const Maze &maze)
{
    setStage(Stage::PREPARING);

    std::size_t calculatedPixels {0};

    png_bytepp rows = new png_bytep[maze.height(GridType::ALL)];

    for (std::size_t y{0}; y < maze.height(GridType::ALL); ++y)
    {
        rows[y] = new uint8_t[maze.width(GridType::ALL)];

        for (std::size_t x{0}; x < maze.width(GridType::ALL); ++x)
        {
            uint8_t colorValue = maze.get({x, y}, GridType::ALL) ? 255 : 0;

            rows[y][x] = colorValue;

            ++calculatedPixels;

            updateProgress((float)calculatedPixels / (float)maze.size(GridType::ALL));
        }
    }

    return rows;
}

void PNGExporter::write(png_structp png, png_infop pngInfo, png_bytepp rows, const std::string& path)
{
    setStage(Stage::WORKING);

    FILE *fp {fopen(path.c_str(), "wb")};

    if (!fp)
    {
        throw std::runtime_error("Couldn't open file '" + path + "' for writing'");
    }

    png_uint_32 height{};
    png_get_IHDR(png, pngInfo, nullptr, &height, nullptr, nullptr, nullptr, nullptr, nullptr);

    static ProgressReporter progressReporter = *this;
    static std::size_t rowCount = height;

    png_set_write_status_fn(png, [](png_structp png_ptr, png_uint_32 row, int pass)
    {
        progressReporter.updateProgress((float)row / rowCount);
    });

    png_init_io(png, fp);
    png_set_rows(png, pngInfo, rows);
    png_write_png(png, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);

    fclose(fp);
}
