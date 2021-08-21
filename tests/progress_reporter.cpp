/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <cmath>
#include <catch2/catch.hpp>

#include "../src/progress_reporter.h"

SCENARIO("Registering and calling callbacks")
{
    GIVEN("A progress reporter object")
    {
        class Test : public ProgressReporter
        {
        public:
            void testCallbacks()
            {
                setStage(Stage::WORKING);
                updateProgress(0.6f);
            }
        };

        Test test;

        WHEN("Calling the callbacks without registered callbacks")
        {
            test.testCallbacks();

            THEN("Nothing happens") {}
        }

        WHEN("Calling the callbacks with two registered callbacks")
        {
            int callback1CallCount {0};
            int callback2CallCount {0};

            test.addCallback([&callback1CallCount](ProgressReporter::Stage stage, long millis, float progress) 
            {
                ++callback1CallCount;
            });

            test.addCallback([&callback2CallCount](ProgressReporter::Stage stage, long millis, float progress) 
            {
                ++callback2CallCount;
            });

            test.testCallbacks();
            test.testCallbacks();

            THEN("All callbacks are called twice")
            {
                REQUIRE(callback1CallCount == 2);
                REQUIRE(callback2CallCount == 2);
            }
        }
    }
}
