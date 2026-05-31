#include "spawn_manager.h"

SpawnManager::SpawnManager(Map& map) : map_(map) {}


void SpawnManager::ScheduleRespawn(int y, int x, TileType tile, int delay_seconds) {
    auto respawn_at = std::chrono::steady_clock::now() + std::chrono::seconds(delay_seconds);
    pending_respawns_.push_back({y, x, tile, respawn_at});
}

void SpawnManager::Update() {
    auto now = std::chrono::steady_clock::now();
    auto it = pending_respawns_.begin();
    while (it != pending_respawns_.end()) {
        if (now >= it->respawn_at) {
            map_.SetTile(it->y, it->x, it->tile);
            it = pending_respawns_.erase(it);
        } else {
            ++it;
        }
    }
}