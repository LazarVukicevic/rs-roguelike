#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "coordinate.h"
#include "direction.h"
#include "tile.h"

class Map {
    std::vector<std::vector<TileType>> map_;
    size_t max_width = 0;
    public:
        Map(const std::string& filename);
        bool IsWalkable(int y, int x);
        TileType GetAdjacentTile(int y, int x, Direction direction);
        TileType GetTile(int y, int x);
        void SetTile(int y, int x, TileType tile);
        Coordinate FindPlayerStart();
        int GetHeight();
        int GetWidth();
        int GetWidth(int row);
    
};

#endif
