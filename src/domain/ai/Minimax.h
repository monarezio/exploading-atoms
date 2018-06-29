//
// Created by Samuel Kodytek on 27/06/2018.
//

#ifndef EXPLOADING_ATOMS_MINIMAX_H
#define EXPLOADING_ATOMS_MINIMAX_H


#include "Ai.h"
#include "../ExploadingAtoms.h"

namespace exploading_atoms {
    namespace ai {
        class Minimax: public Ai {
        private:
            int minimax(ExploadingAtoms *exploadingAtoms, bool max, int depth);
            int biggest_number(int** array, int rows, int columns);
            int smallest_number(int **array, int rows, int columns);
        public:
            Coordinate* getNextMove(ExploadingAtoms *exploadingAtoms) override;
        };
    }
}


#endif //EXPLOADING_ATOMS_MINIMAX_H
