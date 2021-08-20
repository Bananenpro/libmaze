/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef PROGRESS_REPORTER_H
#define PROGRESS_REPORTER_H

// ********** Includes **********

#include <string_view>
#include <vector>
#include <functional>

class ProgressReporter
{
public:
    enum class Stage
    {
        PREPARING, WORKING, FINISHED
    };

    // void callback(Stage stage, long millis, float progress) <- progress: 0-100
    using callback_t = std::function<void(Stage, long, float)>;

protected:
    std::vector<callback_t> mCallbacks;
    long mMaxCallbackInterval{1000};
    float mCallbackPrecision{0.01f};

private:
    Stage mCurrentStage{Stage::PREPARING};

public:
    virtual ~ProgressReporter() {}

    // ********** Getters **********

    /**
     * @return amount of progress(0-1) change needed to trigger a callback call
     */
    float callbackPrecision() const;

    /**
     * @return max amount of time in milliseconds between callback calls
     */
    long maxCallbackInterval() const;

    std::size_t callbackCount() const;

    Stage currentStage() const;


    // ********** Setters **********

    /**
     * @param precision amount of progress(0-1) change needed to trigger a callback call (default=0.01)
     */
    void setCallbackPrecision(float precision);

    /**
     * @param millis max amount of time in milliseconds between callback calls (default=1000)
     */
    void setMaxCallbackInterval(long millis);

    void addCallback(callback_t callback);

    void clearCallbacks();

    void setCurrentStage(Stage stage);

protected:
    /**
     * @param stage the current stage of operation
     * @param millis the time in milliseconds since the start of the current stage
     * @param progress the progress of the current stage between 0 (Nothing done yet) and 1 (Finished)
     */
    void callCallbacks(long millis, float progress) const;
};

#endif /* PROGRESS_REPORTER_H */

