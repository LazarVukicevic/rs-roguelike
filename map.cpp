#include "map.h"

Map::Map(std::string& filename) {
    Load(filename);
}

void Map::Load(std::string& filename) {
    std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Failed to open map file");
	}

	std::vector<std::string> map;
	std::string line;

	while (std::getline(file, line)) {
		if(!line.empty()) {
			map.push_back(line);
		}
	}
	map_ = map;
}

char Map::get_tile(int y, int x) { // need to add boundary check
    return map_[y][x];
}

void Map::set_tile(int y, int x, char symbol) { // need to ensure illegal characters are not added
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
	else if (direction == Direction::Left) {
		return map_[y][x-1];
	}
}

bool Map::isWalkable(int y, int x) {
    return map_[y][x] == ' ';
}