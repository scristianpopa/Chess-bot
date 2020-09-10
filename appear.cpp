#include "appear.h"

void apply_change(struct change* c, struct state* s)
{
    if (c->appear == 1) {
        // update kings
        if (c->piece == -'K') {
            s->king[0][0] = c->x;
            s->king[0][1] = c->y;
        }
        if (c->piece == 'K') {
            s->king[1][0] = c->x;
            s->king[1][1] = c->y;
        }
        s->board[(int)c->x][(int)c->y] = c->piece;
    } else {
        s->board[(int)c->x][(int)c->y] = 0;
    }
}

void undo_change(struct change* c, struct state* s)
{
    c->appear = -(c->appear);
    apply_change(c, s);
    c->appear = -(c->appear);
}

void apply_changes(vector<struct change>& chgs, struct state* s)
{
    for (auto c = chgs.begin(); c != chgs.end(); ++c) {
        apply_change(&(*c), s);
    }
}

void undo_changes(vector<struct change>& chgs, struct state* s)
{
    for (auto c = chgs.rbegin(); c != chgs.rend(); ++c) {
        undo_change(&(*c), s);
    }
}

void gen_move(struct state* s, int sx, int sy, int ex, int ey,
    vector<change>& rez)
{
    struct change c;
    c.x = sx;
    c.y = sy;
    c.appear = -1;
    c.piece = s->board[sx][sy];

    rez.push_back(c);

    c.x = ex;
    c.y = ey;
    c.appear = 1;

    rez.push_back(c);
}

void gen_capture(struct state* s, int sx, int sy, int ex, int ey,
    vector<change>& rez)
{

    struct change c;
    c.x = ex;
    c.y = ey;
    c.appear = -1;
    c.piece = s->board[ex][ey];

    rez.push_back(c);

    gen_move(s, sx, sy, ex, ey, rez);
}

void gen_moves(struct state* s, int sx, int sy, vector<pair<int, int>> end_pos,
    vector<vector<change>>& rez)
{

    for (auto& dest : end_pos) {
        vector<change> tmp;
        gen_move(s, sx, sy, dest.first, dest.second, tmp);
        rez.push_back(tmp);
    }
}

void gen_captures(struct state* s, int sx, int sy,
    vector<pair<int, int>> end_pos, vector<vector<change>>& rez)
{

    for (auto& dest : end_pos) {
        vector<change> tmp;
        gen_capture(s, sx, sy, dest.first, dest.second, tmp);
        rez.push_back(tmp);
    }
}

string chtos(vector<change>& c)
{
    string rez = "";
    auto fin = c.rbegin();
    fin++;
    rez += (fin->y + 'a');
    rez += ((fin->x + 1) + '0');
    fin = c.rbegin();
    rez += (fin->y + 'a');
    rez += ((fin->x + 1) + '0');
    fin++;
    return rez;
}

void stoch(string& s, vector<change>& c, struct state* st)
{
    change beg, fin;
    beg.y = s[0] - 'a';
    beg.x = s[1] - '1';
    beg.appear = -1;
    beg.piece = st->board[(int)beg.x][(int)beg.y];

    fin.y = s[2] - 'a';
    fin.x = s[3] - '1';
    fin.appear = 1;
    fin.piece = beg.piece;

    if ((beg.piece == 'P') && (fin.x == 7)) {
        fin.piece = s[4] - 'a' + 'A';
    }
    if ((beg.piece == -'P') && (fin.x == 0)) {
        fin.piece = -(s[4] - 'a' + 'A');
    }

    if (beg.piece * st->color == 'P' && st->board[(int)fin.x][(int)fin.y] == 0 && beg.y != fin.y) {

        change a;
        a.x = beg.x;
        a.y = fin.y;
        a.appear = -1;
        a.piece = -beg.piece;
        c.push_back(a);
    }

    if (beg.piece * st->color == 'K') {
        if (beg.y - fin.y == 2) {
            change a, b;
            a.y = 0;
            a.x = fin.x;
            a.appear = -1;
            a.piece = 'R' * st->color;

            b.y = fin.y + 1;
            b.x = fin.x;
            b.appear = 1;
            b.piece = a.piece;

            c.push_back(a);
            c.push_back(b);
        } else {
            if (fin.y - beg.y == 2) {
                change a, b;
                a.y = 7;
                a.x = fin.x;
                a.appear = -1;
                a.piece = 'R' * st->color;

                b.y = fin.y - 1;
                b.x = fin.x;
                b.appear = 1;
                b.piece = a.piece;

                c.push_back(a);
                c.push_back(b);
            }
        }
    }

    c.push_back(beg);
    c.push_back(fin);
}
