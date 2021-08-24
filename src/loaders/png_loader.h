/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef PNG_LOADER_H
#define PNG_LOADER_H

// ********** Includes *********

#include <png.h>

#include "loader.h"


class PNGLoader : public ILoader
{
public:
    Maze load(const std::string& path) override;

private:
    Maze constructMaze(png_bytepp rows, std::size_t width, std::size_t height);
    png_bytepp readFile(png_structp png, png_infop pngInfo, const std::string& path);
};

#endif /* PNG_LOADER_H */

