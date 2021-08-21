# IExporter interface

### Saving a maze
See [#Saving](../Maze.md#saving) in the maze class docs

### Callbacks
IExporter inherits its callback capabilities from [ProgressReporter](../ProgressReporter.md).

### Implementations
- [PNGExporter](PNGExporter.md)

### Implementing IExporter
A class that implements IExporter needs to define all of the below member functions:
- `virtual void save(const Maze& maze, const std::string& path)`
    - This method is responsible for saving the provided maze to disk
    - This method should report its progress to the underlying `ProgressReporter` implementation by calling following methods
        - `void setStage(Stage stage)` when the stage changes (PREPARING, WORKING, FINISHED)
        - `void updateProgress(float progress)` when the progress(0-1) changes

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
