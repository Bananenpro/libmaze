# DepthFirstGenerator class

Header: [`generators/depth-first_generator.h`](../../src/generators/depth-first_generator.h)

Implementation of [IGenerator](Generator.md) for generating mazes using the [randomized depth-first search](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_depth-first_search)
algorithm.

# Example usage
```c++
Maze maze(100, 100);

DepthFirstGenerator generator;

maze.generate(generator);
// or alternatively
generator.generate(maze);
```

---
[Go to home](../Home.md)\
Copyright © Julian Hofmann
