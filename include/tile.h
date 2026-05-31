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
};

std::wstring TileGlyph(TileType t);
TileType TileFromChar(char c);

#endif
