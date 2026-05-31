#include "game.h"

#include <locale.h>
#include <signal.h>
#include <curses.h>
#include <format>
#include <iomanip>

Game::Game(const std::string& player_name, const std::string& file_name) : 
	player_(player_name), 
	map_(file_name), 
	player_controller_(player_, map_), 
	spawn_manager_(map_) { }

void Game::Run() {
    (void) signal(SIGINT, finish);
	setlocale(LC_ALL, "");
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();
    getmaxyx(stdscr, rows_, cols_);
	curs_set(0);
	timeout(500);
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
					HandleChopTree();
					break;
				case 'm':
					player_controller_.AddItemToInventory({"Copper ore"+std::to_string(std::rand()), 1}); // testing inventory display
					break;
			}
}

void Game::Render() {
    clear();
    mvprintw(map_.GetHeight() + 1, 0, "Press q to quit");
	mvprintw(map_.GetHeight()+2, 0, "Player Direction: %s", player_.PrintDirection().c_str());
    
	for (int i = 0; (size_t)i < message_list_.size(); i++) {
		mvprintw(map_.GetHeight()+i+3, 0, "- %s -", message_list_[i].c_str());
	}
    
    std::string xp = std::to_string(player_.GetXp(Skill::Woodcutting)).c_str();
	mvprintw(map_.GetHeight()+8, 0, "%s", xp.c_str()); // demo
    
    clrtoeol();

	RenderMap();

	RenderInventory();

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

void Game::PushMessage(std::chrono::system_clock::time_point time, std::string message) {
	std::time_t now_t = std::chrono::system_clock::to_time_t(time);
	std::ostringstream oss;
	oss << std::put_time(std::localtime(&now_t), "[%H:%M:%S] ") << message;
	if (message_list_.size() >= kMaxMessages) {
		message_list_.erase(message_list_.begin());
	}
	message_list_.push_back(oss.str());
}

void Game::RenderMap() {
	for(int y = 0; y < map_.GetHeight(); y++) {
			for (int x = 0; x < map_.GetWidth(y); x++) {
				if (map_.GetTile(y, x) == TileType::kPlayerStart) {
					player_.SetY(y);
                    player_.SetX(x);
					map_.SetTile(y, x, TileType::kFloor);
				}
				std::wstring glyph = TileGlyph(map_.GetTile(y, x));
				mvaddnwstr(y, x, glyph.c_str(), glyph.size());
			}
		}

	mvaddnwstr(player_.GetY(), player_.GetX(), L"@", 1);
}

void Game::RenderInventory() { // render after map
	for(int i = 0; (size_t)i < player_.GetInventory().Size(); i++) {
		mvprintw(i, map_.GetWidth()+35, "| %s", player_controller_.PrintInventory(i).c_str());
	}
}

void Game::HandleChopTree() {
	State ch = player_controller_.ChopTree();
	if(ch == State::kSuccess) {
		Coordinate coord = GetCoordinate();
		map_.SetTile(coord.y, coord.x, TileType::kTreeStump);
		spawn_manager_.ScheduleRespawn(coord.y, coord.x, TileType::kTree, 5);
		PushMessage(std::chrono::system_clock::now(), "You chop down the tree.");
	} else if (ch == State::kIsNotTree){
		PushMessage(std::chrono::system_clock::now(), "There are no trees nearby to chop down.");
	} else {
		PushMessage(std::chrono::system_clock::now(), "Your inventory is too full to chop this tree.");
	}
}