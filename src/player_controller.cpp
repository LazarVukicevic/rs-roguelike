#include "player_controller.h"

PlayerController::PlayerController(Player& player, Map& map) : player_(player), map_(map) { }

bool PlayerController::IsTree() {
	return 
		map_.GetAdjacentTile(player_.GetY(), player_.GetX(), player_.GetDirection()) == 'T';
}

bool PlayerController::ChopTree() {
	if(!IsTree()) {
		return false;
	}
	else if(player_.GetInventory().IsFull()) {
		return false;
	}
    player_.GainXp(Skill::Woodcutting, 25);
	player_.GetInventory().AddItem({"Logs", 1});
	return true;
}

void PlayerController::MoveUp() {
	player_.SetDirection(Direction::Up);
	if (map_.IsWalkable(player_.GetY()-1, player_.GetX())) {
		player_.SetY(player_.GetY()-1);
	}
}

void PlayerController::MoveDown() {
	player_.SetDirection(Direction::Down);
	if (map_.IsWalkable(player_.GetY()+1, player_.GetX())) {
		player_.SetY(player_.GetY()+1);
	}
}

void PlayerController::MoveLeft() {
	player_.SetDirection(Direction::Left);
	if (map_.IsWalkable(player_.GetY(), player_.GetX()-1)) {
		player_.SetX(player_.GetX()-1);
	}
}

void PlayerController::MoveRight() {
	player_.SetDirection(Direction::Right);
	if (map_.IsWalkable(player_.GetY(), player_.GetX()+1)) {
		player_.SetX(player_.GetX()+1);
	}
}

std::string PlayerController::PrintItems() {
    std::string result;
    for (const auto& item : player_.GetInventory()) {
        result += item.name + " x" + std::to_string(item.quantity) + "\n";
    }
    return result;
}
