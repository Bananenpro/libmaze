# AldousBroderGenerator class

Header: [`generators/aldous-broder_generator.h`](../../src/generators/aldous-broder_generator.h)

Implementation of [IGenerator](Generator.md) for generating mazes using the
[Aldous-Broder algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Aldous-Broder_algorithm)
algorithm.

## Example usage

```c++
Maze maze(100, 100);

AldousBroderGenerator generator;

maze.generate(generator);
// or alternatively
generator.generate(maze);
```

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
