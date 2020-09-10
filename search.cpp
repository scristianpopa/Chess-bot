#include "search.h"
#include "moves.h"
#include <algorithm>
#include <fstream>
extern ofstream dbg;
int value[6][8][8] = { { { 0, 0, 0, 0, 0, 0, 0, 0 },
                           { 1, 2, 2, -4, -4, 2, 2, 1 },
                           { 1, -1, -2, 0, 0, -2, -1, 1 },
                           { 0, 0, 0, 4, 4, 0, 0, 0 },
                           { 1, 1, 2, 5, 5, 2, 1, 1 },
                           { 2, 2, 4, 6, 6, 4, 2, 2 },
                           { 10, 10, 10, 10, 10, 10, 10, 10 },
                           { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 1, 1, 0, 0, 0 },
        { -1, 0, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, 0, -1 },
        { -1, 0, 0, 0, 0, 0, 0, -1 },
        { 1, 2, 2, 2, 2, 2, 2, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { { -10, -8, -6, -6, -6, -6, -8, -10 },
        { -8, -4, 0, 1, 1, 0, -4, -8 },
        { -6, 1, 2, 3, 3, 2, 1, -6 },
        { -6, 0, 3, 4, 4, 3, 0, -6 },
        { -6, 1, 3, 4, 4, 3, 1, -6 },
        { -6, 0, 2, 3, 3, 2, 0, -6 },
        { -8, -4, 0, 0, 0, 0, -4, -8 },
        { -10, -8, -6, -6, -6, -6, -8, -10 } },
    { { -4, -2, -2, -2, -2, -2, -2, -4 },
        { -2, 1, 0, 0, 0, 0, 1, -2 },
        { -2, 2, 2, 2, 2, 2, 2, -2 },
        { -2, 0, 2, 2, 2, 2, 0, -2 },
        { -2, 1, 1, 2, 2, 1, 1, -2 },
        { -2, 0, 1, 2, 2, 1, 0, -2 },
        { -2, 0, 0, 0, 0, 0, 0, -2 },
        { -4, -2, -2, -2, -2, -2, -2, -4 } },
    { //{4, 6, 2, 0, 0, 2, 6, 4},
        { 4, 1, 1, 0, 0, 1, 1, 4 },
        { 4, 4, 0, 0, 0, 0, 4, 4 },
        { -2, -4, -4, -4, -4, -4, -4, -2 },
        { -4, -6, -6, -8, -8, -6, -6, -4 },
        { -6, -8, -8, -10, -10, -8, -8, -6 },
        { -6, -8, -8, -10, -10, -8, -8, -6 },
        { -6, -8, -8, -10, -10, -8, -8, -6 },
        { -6, -8, -8, -10, -10, -8, -8, -6 } },
    { { -4, -2, -2, -1, -1, -2, -2, -4 },
        { -2, 0, 1, 0, 0, 0, 0, -2 },
        { -2, 1, 1, 1, 1, 1, 0, -2 },
        { 0, 0, 1, 1, 1, 1, 0, -1 },
        { -1, 0, 1, 1, 1, 1, 0, -1 },
        { -2, 0, 1, 1, 1, 1, 0, -2 },
        { -2, 0, 0, 0, 0, 0, 0, -2 },
        { -4, -2, -2, -1, -1, -2, -2, -4 } } };

int estimate_depth(struct state* s)
{
    int a, b;
    vector<vector<change>> rez;
    gen_all_moves(s, s->color, rez);
    a = rez.size();
    rez.clear();
    gen_all_moves(s, -s->color, rez);
    b = rez.size();

    int x = 1;
    int tot_nodes = 1;
    while (tot_nodes < (10 * 50)) {
        if (x % 2 == 1) {
            tot_nodes *= a;
        } else {
            tot_nodes *= b;
        }
        x++;
    }
    x--;
    if (x < 4) {
        return 4;
    }
    return x;
}

int heuristic1(struct state* s, int color)
{
    int val = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            switch (s->board[i][j]) {
            case ('R'): {
                val += value[1][i][j];
                break;
            }
            case (-'R'): {
                val -= value[1][7 - i][j];
                break;
            }
            case ('N'): {
                val += value[2][i][j];
                break;
            }
            case (-'N'): {
                val -= value[2][7 - i][j];
                break;
            }
            case ('P'): {
                val += 2 * value[0][i][j];
                break;
            }
            case (-'P'): {
                val -= 2 * value[0][7 - i][j];
                break;
            }
            case ('B'): {
                val += value[3][i][j];
                break;
            }
            case (-'B'): {
                val -= value[3][7 - i][j];
                break;
            }
            case ('Q'): {
                val += value[5][i][j];
                break;
            }
            case (-'Q'): {
                val -= value[5][7 - i][j];
                break;
            }
            case ('K'): {
                val += value[4][i][j];
                break;
            }
            case (-'K'): {
                val -= value[4][7 - i][j];
                break;
            }
            default: {
                break;
            }
            }
        }
    }
    return val * color;
}

int heuristic2(struct state* s, int color)
{
    int val = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            switch (s->board[i][j]) {
            case ('R'): {
                val += 10;
                break;
            }
            case (-'R'): {
                val -= 10;
                break;
            }
            case ('N'): {
                val += 6;
                break;
            }
            case (-'N'): {
                val -= 6;
                break;
            }
            case ('P'): {
                val += 2;
                break;
            }
            case (-'P'): {
                val -= 2;
                break;
            }
            case ('B'): {
                val += 6;
                break;
            }
            case (-'B'): {
                val -= 6;
                break;
            }
            case ('Q'): {
                val += 18;
                break;
            }
            case (-'Q'): {
                val -= 18;
                break;
            }
            case ('K'): {
                val += 400;
                break;
            }
            case (-'K'): {
                val -= 400;
                break;
            }
            default: {
                break;
            }
            }
        }
    }
    return val * color;
}

int heuristic3(struct state* s, int color)
{
    int pozx = s->king[kcol(-color)][0];
    int pozy = s->king[kcol(-color)][1];

    int total_atk = 0;
    if (on_board(pozx, pozy))
        total_atk += 2 * check_attack(s, pozx, pozy, color);
    if (on_board(pozx + 1, pozy))
        total_atk += check_attack(s, pozx + 1, pozy, color);
    if (on_board(pozx, pozy + 1))
        total_atk += check_attack(s, pozx, pozy + 1, color);
    if (on_board(pozx - 1, pozy))
        total_atk += check_attack(s, pozx - 1, pozy, color);
    if (on_board(pozx, pozy - 1))
        total_atk += check_attack(s, pozx, pozy - 1, color);
    if (on_board(pozx + 1, pozy + 1))
        total_atk += check_attack(s, pozx + 1, pozy + 1, color);
    if (on_board(pozx - 1, pozy - 1))
        total_atk += check_attack(s, pozx - 1, pozy - 1, color);
    if (on_board(pozx + 1, pozy - 1))
        total_atk += check_attack(s, pozx + 1, pozy - 1, color);
    if (on_board(pozx - 1, pozy + 1))
        total_atk += check_attack(s, pozx - 1, pozy + 1, color);

    return total_atk;
}

int heuristic4(struct state* s, int color)
{
    int toto = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (s->board[i][j] * color > 0) {
                toto += check_attack(s, i, j, color);
            } else {
                if (s->board[i][j] * color < 0) {
                    toto -= check_attack(s, i, j, -color);
                }
            }
        }
    }

    return toto;
}

double apply_heuristics(struct state* s, int color)
{
    return 0.523 * heuristic1(s, color) + 4.069 * heuristic2(s, color);
}

const bool cmpState(const pair<double, vector<change>>& a,
    const pair<double, vector<change>>& b)
{
    ;
    return a.first > b.first;
}

void order_moves(vector<vector<change>>& moves, struct state* s)
{
    vector<pair<double, vector<change>>> unsorted;
    double gigel;
    for (auto& move : moves) {
        apply_changes(move, s);

        gigel = apply_heuristics(s, s->color);
        unsorted.push_back({ gigel, move });

        undo_changes(move, s);
    }

    sort(unsorted.begin(), unsorted.end(), cmpState);
    int size = moves.size();
    for (int i = 0; i < size; ++i) {
        moves[i] = unsorted[i].second;
    }
}

pair<vector<change>, double> alfa_beta2(struct state* s, double alpha,
    double beta, int depth)
{
    if (is_checkmate(s, s->color)) {
        return { vector<change>(), -100000 };
    }
    if (depth == 0) {
        return { vector<change>(), apply_heuristics(s, s->color) };
    }
    vector<vector<change>> moves;
    gen_all_moves(s, s->color, moves);
    order_moves(moves, s);

    double best = -100001;
    vector<change> best_move;
    for (auto& mov : moves) {
        apply_changes(mov, s);
        s->turn++;
        s->color = -(s->color);

        auto rez = alfa_beta2(s, -beta, -alpha, depth - 1);

        double score = -rez.second;

        if (score > best) {
            best = score;
            best_move = mov;
        }

        alpha = max(best, alpha);
        s->turn--;
        s->color = -(s->color);
        undo_changes(mov, s);

        if (alpha >= beta) {
            break;
        }
    }

    return { best_move, best };
}
