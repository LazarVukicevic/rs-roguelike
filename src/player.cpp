#include "player.h"

Player::Player(std::string player_name) : player_name_(player_name) {
}

std::string Player::GetName() {
    return player_name_;
}

void Player::GainXp(Skill skill, int xp) {
    skill_xp_map_[skill] += xp;
}

void Player::LevelUp(Skill skill) {
    skill_level_map_[skill]++;
}

int Player::GetXp(Skill skill) {
    return skill_xp_map_[skill];
}

int Player::GetLevel(Skill skill) {
    return skill_level_map_[skill];
}

Direction Player::GetDirection() {
    return player_direction_;
}


void Player::SetDirection(Direction new_direction) {
    player_direction_ = new_direction;
}

std::string Player::PrintDirection() {
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

void Player::SetX(int new_x) {
    player_x_ = new_x;
}

void Player::SetY(int new_y) {
    player_y_ = new_y;
}

int Player::GetY() {
    return player_y_;
}

int Player::GetX() {
    return player_x_;
}

Inventory& Player::GetInventory() {
    return inventory_;
}