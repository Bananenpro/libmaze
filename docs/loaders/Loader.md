# ILoader interface

### Loading a maze
See [#Loading](../Maze.md#loading) in the maze class docs

### Callbacks
ILoader inherits its callback capabilities from [ProgressReporter](../ProgressReporter.md).
In addition to that ILoader provides the following stages:
- STAGE_READING
- STAGE_CONSTRUCTING

### Implementations
- [PNGLoader](PNGLoader.md)

### Implementing ILoader
A class that implements ILoader needs to define all of the below member functions:
- `virtual Maze load(const std::string& path)`
    - This method is responsible for loading the maze from disk
    - This method should report its progress to the underlying `ProgressReporter` implementation by calling following methods
        - `void setStage(Stage stage)` when the stage changes (PREPARING, WORKING, FINISHED)
        - `void updateProgress(float progress)` when the progress(0-1) changes

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
