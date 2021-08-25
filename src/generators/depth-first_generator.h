/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef DEPTH_FIRST_GENERATOR_H
#define DEPTH_FIRST_GENERATOR_H

// ********** Incldues **********

#include "generator.h"

class DepthFirstGenerator : public IGenerator
{
public:
    virtual void generate(Maze& maze);
};

#endif /* DEPTH_FIRST_GENERATOR_H */

