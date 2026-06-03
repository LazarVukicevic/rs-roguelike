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

int TileColorPair(TileType t) {
    switch (t) {
        case TileType::kFloor:       return static_cast<int>(TileColorPairIndex::kFloor);
        case TileType::kWall:        return static_cast<int>(TileColorPairIndex::kWall);
        case TileType::kTree:        return static_cast<int>(TileColorPairIndex::kTree);
        case TileType::kTreeStump:   return static_cast<int>(TileColorPairIndex::kTreeStump);
        case TileType::kPlayerStart: return static_cast<int>(TileColorPairIndex::kDefault);
        case TileType::kInvalid:     return static_cast<int>(TileColorPairIndex::kDefault);
    }
    return static_cast<int>(TileColorPairIndex::kDefault);
}
