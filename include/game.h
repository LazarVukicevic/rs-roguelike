#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"
#include "player_controller.h"
#include "spawn_manager.h"
#include "coordinate.h"

class Game {
    

    Player player_;
    Map map_;
    PlayerController player_controller_;
    SpawnManager spawn_manager_;
    std:: string message_ = "";
    bool running_ = true;
    int rows_, cols_;

    public:
        Game(const std::string& player_name, const std::string& file_name);
        void Run();
    private:
        void Render();
        void ProcessInput();
        void Update();
        static void finish(int sig);
        void SetMessage(std::string& newMessage);
        std::string GetMessage();
        Coordinate GetCoordinate();



};


#endif