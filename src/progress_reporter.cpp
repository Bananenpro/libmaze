/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

// ********** Includes **********

#include <chrono>

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

ProgressReporter::Stage ProgressReporter::stage() const
{
    return mStage;
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

void ProgressReporter::setStage(Stage stage)
{
    if (stage != mStage)
    {
        mStage = stage;
        mProgress = mStage == Stage::FINISHED ? 1 : 0;
        mStartTime = currentTimeMillis();
        callCallbacks();
    }
}

// =================== PROTECTED ====================


void ProgressReporter::updateProgress(float progress)
{
    if ((progress == 1 && mProgress < 1) || progress - mProgress >= mCallbackPrecision || currentTimeMillis() - mLastCallback > mMaxCallbackInterval)
    {
        mProgress = progress;
        callCallbacks();
    }
}

// =================== PRIVATE ====================

void ProgressReporter::callCallbacks()
{
    for (callback_t cb : mCallbacks)
    {
        cb(stage(), currentTimeMillis() - mStartTime, mProgress);
    }

    mLastCallback = currentTimeMillis();
}

long ProgressReporter::currentTimeMillis() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
