/**
 * @author      : Julian Hofmann
 * @created     : 21/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef LOADER_H
#define LOADER_H

// ********** Includes **********

#include <string_view>
#include <vector>
#include <functional>

#include "../progress_reporter.h"

class Maze;

class ILoader : public ProgressReporter
{
public:
    virtual ~ILoader() {}

    virtual Maze load(const std::string& path) = 0;
};

#endif /* LOADER_H */

