# libmaze

An extensible C++20 library for creating and solving mazes.

**NOTE:** This library currently has some serious performance issues. I'm currently occupied with other projects. I don't kown when or if I will revisit this project.

### [Documentation](docs/Home.md)

### Features

- [x] Work with mazes through an easy to use class
- Export mazes
  - [x] Exporter interface
  - [x] PNGExporter
    - Create png image files showing the maze
  - [ ] MinecraftExporter
    - Create datapacks which generate the maze in-game
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
  - [x] [Randomized depth-first search](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search)
  - [ ] [Wilson's algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Wilson's_algorithm)
  - [x] [Aldous-Broder algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Aldous-Broder_algorithm)
  - [ ] [Randomized Kruskal's algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Kruskal's_algorithm)
  - [ ] [Randomized Prim's algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithmm#Randomized_Prim's_algorithm)
  - [ ] [Recursive division method](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_division_method)
  - [ ] [Simple algorithms](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Simple_algorithms)
  - [ ] [Cellular automata](https://en.wikipedia.org/wiki/Maze_generation_algorithm#Cellular_automaton_algorithms)
- [ ] Create weighted graphs from mazes
- Solve mazes
  - [ ] Solver interface
  - [ ] [Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)
  - [ ] [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra's_algorithm)
  - [ ] [Bellman–Ford algorithm](https://en.wikipedia.org/wiki/Bellman–Ford_algorithm)
  - [ ] [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)
  - [ ] [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd-Warshall_algorithm)
  - [ ] [Johnson's algorithm](https://en.wikipedia.org/wiki/Johnson's_algorithm)
  - [ ] [Viterbi algorithm](https://en.wikipedia.org/wiki/Viterbi_algorithm)

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

Run the following command in the build directory after [building](#Building)
**as debug build**:

```sh
./tests
```

After running the tests you can manually check the outcome of all algorithms
by checking the corresponding _png_ file (e.g. `depth-first.png`).

## License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Copyright

Copyright © 2021 Julian Hofmann
