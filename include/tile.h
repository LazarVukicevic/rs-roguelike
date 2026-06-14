#ifndef TILE_H
#define TILE_H

#include <string>

enum class TileType {
    kFloor,
    kWall,
    kTree,
    kTreeStump,
    kPlayerStart,
    kInvalid,
    kBank
};

enum class TileColorPairIndex {
    kFloor      = 1,
    kWall       = 2,
    kTree       = 3,
    kTreeStump  = 4,
    kPlayer     = 5,
    kDefault    = 6,
    kBank       = 7
};

std::wstring TileGlyph(TileType t);
TileType TileFromChar(char c);
int TileColorPair(TileType t);

#endif
