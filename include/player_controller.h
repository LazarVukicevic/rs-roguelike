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
        void MoveUp();
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        std::string PrintInventory();
        std::string PrintInventory(int index);
        bool AddItemToInventory(const Item& item);
    private:
        bool IsTree();
};

#endif