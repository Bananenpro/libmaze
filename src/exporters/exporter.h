/**
 * @author      : Julian Hofmann
 * @created     : 19/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef EXPORTER_H
#define EXPORTER_H

// ********** Includes **********

#include <functional>
#include <string>
#include <vector>

#include "../progress_reporter.h"

class Maze;

class IExporter : public ProgressReporter
{
  public:
    enum Stage { STAGE_PREPARING, STAGE_WRITING };

  public:
    virtual ~IExporter() {}

    virtual void save(const Maze &maze, const std::string &path) = 0;
};

#endif /* EXPORTER_H */
