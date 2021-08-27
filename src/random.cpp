/**
 * @author      : Julian Hofmann
 * @created     : 24/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <ctime>
#include <stdexcept>

#include "random.h"

template <typename T> T random(T min, T max)
{
    static std::mt19937 mersenne{static_cast<std::mt19937::result_type>(std::time(nullptr))};

    std::uniform_int_distribution<T> generator{min, max};
    return generator(mersenne);
}

template int random(int min, int max);
template std::size_t random(std::size_t min, std::size_t max);
