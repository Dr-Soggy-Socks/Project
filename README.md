# Reverse 2048

A unique twist on the classic 2048 puzzle game built in C++.  
Instead of building up to 2048, Reverse 2048 challenges the player to strategically reduce and manipulate the board in reverse-style gameplay mechanics.

## Overview

Reverse 2048 is a console-based puzzle game inspired by the original 2048 game created by Gabriele Cirulli. This project was developed as a way to explore:

- C++ programming fundamentals
- Object-oriented programming
- Game logic and state management
- Matrix/grid manipulation
- Input handling
- Algorithmic thinking

The project focuses on implementing the complete game logic from scratch while experimenting with reverse mechanics and alternative gameplay strategies.

---

## Features

- Classic 4×4 grid gameplay
- Reverse-style 2048 mechanics
- Keyboard-controlled movement system
- Tile merging logic
- Score tracking
- Random tile generation
- Game-over detection
- Console-based interface
- Lightweight and fast execution

---

## Technologies Used

- **Language:** C++
- **Compiler:** g++
- **IDE/Editor:** Visual Studio Code / Code::Blocks / Any C++ IDE
- **Version Control:** Git & GitHub

---

## How the Game Works

The player moves tiles across the board using directional controls.

When compatible tiles collide:
- They combine according to the reverse game rules
- The board updates dynamically
- A new tile is generated after each move

The game ends when:
- No more valid moves are available
- The board becomes locked

The challenge is to think ahead carefully and manage space efficiently.

---

## Controls

| Key | Action |
|---|---|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
