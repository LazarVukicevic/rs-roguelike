#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "direction.h"

enum class Skill {
    Woodcutting,
    Mining
};




class Player {
    std::string player_name_;
    std::unordered_map<Skill, int> skill_xp_map_ = {
        {Skill::Woodcutting, 0},
        {Skill::Mining, 0}
    };
    std::unordered_map<Skill, int> skill_level_map_ = {
        {Skill::Woodcutting, 1},
        {Skill::Mining, 1}
    };
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
        Direction GetDirection();
        std::string PrintDirection();
        void SetDirection(Direction new_direction);
        int GetY();
        int GetX();
        void SetY(int new_y);
        void SetX(int new_x);

};

#endif // PLAYER_H