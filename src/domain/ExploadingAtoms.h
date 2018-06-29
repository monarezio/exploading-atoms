//
// Created by Samuel Kodytek on 26/06/2018.
//

#ifndef EXPLOADING_ATOMS_EXPLOADINGATOMS_H
#define EXPLOADING_ATOMS_EXPLOADINGATOMS_H

#include "models/Player.h"
#include "models/Field.h"

namespace exploading_atoms {

    class ExploadingAtoms {

    private:
        int columns;
        int rows;
        int moves;
        Field** grid;
        Player playerOnMove;

        void spread(int x, int y);

        bool isValidMove(int x, int y);
    public:
        ExploadingAtoms(int rows, int columns);
        ExploadingAtoms(ExploadingAtoms *exploadingAtoms);
        ~ExploadingAtoms();
        void move(int x, int y);

        Player getWinner();

        int getColumns();
        int getRows();
        int getMoves();
        Field getField(int x, int y);
        Player getPlayerOnMove();
        int count(Player player);

        bool isInGrid(int x, int y);
    };

}


#endif //EXPLOADING_ATOMS_EXPLOADINGATOMS_H
