#include "tile.h"

std::wstring TileGlyph(TileType t) {
    switch (t) {
        case TileType::kFloor:       return L" ";
        case TileType::kWall:        return L"#";
        case TileType::kTree:        return L"T";
        case TileType::kTreeStump:   return L"ףּ";
        case TileType::kPlayerStart: return L"@";
        case TileType::kInvalid:     return L"`";
    }
    return L"?";
}

TileType TileFromChar(char c) {
    switch (c) {
        case ' ':  return TileType::kFloor;
        case '#':  return TileType::kWall;
        case 'T':  return TileType::kTree;
        case '@':  return TileType::kPlayerStart;
        default:   return TileType::kInvalid;
    }
}
