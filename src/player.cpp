#include "player.h"

Player::Player(std::string player_name) : player_name_(player_name) {
    for (const auto& [skill, data] : kAllSkills) {
        skills_[skill] = data;
        SetTargetXp(skill);
    }
}

std::string Player::GetName() {
    return player_name_;
}

void Player::GainXp(Skill skill, int xp) {
    skills_[skill].xp += xp;
    while (skills_[skill].xp >= skills_[skill].xp_target) {
        LevelUp(skill);
    }
}

void Player::LevelUp(Skill skill) {
    skills_[skill].level++;
    SetTargetXp(skill);
    events_.push_back(LevelUpEvent{skills_[skill].name, skills_[skill].level});
}

int Player::GetXp(Skill skill) {
    return skills_[skill].xp;
}

int Player::GetLevel(Skill skill) {
    return skills_[skill].level;
}

const std::unordered_map<Skill, SkillData>& Player::GetSkills() {
    return skills_;
}

std::vector<std::string> Player::GetSkillNames() {
    std::vector<std::string> names;
    for (const auto& [skill, data] : kAllSkills) {
        names.push_back(data.name);
    }
    return names;
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

std::string Player::PrintInventory() {
    if (inventory_.Size() == 0) {
		return "Inventory is empty.";
	}
    std::string result;
    for (const auto& item : inventory_) {
        result += item.name + " x" + std::to_string(item.quantity) + "\n";
    }
    return result;
}

std::string Player::PrintInventory(int index) {
    if (inventory_.Size() == 0) {
		return "Inventory is empty.";
	}
	std::string result;
	if (inventory_.Size() < (size_t)index) {
        if (inventory_.atIndex(index).stackable) {
            result += inventory_.end()->name + " x" + std::to_string(inventory_.end()->quantity) + "\n";
        }
        result += inventory_.end()->name + "\n";
	} else {
        if (inventory_.atIndex(index).stackable) {
		    result += inventory_.atIndex(index).name + " x" + std::to_string(inventory_.atIndex(index).quantity);
        }
        result += inventory_.atIndex(index).name + "\n";
	}
	return result;
}

void Player::SetTargetXp(Skill skill) {
    int level = skills_[skill].level;
    double sum = 0.0;
    for (int n = 1; n <= level; ++n) {
        sum += std::floor(n + 300.0 * std::pow(2.0, n / 7.0));
    }
    skills_[skill].xp_target = static_cast<int>(std::floor(sum / 4.0));
}

std::vector<GameEvent> Player::DrainEvents() {
    std::vector<GameEvent> drained = std::move(events_);
    events_.clear();
    return drained;
}