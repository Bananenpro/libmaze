# IGenerator interface

### Generating a maze
See [#Generating](../Maze.md#generating) in the maze class docs

### Callbacks
IGenerator inherits its callback capabilities from [ProgressReporter](../ProgressReporter.md).
In addition to that IGenerator provides the following stages:
- STAGE_GENERATING

### Implementations
- [DepthFirstGenerator](DepthFirstGenerator.md)

### Implementing IGenerator
A class that implements IExporter needs to define all of the below member functions:
- `virtual void generate(Maze& maze)`
    - This method is responsible clearing and then generating the provided maze.
    - This method should report its progress to the underlying [ProgressReporter](../ProgressReporter.md) implementation by calling following methods
        - `void setStage(Stage stage)` when the stage changes
        - `void updateProgress(float progress)` when the progress changes

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
