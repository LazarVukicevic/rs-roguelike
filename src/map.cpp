#include "map.h"
#include <fstream>
#include <stdexcept>

Map::Map(const std::string& filename) {
    std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Failed to open map file");
	}

	std::string line;

	while (std::getline(file, line)) {
		if(!line.empty()) {
			std::vector<TileType> row;
			row.reserve(line.size());
			for (char c : line) {
				row.push_back(TileFromChar(c));
			}
			map_.push_back(row);
			max_width = std::max(max_width, row.size());
		}
	}
}

TileType Map::GetTile(int y, int x) {
	if (y < 0 || y >= GetHeight() || x < 0 || x >= GetWidth(y)) {
		return TileType::kInvalid;
	}
    return map_[y][x];
}

void Map::SetTile(int y, int x, TileType tile) {
    map_[y][x] = tile;
}

Coordinate Map::FindPlayerStart() {
    for (int y = 0; y < GetHeight(); y++) {
        for (int x = 0; x < GetWidth(y); x++) {
            if (map_[y][x] == TileType::kPlayerStart) {
                map_[y][x] = TileType::kFloor;
                return {y, x};
            }
        }
    }
    return {1, 1};
}

TileType Map::GetAdjacentTile(int y, int x, Direction direction) {
    if (direction == Direction::Up) {
		return map_[y-1][x];
	}
	else if (direction == Direction::Right) {
		return map_[y][x+1];
	}
	else if (direction == Direction::Down) {
		return map_[y+1][x];
	}
	else { // left
		return map_[y][x-1];
	}
}

bool Map::IsWalkable(int y, int x) {
	if (y > 0 && y < GetHeight()-1 && x > 0 && x < GetWidth()-1 && map_[y][x] == TileType::kFloor) {
				return true;
		}
	return false;
}

int Map::GetHeight() {
	return map_.size();
}

int Map::GetWidth() {
	return max_width;
}

int Map::GetWidth(int row) {
	return map_[row].size();
}

bool Map::IsTree(Coordinate coords) {
	return map_[coords.y][coords.x] == TileType::kTree;
}

bool Map::IsRock(Coordinate coords) {
	return map_[coords.y][coords.x] == TileType::kRock;
}