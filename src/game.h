#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"
#include "player_controller.h"

class Game {
    

    Player player_;
    Map map_;
    PlayerController controller_;
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


};


#endif