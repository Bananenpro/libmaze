/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef PROGRESS_REPORTER_H
#define PROGRESS_REPORTER_H

// ********** Includes **********

#include <functional>
#include <string_view>
#include <vector>

class ProgressReporter
{
  public:
    enum Stage { STAGE_FAILURE = -2, STAGE_NONE = -1, STAGE_FINISHED = 100 };

    // void callback(Stage stage, long millis, float progress) <- progress: 0-100
    using callback_t = std::function<void(int, long, float)>;

  private:
    std::vector<callback_t> mCallbacks;
    long mStartTime{currentTimeMillis()};
    long mLastCallback{};
    long mMaxCallbackInterval{1000};
    float mCallbackPrecision{0.01f};
    int mStage{STAGE_NONE};
    float mProgress{0};

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

    int stage() const;

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

    void setStage(int stage);

    /**
     * @param progress the progress of the current stage between 0 and 1
     */
    void updateProgress(float progress);

  private:
    void callCallbacks();
    long currentTimeMillis() const;
};

#endif /* PROGRESS_REPORTER_H */
