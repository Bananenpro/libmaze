/**
 * @author      : Julian Hofmann
 * @created     : 01/09/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef ALDOUS_BRODER_GENERATOR_H
#define ALDOUS_BRODER_GENERATOR_H

// ********** Incldues **********

#include "generator.h"

class AldousBroderGenerator : public IGenerator
{
  public:
    virtual void generate(Maze &maze);
};

#endif /* ALDOUS_BRODER_GENERATOR_H */
