#include <fstream>
#include <stdexcept>
#include "map.h"

Map::Map(const std::string& filename) {
    std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Failed to open map file");
	}

	std::string line;

	while (std::getline(file, line)) {
		if(!line.empty()) {
			map_.push_back(line);
			max_width = std::max(max_width, line.size());
		}
	}
}

char Map::GetTile(int y, int x) {
	if (y < 0 || y >= GetHeight() || x < 0 || x >= GetWidth()) {
		return '`'; // invalid tile is `
	}
    return map_[y][x];
}

void Map::SetTile(int y, int x, char symbol) { // need to ensure illegal characters are not added
    map_[y][x] = symbol;
}

char Map::GetAdjacentTile(int y, int x, Direction direction) {
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
	if (y > 0 && y < GetHeight()-1 && x > 0 && x < GetWidth()-1 && map_[y][x] == ' ') {
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