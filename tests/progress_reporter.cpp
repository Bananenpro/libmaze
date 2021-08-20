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
                setCurrentStage(Stage::WORKING);
                callCallbacks(1000, 0.6f);
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
            Test::Stage stage1{};
            Test::Stage stage2{};

            long millis1{};
            long millis2{};

            float progress1{};
            float progress2{};

            test.addCallback([&stage1, &millis1, &progress1](ProgressReporter::Stage stage, long millis, float progress) 
            {
                stage1 = stage;
                millis1 = millis;
                progress1 = progress;
            });

            test.addCallback([&stage2, &millis2, &progress2](ProgressReporter::Stage stage, long millis, float progress) 
            {
                stage2 = stage;
                millis2 = millis;
                progress2 = progress;
            });

            test.testCallbacks();

            THEN("All callbacks are called with the right values")
            {
                REQUIRE(stage1 == Test::Stage::WORKING);
                REQUIRE(millis1 == 1000);
                REQUIRE(std::abs(progress1 - 0.6f) < 0.001f);

                REQUIRE(stage2 == Test::Stage::WORKING);
                REQUIRE(millis2 == 1000);
                REQUIRE(std::abs(progress2 - 0.6f) < 0.001f);
            }
        }
    }
}
