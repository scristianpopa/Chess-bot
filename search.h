#ifndef _SEARCH_H
#define _SEARCH_H

#include "state.h"
#include <vector>

const int MAX_DEPTH = 4;

int estimate_depth(struct state* s);

int heuristic1(struct state* s, int color);
int heuristic2(struct state* s, int color);
int heuristic3(struct state* s, int color);
int heuristic4(struct state* s, int color);

double apply_heuristics(struct state* s, int color);

vector<change> negamax(struct state* s, int k, double* val);

pair<vector<change>, double> alfa_beta(struct state* s, double alfa,
    double beta, int depth);
pair<vector<change>, double> alfa_beta2(struct state* s, double alpha,
    double beta, int depth);

#endif