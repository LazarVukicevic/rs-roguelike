#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>

#include "direction.h"

class Map {
    std::vector<std::string> map_;
    public:
        Map(std::string& filename);
        void Load(std::string& filename);
        bool isWalkable(int y, int x);
        char GetAdjacentTile(int y, int x, Direction direction);
        char get_tile(int y, int x);
        void set_tile(int y, int x, char symbol);
    
};

#endif
