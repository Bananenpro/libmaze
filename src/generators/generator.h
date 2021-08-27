/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef GENERATOR_H
#define GENERATOR_H

// ********** Includes **********

#include "../progress_reporter.h"

class Maze;

class IGenerator : public ProgressReporter
{
  public:
    enum Stage { STAGE_GENERATING };

  public:
    virtual ~IGenerator() {}

    virtual void generate(Maze &maze) = 0;
};

#endif /* GENERATOR_H */
