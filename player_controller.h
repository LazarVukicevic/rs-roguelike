#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "player.h"

class PlayerController {

    public:
        void ChopTree(Player &player);
        char ScanAdjacent(Player &player, std::vector<std::string> &map, Direction direction);
};

#endif