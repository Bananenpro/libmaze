# libmaze

A simple and extensible C++20 library for creating and solving mazes.

### [Documentation](docs/Home.md)

### Features

- [x] Work with mazes through an easy to use class
- Export mazes
  - [x] Exporter interface
  - [x] PNGExporter
    - Create png image files showing the maze
  - [ ] MinecraftExporter
    - Create datapacks which generates the maze in-game
  - [ ] JSONExporter
    - Create json files representing the maze
- Load mazes
  - [x] Loader interface
  - [x] PNGLoader
    - Load png files created using `PNGExporter`
  - [ ] JSONLoader
        - Load json files created using `JSONExporter`
- Generate mazes
  - [x] Generator interface
  - [x] [Randomized depth-first search](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_depth-first_search)
  - [ ] [Wilson's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Wilson's_algorithm)
  - [x] [Aldous-Broder algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Aldous-Broder_algorithm)
  - [ ] [Randomized Kruskal's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_Kruskal's_algorithm)
  - [ ] [Randomized Prim's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_Prim's_algorithm)
  - [ ] [Recursive division method](https://www.wikiwand.com/en/Maze_generation_algorithm#Recursive_division_method)
  - [ ] [Simple algorithms](https://www.wikiwand.com/en/Maze_generation_algorithm#Simple_algorithms)
  - [ ] [Cellular automata](https://www.wikiwand.com/en/Maze_generation_algorithm#Cellular_automaton_algorithms)
- [ ] Create weighted graphs from mazes
- Solve mazes
  - [ ] Solver interface
  - [ ] [Breadth-first search](https://www.wikiwand.com/en/Breadth-first_search)
  - [ ] [Dijkstra's algorithm](https://www.wikiwand.com/en/Dijkstra's_algorithm)
  - [ ] [Bellman–Ford algorithm](https://www.wikiwand.com/en/Bellman–Ford_algorithm)
  - [ ] [A* search algorithm](https://www.wikiwand.com/en/A*_search_algorithm)
  - [ ] [Floyd–Warshall algorithm](https://www.wikiwand.com/en/Floyd-Warshall_algorithm)
  - [ ] [Johnson's algorithm](https://www.wikiwand.com/en/Johnson's_algorithm)
  - [ ] [Viterbi algorithm](https://www.wikiwand.com/en/Viterbi_algorithm)

### Installing Dependencies

#### ArchLinux

```sh
sudo pacman -S catch2 libpng
```

#### Other

Install the following libraries:

- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x)
- [libpng](http://www.libpng.org/pub/png/libpng.html)

### Building

#### Unix-like

##### Required packages

- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [make](https://www.gnu.org/software/make/)

Run the following commands (Change `Release` to `Debug` for debug build):

```sh
git clone https://gitlab.com/Bananenpro05/libmaze.git
cd libmaze
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

#### Windows

¯\\(o_o)/¯

### Running tests

Run the following command in the build directory after building:

```sh
./tests
```

---
Copyright © Julian Hofmann
