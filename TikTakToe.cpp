#include <iostream>
#include "TikTakToe.h"

TikTakToe::TikTakToe() {
    for (auto &i : grid) {
        for (char &j : i) {
            j = ' ';
        }
    }
}

void  TikTakToe ::print() {
    std::cout << '\n';
    for (int i = 0; i < 3; i++) {
        if (i) {
            std::cout << "-----------\n";
        }
        for (int j = 0; j < 3; j++) {
            if (j) {
                std::cout << "|";
            }
            std::cout << ' ';
            if (grid[i][j] == ' ') {
                std::cout << 3 * i + j + 1;
            } else {
                std::cout << grid[i][j];
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void TikTakToe::playerMove() {
    while (true) {
        std::cout << "Please enter an empty cell from (1 - 9) \n";
        int cell;
        std::cin >> cell;
        if (cell >= 1 && cell <= 9) {
            int row = (cell - 1) / 3;
            int column = (cell - 1) % 3;
            if(grid[row][column]!=' ')
                goto Error;
            grid[row][column] = player;
            break;
        } else {
            Error:std::cout << "ERORR: please enter valid empty cell \n";
        }

    }
}

Move TikTakToe::minimax(bool maximizingPlayer= true) {
    Move bestMove;
    if (win()) {
        if (maximizingPlayer) {
            bestMove.score = -1;
        } else {
            bestMove.score = 1;
        }
        return bestMove;
    } else if (tie()) {
        bestMove.score = 0;
        return bestMove;
    }
    bestMove.score = maximizingPlayer ? -2 : 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = maximizingPlayer ? computer : player;
                Move state = minimax(!maximizingPlayer);
                if (maximizingPlayer) {
                    if (state.score > bestMove.score) {
                        bestMove.score = state.score;
                        bestMove.row = i;
                        bestMove.column = j;
                    }
                } else {
                    if (state.score < bestMove.score) {
                        bestMove.score = state.score;
                        bestMove.row = i;
                        bestMove.column = j;
                    }
                }
                grid[i][j] = ' ';
            }
        }
    }
    return bestMove;
}

void TikTakToe::computerMove() {
    Move bestMove = minimax();
    grid[bestMove.row][bestMove.column] = computer;
}


bool TikTakToe::win() {
    int winStates[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (auto & winState : winStates) {
        bool win = true;
        int firstRow = winState[0] / 3, firstColumn = winState[0] % 3;
        for (int j : winState) {
            int row = j / 3, column= j % 3;
            if (grid[firstRow][firstColumn] == ' ' || grid[firstRow][firstColumn] != grid[row][column]) {
                win = false;
            }
        }
        if (win)
            return true;
    }
    return false;
}

bool  TikTakToe::tie() {
    if(win())
        return false;
    for (auto & i : grid) {
        for (char j : i) {
            if(j==' ')
                return false;
        }
    }
    return true;
}

void TikTakToe::play() {
    while (true) {
        std::cout << "which symbol you choose (x or y, x goes first)? ";
        std::cin >> player;
        if (player == 'x' || player == 'o')
            break;
        std::cout << "ERORR: please enter valid symbol \n";
    }
    computer = player == 'x' ? 'o' : 'x';
    if(computer == 'x'){
        std::cout<<"Computer is making a move ...\n";
        computerMove();
    }
    print();
    while (true) {
        playerMove();
        print();
        if (win()) {
            std::cout << "Player wins!\n";
            return;
        } else if (tie()) {
            std::cout << "Tie!\n";
            return;
        }
        std::cout<<"Computer is making a move ...\n";
        computerMove();
        print();
        if (win()) {
            std::cout << "Computer wins!\n";
            return;
        } else if (tie()) {
            std::cout << "Tie!\n";
            return;
        }
    }
}