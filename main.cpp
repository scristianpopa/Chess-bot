#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "moves.h"
#include "search.h"
#include "state.h"

using namespace std;

fd_set intrare;
struct timeval tv;

ofstream dbg("debug-hardstuck.txt");

string read_string()
{
    string command;
    cin >> command;
    return command;
}

void init_comm()
{
    setbuf(stdout, NULL);
    dbg.setf(ios::unitbuf);
    cout.setf(ios::unitbuf);
    cin.setf(ios::unitbuf);

    printf("feature sigint=0 reuse=0\n");
    printf("feature sigterm=0 san=0\n");
    printf("feature colors=1\n");
    printf("feature time=0\n");
    printf("feature done=1\n");

    FD_ZERO(&intrare);
    FD_SET(0, &intrare);
    tv.tv_sec = 300;
    tv.tv_usec = 0;

    for (int i = 0; i < 25; i++) {
        string s = read_string();
    }
}

int main()
{

    init_comm();

    state* game = new state();
    int iplay = -1;

    string command;

    FILE* afis = fopen("debug-print.txt", "w");

    while (1) {
        if (iplay == game->color) {
            auto rezt = alfa_beta2(game, -100000, 100001, 1);
            for (int i = 2; i <= 5; i++) {
                rezt = alfa_beta2(game, rezt.second, 100001, i);
            }
            auto rez = rezt.first;
            cout << "move " << chtos(rez) << endl;
            apply_changes(rez, game);
            game->turn++;
            game->color = -game->color;
        } else {
            command = read_string();
            if (command == "quit") {
                return 0;
            } else if (command == "white") {
                iplay = 1;
                command = read_string();
            } else if (command == "black") {
                iplay = -1;
                command = read_string();
            } else if (command == "force") {
                command = read_string();
                while (command != "white" && command != "black") {
                    if ('0' <= command[1] && command[1] <= '9') {
                        vector<change> ch;
                        stoch(command, ch, game);
                        apply_changes(ch, game);
                        game->turn++;
                        game->color = -game->color;
                    }
                    command = read_string();
                }
                if (command == "white") {
                    iplay = 1;
                } else {
                    iplay = -1;
                }
                command = read_string();
            } else if ('0' <= command[1] && command[1] <= '9') {
                vector<change> ch;
                stoch(command, ch, game);
                apply_changes(ch, game);
                game->turn++;
                game->color = -game->color;
            }
        }
    }
    fclose(afis);
    return 0;
}