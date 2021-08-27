/**
 * @author      : Julian Hofmann
 * @created     : 20/08/2021
 * @copyright   : Copyright © Julian Hofmann
 * @license     : MIT
 */

#include <catch2/catch.hpp>
#include <cmath>

#include "../src/progress_reporter.h"

SCENARIO("Registering and calling callbacks")
{
    GIVEN("A progress reporter object")
    {
        class Test : public ProgressReporter
        {
          public:
            enum Stage { STAGE_WORKING };

            void testCallbacks()
            {
                setStage(STAGE_WORKING);
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
            int callback1CallCount{0};
            int callback2CallCount{0};

            test.addCallback([&callback1CallCount](int stage, long millis, float progress) {
                if (stage == Test::STAGE_WORKING)
                    ++callback1CallCount;
            });

            test.addCallback([&callback2CallCount](int stage, long millis, float progress) {
                if (stage == Test::STAGE_WORKING)
                    ++callback2CallCount;
            });

            test.testCallbacks();
            test.testCallbacks();

            THEN("All callbacks are called once")
            {
                REQUIRE(callback1CallCount == 2);
                REQUIRE(callback2CallCount == 2);
            }
        }
    }
}
