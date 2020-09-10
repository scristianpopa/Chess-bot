#ifndef _STATE_H
#define _STATE_H

#include <sstream>
#include <vector>

#include "appear.h"

using namespace std;

class state {
public:
    char board[8][8];
    int turn;
    int color;
    char king[2][2];
    bool check;
    state();
};

// checks if color atacks (x, y) in state s
char check_attack(struct state* s, int x, int y, int color);

// generates all possible moves in state s, when color attacks
void gen_all_moves(struct state* s, int color,
    vector<vector<struct change>>& final);

int in_turn(struct state* s);

int is_checkmate(struct state* s, int color);

// used for king coordinates
int kcol(int color);

void print_board(struct state* s, FILE* afis);

#endif