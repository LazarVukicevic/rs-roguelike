#include "player_controller.h"

PlayerController::PlayerController(Player& player, Map& map) : player_(player), map_(map) { }

bool PlayerController::IsTree() {
	return 
		map_.GetAdjacentTile(player_.GetY(), player_.GetX(), player_.GetDirection()) == TileType::kTree;
}

State PlayerController::ChopTree() {
	// if(!IsTree()) {
	// 	return State::kIsNotTree;
	// }
	if (!player_.GetInventory().AddItem({"Logs", 1})) {
		return State::kInventoryFullLogs;
	}
    player_.GainXp(Skill::Woodcutting, 25);
	return State::kSuccessChopTree;
}

State PlayerController::MineRock() {
	if (!player_.GetInventory().AddItem({"Copper Ore", 1})) {
		return State::kInventoryFullCopperOre;
	}
	player_.GainXp(Skill::Mining, 18);
	return State::kSuccessMineRock;
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

State PlayerController::Interact() {
	TileType target = map_.GetAdjacentTile(player_.GetY(), player_.GetX(), player_.GetDirection());

	switch(target) {
		case TileType::kTree: 
			return ChopTree();
		case TileType::kRock: 
			return MineRock();
		default:
			return State::kNothingToInteract;
	}
}