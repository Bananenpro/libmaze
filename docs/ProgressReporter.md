# ProgressReporter class 

Header: [`progress_reporter.h`](../src/progress_reporter.h)

## Registering callback functions

You can register callback functions with the signature
`void callback(int stage, long millis, float progress)`
using the `void addCallback(callback_t callback)`
member function and remove them with `void clearCallbacks()`.

## When are callback functions called?

All registered callbacks are called once one of the following conditions is met:

- The progress changed by more than `callbackPrecision`
- The last call was more than `maxCallbackInterval` milliseconds ago
- The stage changed

## What arguments are passed to the callback functions

Three arguments are passed to the callback functions:

- The current stage
- The time in milliseconds since the start of the current stage
- The progress of the current stage between 0 (nothing done yet) and 1 (finished)
or -1 (undeterminable)

## Extending ProgressReporter

To extend ProgressReporter you don't need to do anything except optionally
providing a Stage enum for the extra stages your class provides.
ProgressReporter already provides STAGE_NONE, STAGE_FINISHED and STAGE_FAILURE.
Example:

```c++
enum Stage
{
    STAGE_DOING_SOMETHING, STAGE_DOING_SOMETHING_ELSE
};
```

**IMPORTANT:** Do not use negative enum values or values above 99!

---
[Go to home](Home.md)\
Copyright © Julian Hofmann
