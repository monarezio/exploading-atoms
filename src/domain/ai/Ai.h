//
// Created by Samuel Kodytek on 27/06/2018.
//

#ifndef EXPLOADING_ATOMS_AI_H
#define EXPLOADING_ATOMS_AI_H

#include "../models/Field.h"
#include "../models/Coordinate.h"
#include "../ExploadingAtoms.h"

namespace exploading_atoms {

    namespace ai {

        class Ai {
        public:
            virtual Coordinate* getNextMove(ExploadingAtoms *exploadingAtoms) = 0;
        };

    }

}

#endif //EXPLOADING_ATOMS_AI_H
