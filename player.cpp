#include "player.h"

Player::Player(std::string player_name) : player_name_(player_name) {
}

std::string Player::get_player_name() {
    return player_name_;
}

void Player::gain_xp(Skill skill, int xp) {
    skill_xp_map_[skill] += xp;
}

void Player::level_up(Skill skill) {
    skill_level_map_[skill]++;
}

int Player::get_xp(Skill skill) {
    return skill_xp_map_[skill];
}

int Player::get_level(Skill skill) {
    return skill_level_map_[skill];
}

Direction Player::get_player_direction() {
    return player_direction_;
}

// char Player::ScanAdjacent(std::vector<std::string> &map, Direction direction) {
//     if (direction == Direction::Up) {
// 		return map[player_y_-1][player_x_];
// 	}
// 	else if (direction == Direction::Right) {
// 		return map[player_y_][player_x_+1];
// 	}
// 	else if (direction == Direction::Down) {
// 		return map[player_y_+1][player_x_];
// 	}
// 	else if (direction == Direction::Left) {
// 		return map[player_y_][player_x_-1];
// 	}
// }


void Player::set_player_direction(Direction new_direction) {
    player_direction_ = new_direction;
}

std::string Player::PrintPlayerDirection() {
    if (player_direction_ == Direction::Up) {
		return "UP";
	}
	else if (player_direction_ == Direction::Left) {
		return "LEFT";
	}
	else if (player_direction_ == Direction::Down) {
		return "DOWN";
	}
	else {
		return "RIGHT";
	}
}

void Player::set_player_x(int new_x) {
    player_x_ = new_x;
}

void Player::set_player_y(int new_y) {
    player_y_ = new_y;
}

int Player::get_player_y() {
    return player_y_;
}

int Player::get_player_x() {
    return player_x_;
}