# Exporter interface

### Saving a maze
- See [#Saving](Maze.md#saving) in maze class docs

### Callbacks

#### Registering callback functions
You can register callback functions with the signature `void callback(Stage stage, long millis, float progress)`
using the `void addCallback(callback_t callback)`
member function and remove them with `void clearCallbacks()`.

#### When are callback functions called?
All registered callbacks are called once one of the following conditions is met:
- The progress changed by more than `callbackPrecision`
- The last call was more than `maxCallbackInterval` milliseconds ago
- The stage changed

#### What arguments are passed to the callback functions
Three arguments are passed to the callback functions:
- The current stage (This can either be `Stage::PREPARING`, `Stage::WRITING` ore `Stage::FINISHED`)
- The time in milliseconds since the start of the current stage
- The progress between 0 (Nothing done yet) and 1 (Finished)

### Implementations
- None

### Implementing IExporter
A class that implements IExporter needs to define all of the below member functions:
- `virtual void save(const Maze& maze, std::string_view path) const`
    - This method is responsible for saving the provided maze to disk
    - This method should call all callback functions in `mCallbacks` as soon as
        - The progress changed by more than `mCallbackPrecision` since the last callback call
        - The last call was more than `mMaxCallbackInterval` milliseconds ago
        - The stage changed

---
[Go to home](Home.md)\
Copyright © Julian Hofmann
