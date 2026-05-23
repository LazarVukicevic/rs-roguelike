#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "direction.h"

class Map {
    std::vector<std::string> map_;
    size_t max_width = 0;
    public:
        Map(const std::string& filename);
        bool IsWalkable(int y, int x);
        char GetAdjacentTile(int y, int x, Direction direction);
        char GetTile(int y, int x);
        void SetTile(int y, int x, char symbol);
        int GetHeight();
        int GetWidth();
    
};

#endif
