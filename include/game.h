#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"
#include "player_controller.h"
#include "spawn_manager.h"
#include "coordinate.h"

class Game {
    static constexpr int kViewWidth  = 30;
    static constexpr int kViewHeight = 10;
    Player player_;
    Map map_;
    PlayerController player_controller_;
    SpawnManager spawn_manager_;
    std:: string message_ = "";
    bool running_ = true;
    int rows_, cols_;
    std::vector<std::string> message_list_;
    const size_t kMaxMessages = 5;
    int cam_x_ = 0;
    int cam_y_ = 0;

    public:
        Game(const std::string& player_name, const std::string& file_name);
        void Run();
    private:
        int tab_ = 1;
        void Render();
        void ProcessInput();
        void Update();
        static void finish(int sig);
        void PushMessage(std::chrono::system_clock::time_point, std::string message);
        void DispatchEvents();
        Coordinate GetCoordinate();
        void RenderMap();
        void RenderInventory();
        void RenderSkillsTab();
        void HandleChopTree();
        void HandleMineRock();
        void HandleInteract();
        void InitColours();
        State Interact();



};


#endif