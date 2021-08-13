# libmaze

A simple C++ library for creating and solving mazes.

### [Documentation](https://gitlab.com/Bananenpro05/libmaze/-/blob/main/docs/QuickStart.md)

### Features

- [ ] Export mazes
    - [ ] Exporter Interface
    - [ ] PNGExporter
        - Creates png image file showing the maze
        - Configurable colors?
    - [ ] MinecraftExporter
        - Creates datapack which generates the maze in-game
    - [ ] JSONExporter
        - Creates json file representing the maze
- [ ] Load mazes
    - [ ] Loader Interface
    - [ ] PNGLoader
        - Load png files created using `PNGExporter`
- [ ] Create weighted graphs from mazes
- [ ] Generate mazes
    - [ ] [Randomized depth-first search](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_depth-first_search)
    - [ ] [Wilson's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Wilson's_algorithm)
    - [ ] [Aldous-Broder algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Aldous-Broder_algorithm)
    - [ ] [Randomized Kruskal's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_Kruskal's_algorithm)
    - [ ] [Randomized Prim's algorithm](https://www.wikiwand.com/en/Maze_generation_algorithm#Randomized_Prim's_algorithm)
    - [ ] [Recursive division method](https://www.wikiwand.com/en/Maze_generation_algorithm#Recursive_division_method)
    - [ ] [Simple algorithms](https://www.wikiwand.com/en/Maze_generation_algorithm#Simple_algorithms)
    - [ ] [Cellular automata](https://www.wikiwand.com/en/Maze_generation_algorithm#Cellular_automaton_algorithms)
- [ ] Solve mazes
    - [ ] [Breadth-first search](https://www.wikiwand.com/en/Breadth-first_search)
    - [ ] [Dijkstra's algorithm](https://www.wikiwand.com/en/Dijkstra's_algorithm)
    - [ ] [Bellman–Ford algorithm](https://www.wikiwand.com/en/Bellman–Ford_algorithm)
    - [ ] [A* search algorithm](https://www.wikiwand.com/en/A*_search_algorithm)
    - [ ] [Floyd–Warshall algorithm](https://www.wikiwand.com/en/Floyd-Warshall_algorithm)
    - [ ] [Johnson's algorithm](https://www.wikiwand.com/en/Johnson's_algorithm)
    - [ ] [Viterbi algorithm](https://www.wikiwand.com/en/Viterbi_algorithm)

### Installing Dependencies
#### ArchLinux
```
sudo pacman -S libpng
```
#### Other
Install the following libraries:
- [libpng](http://www.libpng.org/pub/png/libpng.html)

### Building
#### Unix-like
##### Required packages
- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [make](https://www.gnu.org/software/make/)
```
git clone https://gitlab.com/Bananenpro05/libmaze.git
cd libmaze
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
##### Windows
¯\\(o_o)/¯
