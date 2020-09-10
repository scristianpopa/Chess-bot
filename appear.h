#ifndef _APPEAR_H
#define _APPEAR_H

#include "state.h"
#include <string>
#include <vector>

using namespace std;

// we use this to say that the piece from (x, y) appears or disappears
// this way, when some piece moves from (a, b) to (x, y), it shall
// disappear from (a, b) and appear at (x, y)
struct change {
    char x, y, piece, appear;
};

void apply_change(struct change* c, struct state* s);
void undo_change(struct change* c, struct state* s);
void apply_changes(vector<struct change>& chgs, struct state* s);
void undo_changes(vector<struct change>& chgs, struct state* s);

void gen_move(struct state* s, int sx, int sy, int ex, int ey,
    vector<change>& rez);
void gen_capture(struct state* s, int sx, int sy, int ex, int ey,
    vector<change>& rez);

// generates all moves from (sx, sy) to (ex, ey)
void gen_moves(struct state* s, int sx, int sy, vector<pair<int, int>> end_pos,
    vector<vector<change>>& rez);

// generates all captures from (sx, sy) to (ex, ey)
void gen_captures(struct state* s, int sx, int sy,
    vector<pair<int, int>> end_pos, vector<vector<change>>& rez);
void gen_castle(struct state* s, vector<vector<change>>& rez);

// transforms commands from xboard to game engine and vice-versa
string chtos(vector<change>& c);
void stoch(string& s, vector<change>& c, struct state* st);

#endif