#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>

enum class Skill {
    Woodcutting,
    Mining
};

enum class Direction {
	Up,
	Right,
	Left,
	Down
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
        std::string get_player_name();
        void gain_xp(Skill skill, int xp);
        void level_up(Skill skill);
        int get_xp(Skill skill);
        int get_level(Skill skill);
        Direction get_player_direction();
        std::string PrintPlayerDirection();
        void set_player_direction(Direction new_direction);
        int get_player_y();
        int get_player_x();
        void set_player_y(int new_y);
        void set_player_x(int new_x);

};

#endif // PLAYER_H