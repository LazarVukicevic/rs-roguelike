#include "tile.h"

std::wstring TileGlyph(TileType t) {
    switch (t) {
        case TileType::kFloor:       return L" ";
        case TileType::kWall:        return L"#";
        case TileType::kTree:        return L"♣";
        case TileType::kTreeStump:   return L"%";
        case TileType::kPlayerStart: return L"☺︎";
        case TileType::kInvalid:     return L"`";
        case TileType::kBank:        return L"ß";
        case TileType::kRock:        return L"▲";
    }
    return L"?";
}

TileType TileFromChar(char c) {
    switch (c) {
        case ' ':  return TileType::kFloor;
        case '#':  return TileType::kWall;
        case 'T':  return TileType::kTree;
        case '@':  return TileType::kPlayerStart;
        case 'B':  return TileType::kBank;
        case 'X':  return TileType::kRock;
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
        case TileType::kBank:        return static_cast<int>(TileColorPairIndex::kBank);
        case TileType::kRock:        return static_cast<int>(TileColorPairIndex::kRock);
    }
    return static_cast<int>(TileColorPairIndex::kDefault);
}
