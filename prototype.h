#ifndef PROTOTYPE_H
#define PROTOTYPE_H

typedef enum { PLAYER1, PLAYER2, NONE } Player;
typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Player player;
    Position position;
} Piece;

typedef struct {
    Piece pieces[24]; // Assumed number of pieces
    int pieceCount;
} GameState;

typedef struct {
    Position from;
    Position to;
} Move;

// Function prototypes
void gameLoop();
void displayHighlighted();
void generateMoves();
int minimax(int depth);
int alphaBeta(int depth);
void helperFunction1();
void helperFunction2();

#endif // PROTOTYPE_H
