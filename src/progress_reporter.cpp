/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include "progress_reporter.h"


// =================== PUBLIC ====================


// ********** Getters **********

float ProgressReporter::callbackPrecision() const
{
    return mCallbackPrecision;
}

long ProgressReporter::maxCallbackInterval() const
{
    return mMaxCallbackInterval;
}

std::size_t ProgressReporter::callbackCount() const
{
    return mCallbacks.size();
}

ProgressReporter::Stage ProgressReporter::currentStage() const
{
    return mCurrentStage;
}


// ********** Setters **********

void ProgressReporter::setCallbackPrecision(float precision)
{
    mCallbackPrecision = precision;
}

void ProgressReporter::setMaxCallbackInterval(long millis)
{
    mMaxCallbackInterval = millis;
}

void ProgressReporter::addCallback(callback_t callback)
{
    mCallbacks.push_back(callback);
}

void ProgressReporter::clearCallbacks()
{
    mCallbacks.clear();
    mCallbacks.shrink_to_fit();
}

void ProgressReporter::setCurrentStage(Stage stage)
{
    mCurrentStage = stage;
}

// =================== PUBLIC ====================


void ProgressReporter::callCallbacks(long millis, float progress) const
{
    for (callback_t cb : mCallbacks)
    {
        cb(currentStage(), millis, progress);
    }
}
