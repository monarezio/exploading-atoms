//
// Created by Samuel Kodytek on 27/06/2018.
//

#include "Minimax.h"

#include <iostream>

int exploading_atoms::ai::Minimax::minimax(exploading_atoms::ExploadingAtoms *exploadingAtoms, bool max, int depth) {
    if(depth == 0)
        return exploadingAtoms->count(blue); //AI is always blue!

    Player winner = exploadingAtoms->getWinner();
    if(winner == blue) {
        return 99999;
    }
    else if(winner == red) {
        return -99999;
    }
    else {

        int **evals = new int*[exploadingAtoms->getRows()];

        for (int i = 0; i < exploadingAtoms->getRows(); i++) {
            evals[i] = new int[exploadingAtoms->getColumns()];
            for (int j = 0; j < exploadingAtoms->getColumns(); j++) {
                Player fieldPlayer = exploadingAtoms->getField(j, i).getPlayer();
                if(fieldPlayer == blue || fieldPlayer == none) {
                    ExploadingAtoms *state = new ExploadingAtoms(exploadingAtoms);
                    state->move(j, i);
                    evals[i][j] = minimax(state, !max, depth - 1);

                    delete state;
                } else {
                    evals[i][j] = -1;
                }
            }
        }

        int eval = 0;

        if (max) {
            eval = biggest_number(evals, exploadingAtoms->getRows(), exploadingAtoms->getColumns());
        } else {
            eval = smallest_number(evals, exploadingAtoms->getRows(), exploadingAtoms->getColumns());
        }

        //Clear the memory
        for (int k = 0; k < exploadingAtoms->getRows(); k++)
            delete[] evals[k];
        delete[] evals;

        return eval;
    }
}

int exploading_atoms::ai::Minimax::biggest_number(int **array, int rows, int columns) {

    int number = -1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(number <= array[i][j])
                number = array[i][j];
        }
    }

    return number;
}

int exploading_atoms::ai::Minimax::smallest_number(int **array, int rows, int columns) {

    int number = rows * columns * 3; //max amount available of atoms

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(array[i][j] != -1 && number >= array[i][j])
                number = array[i][j];
        }
    }

    return number;
}

Coordinate *exploading_atoms::ai::Minimax::getNextMove(exploading_atoms::ExploadingAtoms *exploadingAtoms) {
    int **array = new int*[exploadingAtoms->getRows()];

    int number = -1;
    int x = 0;
    int y = 0;

    for (int i = 0; i < exploadingAtoms->getRows(); i++) {
        array[i] = new int[exploadingAtoms->getColumns()];
        for (int j = 0; j < exploadingAtoms->getColumns(); j++) {
            Player fieldPlayer = exploadingAtoms->getField(j, i).getPlayer();
            if(fieldPlayer == blue || fieldPlayer == none) {
                ExploadingAtoms *state = new ExploadingAtoms(exploadingAtoms);
                state->move(j, i);
                array[i][j] = minimax(state, false, 2) * 100;
                delete state;
            } else {
                array[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < exploadingAtoms->getRows(); i++) {
        for (int j = 0; j < exploadingAtoms->getColumns(); j++) {
            Player fieldPlayer = exploadingAtoms->getField(j, i).getPlayer();
            if(fieldPlayer == blue || fieldPlayer == none) {
                array[i][j] -= abs(exploadingAtoms->getRows() / 2 - i) + abs(exploadingAtoms->getColumns() / 2 - j);

                if (exploadingAtoms->isInGrid(j, i + 1) && array[i + 1][j] == -1)
                    array[i][j] -= 2;
                if (exploadingAtoms->isInGrid(j, i - 1) && array[i - 1][j] == -1)
                    array[i][j] -= 2;
                if (exploadingAtoms->isInGrid(j - 1, i) && array[i][j - 1] == -1)
                    array[i][j] -= 2;
                if (exploadingAtoms->isInGrid(j + 1, i) && array[i][j + 1] == -1)
                    array[i][j] -= 2;
            }

            if(array[i][j] != -1 && number <= array[i][j]) {
                number = array[i][j];
                x = j;
                y = i;
            }
        }
    }



    return new Coordinate(x, y);
}

