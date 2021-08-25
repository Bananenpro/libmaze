# PNGExporter class

Header: [`exporters/png_exporter.h`](../../src/exporters/png_exporter.h)

Implementation of [IExporter](Exporter.md) for saving mazes as *png* files.

# Example usage
```c++
Maze maze(100, 100);

PNGExporter exporter;

// Change compression of png file (default=VERY_LOW)
exporter.setCompression(PNGExporter::Compression::LOW);

maze.save(exporter, "maze.png");
// or alternatively
exporter.save(maze, "maze.png");
```

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
