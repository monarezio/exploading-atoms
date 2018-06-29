//
// Created by Samuel Kodytek on 26/06/2018.
//

#include "Field.h"

exploading_atoms::Field::Field(int amount, exploading_atoms::Player player) {
    this->amount = amount;
    this->player = player;
}

exploading_atoms::Field::~Field() {}

int exploading_atoms::Field::getAmount() {
    return amount;
}

exploading_atoms::Player exploading_atoms::Field::getPlayer() {
    return player;
}
