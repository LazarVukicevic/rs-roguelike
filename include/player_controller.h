#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "player.h"
#include "map.h"
#include "states.h"

class PlayerController {
    Player& player_;
    Map& map_;
    public:
        PlayerController(Player& player, Map& map);
        State ChopTree();
        State MineRock();
        void MoveUp();
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        State Interact();
        // bool AddItemToInventory(const Item& item);
    private:
        bool IsTree();
};

#endif