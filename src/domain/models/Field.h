//
// Created by Samuel Kodytek on 26/06/2018.
//

#ifndef EXPLOADING_ATOMS_FIELD_H
#define EXPLOADING_ATOMS_FIELD_H


#include "Player.h"

namespace exploading_atoms {

    class Field {
    private:
        int amount;
        Player player;
    public:
        Field(int amount = 0, Player player = none);
        ~Field();

        int getAmount();
        Player getPlayer();
    };

}


#endif //EXPLOADING_ATOMS_FIELD_H
