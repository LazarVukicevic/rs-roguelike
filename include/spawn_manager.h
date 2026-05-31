#ifndef SPAWN_MANAGER_H
#define SPAWN_MANAGER_H

#include "map.h"
#include <chrono>

struct PendingRespawn {
    int y;
    int x;
    TileType tile;
    std::chrono::steady_clock::time_point respawn_at;
};


class SpawnManager {
    Map& map_;
    std::vector<PendingRespawn> pending_respawns_;
    public:
        SpawnManager(Map& map);
        void ScheduleRespawn(int y, int x, TileType tile, int delay_seconds);
        void Update();
};

#endif