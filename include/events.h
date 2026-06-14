#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <variant>


struct LevelUpEvent {
    std::string skill_name;
    int level;
};

using GameEvent = std::variant<LevelUpEvent>;

#endif