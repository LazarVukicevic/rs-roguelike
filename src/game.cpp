#include "game.h"

#include <signal.h>
#include <curses.h>

Game::Game(const std::string& player_name, const std::string& file_name) : 
	player_(player_name), 
	map_(file_name), 
	player_controller_(player_, map_), 
	spawn_manager_(map_) { }

void Game::Run() {
    (void) signal(SIGINT, finish);
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();
    getmaxyx(stdscr, rows_, cols_);

    while(running_) {
        Render();
        ProcessInput();
        Update();
    }
    finish(0);
}

void Game::Update() {
	spawn_manager_.Update();
}

void Game::ProcessInput() {
    int c = getch();

    switch(c) {
				case KEY_UP:
					player_controller_.MoveUp();
					break;
				case KEY_DOWN:
					player_controller_.MoveDown();
					break;
				case KEY_LEFT:
					player_controller_.MoveLeft();
					break;
				case KEY_RIGHT:
					player_controller_.MoveRight();
					break;
				case 'q':
					running_ = false;
					break;
				case 'c':
					if(player_controller_.ChopTree()) {
						// spawn manager should schedule respawn here
						Coordinate coord = GetCoordinate();
						map_.SetTile(coord.y, coord.x, '-');
						spawn_manager_.ScheduleRespawn(coord.y, coord.x, 'T', 5);
                        message_ = "You chop down the tree.";
                    } else {
                        message_ = "There are no trees nearby to chop down.";
                    }
					break;
			}
}

void Game::Render() {
    clear();
    mvprintw(map_.GetHeight() + 1, 0, "Press : for command mode, q to quit");
	mvprintw(map_.GetHeight()+2, 0, "Player Direction: %s", player_.PrintDirection().c_str());
    
    mvprintw(map_.GetHeight()+3, 0, "%s", message_.c_str());
    message_.clear();
    
    std::string xp = std::to_string(player_.GetXp(Skill::Woodcutting)).c_str();
	mvprintw(map_.GetHeight()+4, 0, "%s", xp.c_str()); // demo
    
    clrtoeol();


    for(int y = 0; y < map_.GetHeight(); y++) {
			for (int x = 0; x < map_.GetWidth(y); x++) {
				if (map_.GetTile(y, x) == '@') {
					player_.SetY(y);
                    player_.SetX(x);
					map_.SetTile(y, x, ' ');
				}
				mvaddch(y, x, map_.GetTile(y, x));
			}
		}

		mvaddch(player_.GetY(), player_.GetX(), '@');

		refresh();

}

void Game::finish(int sig)
{
	endwin();
	exit(0);
}

void Game::SetMessage(std::string& newMessage) {
    message_ = newMessage;
}

std::string Game::GetMessage() {
    return message_.c_str();
}

Coordinate Game::GetCoordinate() {
	if (player_.GetDirection() == Direction::Up) {
		return {player_.GetY()-1, player_.GetX()};
	}
	else if (player_.GetDirection() == Direction::Down) {
		return {player_.GetY()+1, player_.GetX()};
	}
	else if (player_.GetDirection() == Direction::Left) {
		return {player_.GetY(), player_.GetX()-1};
	}
	else { // right
		return {player_.GetY(), player_.GetX()+1};
	}
}
