#include "game.h"
#include "tile.h"

#include <locale.h>
#include <signal.h>
#include <curses.h>
#include <format>
#include <iomanip>
#include <algorithm>

Game::Game(const std::string& player_name, const std::string& file_name) : 
	player_(player_name), 
	map_(file_name), 
	player_controller_(player_, map_), 
	spawn_manager_(map_) { }

void Game::Run() {
    (void) signal(SIGINT, finish);
	setlocale(LC_ALL, "");
	(void) initscr();
    start_color();
	InitColours();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();
    getmaxyx(stdscr, rows_, cols_);
	curs_set(0);
	timeout(500);
	Coordinate start = map_.FindPlayerStart();
	player_.SetY(start.y);
	player_.SetX(start.x);
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
				case '1':
					tab_ = 1;
					// inv tab
					break;
				case '2':
					tab_ = 2;
					// skills tab
					break;
			}
}

void Game::Render() {
    erase();
    mvprintw(kViewHeight + 1, 0, "Press q to quit");
	mvprintw(kViewHeight+2, 0, "Player Direction: %s", player_.PrintDirection().c_str());
    
	for (int i = 0; (size_t)i < message_list_.size(); i++) {
		mvprintw(kViewHeight+i+3, 0, "- %s -", message_list_[i].c_str());
	}
    
    clrtoeol();
	RenderMap();
	switch(tab_) {
		case 1:
			RenderInventory();
			break;
		case 2:
			RenderSkillsTab();
			break;
		default:
			RenderInventory();
			break;
	}
	refresh();

}

void Game::finish(int sig)
{
	endwin();
	exit(0);
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
	cam_x_ = std::clamp(player_.GetX() - kViewWidth/2, 0, std::max(0, map_.GetWidth() - kViewWidth));
    cam_y_ = std::clamp(player_.GetY() - kViewHeight/2, 0, std::max(0, map_.GetHeight() - kViewHeight));
	for (int y = cam_y_; y < cam_y_ + kViewHeight; y++) {
		for (int x = cam_x_; x < cam_x_ + kViewWidth; x++) {
			TileType tile = map_.GetTile(y, x);
			if (tile == TileType::kInvalid) continue;
			std::wstring glyph = TileGlyph(tile);
			int pair = TileColorPair(tile);
			attron(COLOR_PAIR(pair));
			mvaddnwstr(y - cam_y_, x - cam_x_, glyph.c_str(), glyph.size());
			attroff(COLOR_PAIR(pair));
		}
	}
	attron(COLOR_PAIR(static_cast<int>(TileColorPairIndex::kPlayer)));
	mvaddnwstr(player_.GetY()-cam_y_, player_.GetX()-cam_x_, L"@", 1);
	attroff(COLOR_PAIR(static_cast<int>(TileColorPairIndex::kPlayer)));
}

void Game::RenderInventory() { // render after map
	for(int i = 0; (size_t)i < player_.GetInventory().Size(); i++) {
		mvprintw(i, kViewWidth+35, "| %s", player_.PrintInventory(i).c_str());
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

void Game::InitColours() {
	init_pair(static_cast<int>(TileColorPairIndex::kFloor),     COLOR_WHITE,   COLOR_BLACK); // text colour, background colour
    init_pair(static_cast<int>(TileColorPairIndex::kWall),      COLOR_WHITE,   COLOR_WHITE);
    init_pair(static_cast<int>(TileColorPairIndex::kTree),      COLOR_GREEN,   COLOR_BLACK);
    init_pair(static_cast<int>(TileColorPairIndex::kTreeStump), COLOR_YELLOW,  COLOR_BLACK);
    init_pair(static_cast<int>(TileColorPairIndex::kPlayer),    COLOR_WHITE,   COLOR_BLACK);
    init_pair(static_cast<int>(TileColorPairIndex::kDefault),   COLOR_WHITE,   COLOR_BLACK);
}

void Game::RenderSkillsTab() {
	const auto& skills = player_.GetSkills();
	int row = 0;
	for (const auto& [skill, data] : kAllSkills) {
		const SkillData& s = skills.at(skill);
		mvprintw(row++, kViewWidth+35, "| %-12s Lvl: %d  XP: %d", s.name.c_str(), s.level, s.xp);
	}
}