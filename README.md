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
- ✅ Three AI difficulty levels: **Human vs Human**, **Human vs Simple AI**, **Human vs Hard AI**
- ✅ Hard AI powered by the **Minimax algorithm with Alpha-Beta pruning** (depth 3)
- ✅ Simple AI for casual play (random moves with basic mill capture)
- ✅ In-game rules reference accessible from the main menu
- ✅ Colorized ASCII board rendering in the terminal (ANSI color codes)
- ✅ Input validation with error handling
- ✅ Replay and return-to-menu options after each game
- ✅ Modular architecture with clean separation of concerns

---

## Project Structure

```
projet_moulin/
│
├── main.c          # Entry point — seeds RNG and calls Jouer()
│── functions.c     # All game logic: board, rules, phases, AI
│── prototype.h     # All declarations, structs, constants, and color macros
├── README.md           
```

> **Note:** The entire logic is organized across 3 files: `prototype.h` for declarations and type definitions, `functions.c` for all implementations, and `main.c` as the minimal entry point.

### Key Types (defined in `prototype.h`)

| Type | Description |
|---|---|
| `etatCase` | Enum — `vide`, `J1`, `J2` |
| `typeJoueur` | Enum — `humain`, `IA_simple`, `IA_difficile` |
| `PhaseJeu` | Enum — `Placement`, `Deplacement`, `Vol` |
| `Plateau` | Board state: cells, adjacency list, mill definitions |
| `Joueur` | Player state: name, piece counts, type |
| `Jeu` | Full game state: board, two players, phase, current player, end flag |
| `Coup` | A move: `depart` (−1 if placement), `arrivee`, `capture` (−1 if none) |

---

## Getting Started

### Prerequisites

- GCC compiler
- Linux / macOS / Windows with MinGW
- A terminal that supports **ANSI escape codes** (color output)

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

On launch, you will see a colorized main menu:

```
+------------------------------+
|     1 - Joueur VS Joueur     |
+------------------------------+
|   2 - Joueur VS IA SIMPLE    |
+------------------------------+
| 3 - Joueur VS IA Difficile   |
+------------------------------+
|     4 - Regles du Jeu        |
+------------------------------+
|     5 - Quitter              |
+------------------------------+
```

The board uses ASCII rendering with positions labeled **A–X** (internally mapped to indices 0–23):

```
A-----------B-----------C
|           |           |
|   I-------J-------K   |
|   |       |       |   |
|   |   Q---R---S   |   |
H---P---X       T---L---D
|   |   W---V---U   |   |
|   |       |       |   |
|   O-------N-------M   |
|           |           |
G-----------F-----------E
```

- **Outer square:** A(0) B(1) C(2) D(3) E(4) F(5) G(6) H(7)
- **Middle square:** I(8) J(9) K(10) L(11) M(12) N(13) O(14) P(15)
- **Inner square:** Q(16) R(17) S(18) T(19) U(20) V(21) W(22) X(23)

Player 1's pieces are shown in **red**, Player 2's in **blue**.

- **Placement phase:** Enter the letter of the position to place your piece (e.g., `A`)
- **Movement phase:** Enter your piece's letter, then the destination letter
- **Mill formed:** You will be prompted to select an opponent's piece to capture

---

## AI Implementation

The game offers two AI opponents:

### Simple AI (`IA_simple`)
Places and moves pieces **randomly**, but will capture an opponent's piece if a mill is accidentally formed. Used as a beginner-friendly opponent.

### Hard AI (`IA_difficile`)
Powered by the **Minimax algorithm with Alpha-Beta pruning** at depth 3.

| Component | Description |
|---|---|
| **Minimax** | Recursively explores the game tree, maximizing the AI's score and minimizing the player's score |
| **Alpha-Beta pruning** | Eliminates branches that cannot affect the final result, significantly reducing computation time |
| **Move generator** | `genererCoups()` enumerates all valid placements, moves, and flying moves, including captures when a mill is formed |
| **Heuristic function** | `evaluerPlateau()` scores positions based on piece counts (×10), active mills (×5), piece mobility (×2), blocking the opponent (×15), and terminal win/loss (±200) |

```
meilleurCoupIA(jeu)
└── for each generated move:
    └── alphaBeta(copy, depth=3, alpha=-1000, beta=1000, minimizing, joueurIA)
        ├── Base case: depth == 0 or game over → evaluerPlateau()
        ├── Maximizing: find move that maximizes score, update alpha
        └── Minimizing: find move that minimizes score, update beta
            └── Prune branch when beta ≤ alpha
```

---

## Game Rules

### The Board
- 24 intersections across 3 concentric squares connected by lines
- 16 possible mills (horizontal and vertical alignments of 3)
- Each player starts with **9 pieces**

### Phase 1 — Placement
Players alternate placing pieces on empty intersections. Forming a **mill** (3 aligned pieces) allows capturing one opponent piece. A piece inside a mill cannot be captured unless all opponent pieces are in mills.

### Phase 2 — Movement (`Deplacement`)
Once all 18 pieces are placed, players move pieces to **adjacent** intersections. Blocking all of an opponent's moves wins the game.

### Phase 3 — Flying (`Vol`)
When a player has only **3 pieces** left, they may move to **any** empty intersection on the board.

### Winning Conditions
A player **loses** if:
- They have fewer than 3 pieces remaining (impossible to form a mill)
- All their pieces are blocked with no valid moves (during `Deplacement`)

---
