# Nine Men's Morris – AI Strategy Game Engine

> A fully functional Nine Men's Morris game engine built in C, featuring a complete rule system and an AI opponent powered by the Minimax algorithm with Alpha-Beta pruning.

**Built at:** Ecole Hassania des Travaux Publics (EHTP) — Advanced Algorithmics & Game Theory

**Organization:** Hassania IT Club (H.I.T.C)

**Language:** C

**Authors:** IDRISSI MELIANI Hamza and TAQI Youssef

**Year:** 2025–2026

---
## Table of Contents

- [About the Game](#about-the-game)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [How to Play](#how-to-play)
- [AI Implementation](#ai-implementation)
- [Game Rules](#game-rules)

---

## About the Game

Nine Men's Morris (Jeu du Moulin) is one of the oldest two-player strategy games in the world, with origins tracing back to ancient Egypt and Rome. Players alternate placing and moving pieces on a board of 24 intersections, aiming to form **mills** (alignments of 3 pieces) to capture the opponent's pieces.

This project implements the full game logic in C — including all three phases of play, mill detection, capture rules, and an AI opponent — as part of the Advanced Algorithmics & Game Theory module at EHTP.

---

## Features

- ✅ Complete rule enforcement: placement, movement, mill detection, and capture phases
- ✅ AI opponent using **Minimax algorithm with Alpha-Beta pruning**
- ✅ Human vs Human and Human vs AI modes
- ✅ Clean ASCII board rendering in the terminal
- ✅ Input validation with error handling
- ✅ Modular architecture with clean separation of concerns

---

## Project Structure

```
projet_moulin/
│
├── src/
│   ├── main.c          # Entry point — game mode selection & main loop
│   ├── functions.c     # All game logic: board, rules, phases, AI
│   └── prototype.h     # All declarations, structs, and constants
│
├── README.md           # This file
└── Makefile            # Compilation instructions
```

> **Note:** The entire logic is organized across 3 files: `prototype.h` for declarations, `functions.c` for all implementations, and `main.c` as the entry point.

---

## Getting Started

### Prerequisites

- GCC compiler
- Linux / macOS / Windows with MinGW

### Compile

```bash
make
```

Or manually:

```bash
gcc -Wall -Wextra -g -o moulin src/main.c src/functions.c
```

### Run

```bash
./moulin
```

---

## How to Play

On launch, you will see a menu:

```
===========================
   NINE MEN'S MORRIS
===========================
1. Human vs Human
2. Human vs AI
3. Quit
Select mode:
```

The board uses ASCII rendering with positions numbered **0–23**:

```
0-----------1-----------2
|           |           |
|   8-------9-------10  |
|   |       |       |   |
|   |  16--17--18   |   |
7--15  |        |   11--3
|   |  23--22--21   |   |
|   |       |       |   |
|   14------13------12  |
|           |           |
6-----------5-----------4
```

- **Placement phase:** Enter the position number to place your piece
- **Movement phase:** Enter `source destination` (e.g., `4 7`)
- **Mill formed:** You will be prompted to select an opponent piece to capture

---

## AI Implementation

The AI opponent is implemented using the **Minimax algorithm with Alpha-Beta pruning**.

### How it works

| Component | Description |
|---|---|
| **Minimax** | Recursively explores the game tree, maximizing the AI's score and minimizing the player's score |
| **Alpha-Beta pruning** | Eliminates branches that cannot influence the final decision, significantly reducing computation time |
| **Heuristic function** | Evaluates board positions based on: number of mills formed, number of pieces on board, mobility (available moves) |

```
minimax(state, depth, alpha, beta, isMaximizing)
├── Base case: depth == 0 or game over → return heuristic(state)
├── Maximizing: find move that maximizes score
└── Minimizing: find move that minimizes score
    └── Alpha-Beta: prune branches where alpha ≥ beta
```

---

## Game Rules

### The Board
- 24 intersections across 3 concentric squares connected by lines
- Each player starts with **9 pieces**

### Phase 1 — Placement
Players alternate placing pieces on empty intersections. Forming a **mill** (3 aligned pieces) allows capturing one opponent piece.

### Phase 2 — Movement
Once all 18 pieces are placed, players move pieces to adjacent intersections. Blocking all of an opponent's moves wins the game.

### Phase 3 — Flying *(optional)*
When a player has only 3 pieces left, they may move to any empty intersection.

### Winning Conditions
A player **loses** if:
- They have fewer than 3 pieces remaining
- All their pieces are blocked with no valid moves

---
