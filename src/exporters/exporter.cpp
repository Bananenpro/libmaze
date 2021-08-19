/**
 * @author      : Julian Hofmann
 * @created     : 19/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include "exporter.h"


// ********** Getters **********

float IExporter::callbackPrecision() const
{
    return mCallbackPrecision;
}

long IExporter::maxCallbackInterval() const
{
    return mMaxCallbackInterval;
}

std::size_t IExporter::callbackCount() const
{
    return mCallbacks.size();
}


// ********** Setters **********

void IExporter::setCallbackPrecision(float precision)
{
    mCallbackPrecision = precision;
}

void IExporter::setMaxCallbackInterval(long millis)
{
    mMaxCallbackInterval = millis;
}

void IExporter::addCallback(callback_t callback)
{
    mCallbacks.push_back(callback);
}

void IExporter::clearCallbacks()
{
    mCallbacks.clear();
    mCallbacks.shrink_to_fit();
}
