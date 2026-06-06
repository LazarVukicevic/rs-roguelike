#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "direction.h"
#include "inventory.h"

enum class Skill {
    Woodcutting,
    Mining
};

struct SkillData {
    std::string name;
    int level = 1;
    int xp    = 0;
};

inline const std::vector<std::pair<Skill, SkillData>> kAllSkills = {
    {Skill::Woodcutting, {"Woodcutting"}},
    {Skill::Mining,      {"Mining"}},
};

class Player {
    Inventory inventory_;
    std::string player_name_;
    std::unordered_map<Skill, SkillData> skills_;
    int player_y_=-1;
    int player_x_=-1;
    Direction player_direction_ = Direction::Right; // default to right
    public:
        Player(std::string player_name);
        std::string GetName();
        void GainXp(Skill skill, int xp);
        void LevelUp(Skill skill);
        int GetXp(Skill skill);
        int GetLevel(Skill skill);
        std::vector<std::string> GetSkillNames();
        const std::unordered_map<Skill, SkillData>& GetSkills();
        std::string PrintInventory(int index);
        std::string PrintInventory();
        Direction GetDirection();
        std::string PrintDirection();
        void SetDirection(Direction new_direction);
        int GetY();
        int GetX();
        void SetY(int new_y);
        void SetX(int new_x);
        Inventory& GetInventory();

};

#endif // PLAYER_H