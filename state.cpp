#include "state.h"
#include "appear.h"
#include "moves.h"
#include "search.h"

using namespace std;

state::state()
{
    for (int i = 0; i < 8; i++) {
        board[1][i] = 'P';
    }

    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';

    for (int i = 0; i < 8; i++) {
        board[7][i] = -board[0][i];
        board[6][i] = -board[1][i];
    }

    turn = 0;
    color = 1;
    king[0][0] = 7; // 0 - black // 1 - white
    king[0][1] = 4;
    king[1][0] = 0;
    king[1][1] = 4;

    check = false;
}

char check_attack(struct state* s, int x, int y, int color)
{
    vector<pair<int, int>> mov, capt;
    rook_possible(s, x, y, -color, mov, capt);
    for (auto& poz : capt) {
        if (s->board[poz.first][poz.second] == 'R' * color || s->board[poz.first][poz.second] == 'Q' * color) {
            return 1;
        }
    }

    mov.clear();
    capt.clear();

    bishop_possible(s, x, y, -color, mov, capt);
    for (auto& poz : capt) {
        if (s->board[poz.first][poz.second] == 'B' * color || s->board[poz.first][poz.second] == 'Q' * color) {
            return 1;
        }
    }

    mov.clear();
    capt.clear();

    knight_possible(s, x, y, -color, mov, capt);
    for (auto& poz : capt) {
        if (s->board[poz.first][poz.second] == 'N' * color) {
            return 1;
        }
    }

    mov.clear();
    capt.clear();

    king_possible(s, x, y, -color, mov, capt);
    for (auto& poz : capt) {
        if (s->board[poz.first][poz.second] == 'K' * color) {
            return 1;
        }
    }

    mov.clear();
    capt.clear();

    int pozx = x - color;
    int pozy = y - 1;
    if (on_board(pozx, pozy) && s->board[pozx][pozy] == 'P' * color) {
        return 1;
    }

    pozx = x - color;
    pozy = y + 1;
    if (on_board(pozx, pozy) && s->board[pozx][pozy] == 'P' * color) {
        return 1;
    }

    return 0;
}

void gen_all_moves(struct state* s, int color, vector<vector<change>>& final)
{
    vector<vector<change>> rez;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (s->board[i][j] * color > 0) {
                vector<pair<int, int>> mov, capt;
                switch (s->board[i][j] * color) {
                case 'P':
                    pawn_possible(s, i, j, color, mov, capt);
                    break;
                case 'R':
                    rook_possible(s, i, j, color, mov, capt);
                    break;
                case 'N':
                    knight_possible(s, i, j, color, mov, capt);
                    break;
                case 'B':
                    bishop_possible(s, i, j, color, mov, capt);
                    break;
                case 'Q':
                    rook_possible(s, i, j, color, mov, capt);
                    bishop_possible(s, i, j, color, mov, capt);
                    break;
                case 'K':
                    king_possible(s, i, j, color, mov, capt);
                    break;
                default:
                    break;
                }
                gen_captures(s, i, j, capt, rez);
                gen_moves(s, i, j, mov, rez);
            }
        }
    }

    for (auto& diff : rez) {
        if (diff.back().piece * color == 'P') {
            if (diff.back().x == 7 && color == 1) {
                diff.back().piece = 'Q';
            }
            if (diff.back().x == 0 && color == -1) {
                diff.back().piece = -'Q';
            }
        }

        apply_changes(diff, s);

        int in_check = check_attack(s, s->king[kcol(color)][0],
            s->king[kcol(color)][1], -color);
        if (!in_check) {
            final.push_back(diff);
        }
        undo_changes(diff, s);
    }
}

int is_checkmate(struct state* s, int color)
{
    vector<vector<change>> rez;
    gen_all_moves(s, color, rez);

    if (rez.size() == 0) {
        return 1;
    } else {
        return 0;
    }
}

int kcol(int color)
{
    if (color == -1) {
        return 0;
    }
    return 1;
}

void print_board(struct state* s, FILE* afis)
{
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (s->board[i][j] != 0) {
                if (s->board[i][j] < 0) {
                    fprintf(afis, "%c", (char)((-s->board[i][j]) - 'A' + 'a'));
                } else {
                    fprintf(afis, "%c", (char)(s->board[i][j]));
                }
            } else {
                fprintf(afis, ".");
            }
        }
        fprintf(afis, "\n");
    }
    fflush(afis);
}
