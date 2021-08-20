# IExporter interface

### Saving a maze
See [#Saving](Maze.md#saving) in the maze class docs

### Callbacks
IExporter inherits its callback capabilities from [ProgressReporter](ProgressReporter.md).

### Implementations
- None

### Implementing IExporter
A class that implements IExporter needs to define all of the below member functions:
- `virtual void save(const Maze& maze, std::string_view path) const`
    - This method is responsible for saving the provided maze to disk
    - This method should call all callback functions in `callbacks` as soon as
        - The progress changed by more than `callbackPrecision` since the last callback call
        - The last call was more than `maxCallbackInterval` milliseconds ago
        - The stage changed

---
[Go to home](Home.md)\
Copyright © Julian Hofmann
