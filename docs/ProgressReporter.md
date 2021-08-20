# ProgressReporter class 

### Registering callback functions
You can register callback functions with the signature `void callback(Stage stage, long millis, float progress)`
using the `void addCallback(callback_t callback)`
member function and remove them with `void clearCallbacks()`.

### When are callback functions called?
All registered callbacks are called once one of the following conditions is met:
- The progress changed by more than `callbackPrecision`
- The last call was more than `maxCallbackInterval` milliseconds ago
- The stage changed

### What arguments are passed to the callback functions
Three arguments are passed to the callback functions:
- The current stage (This can either be `Stage::PREPARING`, `Stage::WORKING` or `Stage::FINISHED`)
- The time in milliseconds since the start of the current stage
- The progress of the current stage between 0 (Nothing done yet) and 1 (Finished)

---
[Go to home](Home.md)\
Copyright © Julian Hofmann
