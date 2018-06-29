//
// Created by Samuel Kodytek on 26/06/2018.
//

#include <iostream>
#include "ExploadingAtoms.h"

exploading_atoms::ExploadingAtoms::ExploadingAtoms(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    this->moves = 0;
    this->playerOnMove = red;

    this->grid = new Field*[rows];
    for (int i = 0; i < rows; i++)
        this->grid[i] = new Field[columns];
}

/**
 * Deep copy contructor
 */
exploading_atoms::ExploadingAtoms::ExploadingAtoms(exploading_atoms::ExploadingAtoms *exploadingAtoms) {
    this->rows = exploadingAtoms->getRows();
    this->columns = exploadingAtoms->getColumns();
    this->moves = exploadingAtoms->getMoves();
    this->playerOnMove = exploadingAtoms->getPlayerOnMove();

    this->grid = new Field*[rows];
    for (int i = 0; i < rows; i++) {
        this->grid[i] = new Field[columns];
        for(int j = 0; j < columns; j++) {
            this->grid[i][j] = exploadingAtoms->getField(j, i);
        }
    }
}

exploading_atoms::ExploadingAtoms::~ExploadingAtoms() {
    for (int i = 0; i < rows; i++)
        delete[] grid[i];
    delete[] grid;
}

void exploading_atoms::ExploadingAtoms::move(int x, int y) {
    if(isValidMove(x, y) && getWinner() == none) {
        spread(x, y);
        playerOnMove = playerOnMove == red ? blue : red;
        moves++;
    }
}

exploading_atoms::Player exploading_atoms::ExploadingAtoms::getWinner() {
    if(moves <= 1)
        return none;

    bool didRedWin = true;
    bool didBlueWin = true;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(grid[i][j].getPlayer() == red)
                didBlueWin = false;
            else if(grid[i][j].getPlayer() == blue)
                didRedWin = false;
        }
    }

    if(didBlueWin)
        return blue;
    else if(didRedWin)
        return red;
    return none;
}

int exploading_atoms::ExploadingAtoms::getColumns() {
    return columns;
}

int exploading_atoms::ExploadingAtoms::getRows() {
    return rows;
}

bool exploading_atoms::ExploadingAtoms::isInGrid(int x, int y) {
    return x >= 0 && x < columns && y >= 0 && y < rows;
}

bool exploading_atoms::ExploadingAtoms::isValidMove(int x, int y) {
    return grid[y][x].getPlayer() == none || playerOnMove == grid[y][x].getPlayer();
}

exploading_atoms::Player exploading_atoms::ExploadingAtoms::getPlayerOnMove() {
    return playerOnMove;
}

void exploading_atoms::ExploadingAtoms::spread(int x, int y) {
    if(isInGrid(x, y)) {
        Field field = grid[y][x];
        if(field.getAmount() + 1 > 3) {
            grid[y][x] = Field(0, none);
            spread(x + 1, y);
            spread(x - 1, y);
            spread(x, y + 1);
            spread(x, y - 1);
        } else {
            grid[y][x] = Field(field.getAmount() + 1, playerOnMove);
        }
    }
}

exploading_atoms::Field exploading_atoms::ExploadingAtoms::getField(int x, int y) {
    return grid[y][x];
}

int exploading_atoms::ExploadingAtoms::count(exploading_atoms::Player player) {

    int counter = 0;

    for (int i = 0; i < getColumns(); i++) {
        for (int j = 0; j < getRows(); j++) {
            if(grid[j][i].getPlayer() == player) {
                counter += grid[j][i].getAmount();
            }
        }
    }

    return counter;
}

int exploading_atoms::ExploadingAtoms::getMoves() {
    return moves;
}
