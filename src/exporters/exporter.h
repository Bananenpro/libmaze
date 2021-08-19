/**
 * @author      : Julian Hofmann
 * @created     : 19/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */
#ifndef EXPORTER_H
#define EXPORTER_H

// ********** Includes **********

#include <string_view>
#include <vector>
#include <functional>

class Maze;

class IExporter
{
public:
    enum class Stage
    {
        PREPARING, WRITING, FINISHED
    };

    // void callback(Stage stage, long millis, float progress) <- progress: 0-100
    using callback_t = std::function<void(Stage, long, float)>;

protected:
    std::vector<callback_t> mCallbacks;
    long mMaxCallbackInterval{1000};
    float mCallbackPrecision{0.01f};

public:
    virtual ~IExporter() {}

    virtual void save(const Maze& maze, std::string_view path) const = 0;


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
};

#endif /* EXPORTER_H */

