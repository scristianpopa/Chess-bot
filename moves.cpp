#include "moves.h"

int on_board(int x, int y)
{
    if (x >= 0 && y >= 0 && x < 8 && y < 8) {

        return 1;
    } else {
        return 0;
    }
}

void rook_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture)
{

    int posx = x;
    int posy = y - 1;
    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posy--;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x;
    posy = y + 1;
    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posy++;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x - 1;
    posy = y;
    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx--;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x + 1;
    posy = y;
    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx++;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }
}

void bishop_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture)
{
    int posx = x - 1;
    int posy = y - 1;

    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx--;
        posy--;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x + 1;
    posy = y - 1;

    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx++;
        posy--;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x - 1;
    posy = y + 1;

    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx--;
        posy++;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x + 1;
    posy = y + 1;

    while (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
        posx++;
        posy++;
    }
    if (on_board(posx, posy) && (s->board[posx][posy] * color < 0)) {
        capture.push_back(make_pair(posx, posy));
    }
}

void knight_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture)
{

    int posx = x + 1;
    int posy = y + 2;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 1;
    posy = y + 2;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x + 1;
    posy = y - 2;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 1;
    posy = y - 2;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x + 2;
    posy = y + 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 2;
    posy = y + 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x + 2;
    posy = y - 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 2;
    posy = y - 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }
}

void king_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture)
{

    int posx = x + 1;
    int posy = y;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 1;
    posy = y;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x;
    posy = y + 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x;
    posy = y - 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x + 1;
    posy = y + 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 1;
    posy = y + 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x + 1;
    posy = y - 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }

    posx = x - 1;
    posy = y - 1;

    if (on_board(posx, posy)) {
        if (s->board[posx][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
        if (s->board[posx][posy] * color < 0) {
            capture.push_back(make_pair(posx, posy));
        }
    }
}

void pawn_possible(state* s, int x, int y, int color,
    vector<pair<int, int>>& moves,
    vector<pair<int, int>>& capture)
{

    int posx = x + 2 * color;
    int posy = y;

    if ((x == 1 && color == 1) || (x == 6 && color == -1)) {

        if (on_board(posx, posy) && s->board[posx][posy] == 0 && s->board[posx - color][posy] == 0) {
            moves.push_back(make_pair(posx, posy));
        }
    }

    posx = x + color;
    posy = y;

    if (on_board(posx, posy) && s->board[posx][posy] == 0) {
        moves.push_back(make_pair(posx, posy));
    }

    posx = x + color;
    posy = y + 1;

    if (on_board(posx, posy) && s->board[posx][posy] * color < 0) {
        capture.push_back(make_pair(posx, posy));
    }

    posx = x + color;
    posy = y - 1;

    if (on_board(posx, posy) && s->board[posx][posy] * color < 0) {
        capture.push_back(make_pair(posx, posy));
    }
}
