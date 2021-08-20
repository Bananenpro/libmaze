/**
 * @author      : Julian Hofmann
 * @created     : 19/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef EXPORTER_H
#define EXPORTER_H

// ********** Includes **********

#include <string_view>
#include <vector>
#include <functional>

#include "../progress_reporter.h"

class Maze;

class IExporter : public ProgressReporter
{
public:
    virtual ~IExporter() {}

    virtual void save(const Maze& maze, std::string_view path) const = 0;
};

#endif /* EXPORTER_H */

