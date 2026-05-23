#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "player.h"
#include "map.h"

class PlayerController {
    Player& player_;
    Map& map_;
    public:
        PlayerController(Player& player, Map& map);
        bool ChopTree();
        void MoveUp();
        void MoveLeft();
        void MoveRight();
        void MoveDown();
    private:
        bool IsTree();
};

#endif