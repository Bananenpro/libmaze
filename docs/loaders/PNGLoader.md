# PNGLoader class

Header: [`loaders/png_loader.h`](../../src/loaders/png_loader.h)

Implementation of [ILoader](Exporter.md) for loading mazes from *png* files.

## Example usage

```c++
PNGLoader loader;

Maze maze {Maze::load(loader, "maze.png")};
// or alternatively
Maze maze {loader.load("maze.png")};
```

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
