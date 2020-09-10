#ifndef _MOVES_H
#define _MOVES_H

#include "state.h"
#include <utility>
#include <vector>

using namespace std;

int on_board(int x, int y);

// generating all possible moves a piece can make from (x, y)
// queen moves are bishops + rook
void rook_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture);

void bishop_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture);

void knight_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture);

void king_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture);

void pawn_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture);

#endif