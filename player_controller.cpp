#include "player_controller.h"

void PlayerController::ChopTree(Player &player) {
    player.gain_xp(Skill::Woodcutting, 25);
}

char PlayerController::ScanAdjacent(Player &player, std::vector<std::string> &map, Direction direction) {
    if (direction == Direction::Up) {
		return map[player.get_player_y()-1][player.get_player_x()];
	}
	else if (direction == Direction::Right) {
		return map[player.get_player_y()][player.get_player_x()+1];
	}
	else if (direction == Direction::Down) {
		return map[player.get_player_y()+1][player.get_player_x()];
	}
	else if (direction == Direction::Left) {
		return map[player.get_player_y()][player.get_player_x()-1];
	}
}