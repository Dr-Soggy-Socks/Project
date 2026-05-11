# Reverse 2048

A custom reverse implementation of the classic 2048 puzzle game built entirely in C++.

Unlike traditional 2048 where tiles merge into larger values, this version reverses the mechanic:
matching tiles combine into smaller values until the player reaches the target value of `2`.

The project also includes automated solving algorithms capable of playing the game autonomously.

---

# Features

## Core Gameplay
- Reverse 2048 mechanics
- Dynamic board sizes:
  - 3×3
  - 4×4
  - 5×5
- Multiple reverse target modes:
  - Reverse 128
  - Reverse 256
  - Reverse 512
- Random tile generation
- Tile movement and merge logic
- Win condition detection
- Game-over detection
- Move validation system
- Console-based interface

---

# Algorithmic Gameplay

The project includes autonomous solving algorithms capable of:
- Analysing board states
- Selecting valid moves
- Progressing toward win conditions automatically
- Simulating gameplay without user interaction

Two separate algorithms were developed and tested to compare solving strategies and board performance.

---

# Technologies Used

- C++
- STL Vectors
- Object-Oriented Programming
- Random Number Generation
- Matrix/Grid Manipulation
- Algorithm Design
- Console I/O

---

# How Reverse 2048 Works

Traditional 2048:
```text
2 + 2 = 4
```

Reverse 2048:
```text
128 + 128 = 64
64 + 64 = 32
...
4 + 4 = 2
```

The objective is to strategically reduce tiles until reaching the final target value of `2`.

This creates a completely different optimisation problem compared to the original game because:
- larger values become resources,
- board compression behaves differently,
- and long-term planning changes significantly.

---

# Controls

| Key | Action |
|------|------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| Q | Quit Game |

---

# Game Modes

## Manual Mode
The player controls all movement decisions.

## Algorithm Mode
The game is played automatically using one of the implemented solving algorithms.

Optional board-state visualisation allows every move made by the algorithm to be displayed.

---

# Project Structure

```text
Project/
│
├── main.cpp
├── Algorithm1.cpp
├── Algorithm1.h
├── Algorithm2.cpp
├── Algorithm2.h
├── README.md
```

---

# Example Gameplay

```text
=== Reverse 256 Mode ===

128    64     0      0
128    32     16     0
64     16     0      0
0      0      0      0

Move: W
```

After merging:

```text
64     64     16     0
64     16     0      0
0      0      0      0
0      0      0      0
```

---

# Key Programming Concepts Demonstrated

This project demonstrates understanding of:

- 2D vector manipulation
- State-based game systems
- Merge algorithms
- Input validation
- Randomised systems
- Procedural game logic
- Algorithmic automation
- Modular program structure
- Separation of concerns
- Simulation design

---

# Challenges Solved During Development

Some of the major implementation challenges included:
- Correctly handling merge order
- Preventing duplicate merges
- Detecting impossible board states
- Designing reversible mechanics
- Managing dynamic board sizes
- Building autonomous solving behaviour
- Ensuring move legality

---

# Future Improvements

Potential future additions:
- Graphical interface (SFML or SDL)
- Improved AI search algorithms
- Minimax or heuristic-based solving
- Save/load functionality
- Move undo system
- Performance benchmarking
- Animated terminal rendering
- Difficulty presets

---

# Educational Value

This project was developed as both:
- a programming exercise,
- and an experimental game systems project.

It explores how small rule changes can fundamentally alter optimisation strategies and gameplay behaviour.

The automated algorithms additionally introduce elements of:
- search strategy,
- state evaluation,
- and autonomous decision-making.

---

# Author

Tlhompo Khanye  
Engineering Student — University of the Witwatersrand

GitHub:
https://github.com/Dr-Soggy-Socks
