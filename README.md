# Bomb Diffusion Game

A simple C++ console game where you have 3 attempts to guess the randomly generated location of a hidden bomb (1-10).

## How to Compile

To compile the program, use a C++ compiler such as g++:

```bash
g++ -o bomb_game bomb_game.cpp
```

## How to Run

After compilation, run the executable:

- On Windows:
```bash
.\bomb_game.exe
```

- On Linux/Mac:
```bash
./bomb_game
```

## Game Rules

1. The bomb is hidden in a random location (box) numbered from 1 to 10.
2. You have 3 attempts to guess the correct location.
3. After each incorrect guess, you'll get a hint whether the bomb is in a higher or lower numbered box.
4. If you guess correctly, you win and the bomb is diffused.
5. If you use all 3 attempts without finding the bomb, it explodes and you lose.

## Implementation Details

The game is implemented using Object-Oriented Programming principles with a `BombGame` class that handles all game logic. 