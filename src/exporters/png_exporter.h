/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef PNGEXPORTER_H
#define PNGEXPORTER_H

// ********** Includes *********

#include <png.h>

#include "exporter.h"


class PNGExporter : public IExporter
{
public:
    enum Compression
    {
        OFF, VERY_LOW, LOW, MEDIUM_LOW, MEDIUM, MEDIUM_HIGH, HIGH, VERY_HIGH, EXTREME, FULL
    };

    Compression mCompression {VERY_LOW};

public:
    void save(const Maze &maze, const std::string& path) override;


    // ********** Getters **********

    Compression compression() const;


    // ********** Setters **********

    void setCompression(Compression compression);

private:
    png_bytepp generatePixelData(const Maze &maze);
    void write(png_structp png, png_infop pngInfo, png_bytepp rows, const std::string& path);
};

#endif /* PNGEXPORTER_H */

