#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>

#include "player.h"

static void finish(int sig);

enum class Mode {
	Normal,
	Command
};



std::string command;
std::string message;
int playerY=-1;
int playerX=-1;
Direction playerDirection = Direction::Right;
std::vector<std::string> map;

std::vector<std::string> loadMap(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Failed to open map file");
	}

	std::vector<std::string> map;
	std::string line;

	while (std::getline(file, line)) {
		if(!line.empty()) {
			map.push_back(line);
		}
	}
	return map;
}

char ScanAdjacent() {
	if (playerDirection == Direction::Up) {
		return map[playerY-1][playerX];
	}
	else if (playerDirection == Direction::Right) {
		return map[playerY][playerX+1];
	}
	else if (playerDirection == Direction::Down) {
		return map[playerY+1][playerX];
	}
	else if (playerDirection == Direction::Left) {
		return map[playerY][playerX-1];
	}
}

std::string printPlayerDirection() {
	if (playerDirection == Direction::Up) {
		return "UP";
	}
	else if (playerDirection == Direction::Right) {
		return "RIGHT";
	}
	else if (playerDirection == Direction::Down) {
		return "DOWN";
	}
	else {
		return "LEFT";
	}
}

bool isTree() {
	char adjacent = ScanAdjacent();
	return adjacent == 'T';
}

bool chopTree() {
	if (!isTree()) {
		message = "There are no trees nearby to chop down.";
		return false;
	}
	else {
		message = "You chop down the tree.";
		return true;
	}
}



int main(int argc, char *argv[])
{
	
	(void) signal(SIGINT, finish);
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();

	map = loadMap("map.txt");

	bool running = true;

	int rows, cols;
	getmaxyx(stdscr, rows, cols);

	

	Mode mode = Mode::Normal;
	
	Player player("Lazar");

	while(running) {
		clear();

		if (mode == Mode::Command) {
			mvprintw(map.size() + 1, 0, "%s", command.c_str());
			clrtoeol();
		}
		else {
			mvprintw(map.size() + 1, 0, "Press : for command mode, q to quit");
			mvprintw(map.size()+2, 0, "Player Direction: %s", printPlayerDirection().c_str());
			if (message.c_str()) {
				mvprintw(map.size()+3, 0, message.c_str());
				message.clear();
			}
			std::string xp = std::to_string(player.get_xp(Skill::Woodcutting)).c_str();
			mvprintw(map.size()+4, 0, xp.c_str());
			clrtoeol();
		}

		for(int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[y].size(); x++) {
				if (map[y][x] == '@') {
					playerY = y;
					playerX = x;
					map[y][x]=' ';
				}
				mvaddch(y, x, map[y][x]);
			}
		}

		mvaddch(playerY, playerX, '@');

		refresh();

		if (mode == Mode::Normal) {
			int c = getch();

			int nextY = playerY;
			int nextX = playerX;
	
			switch(c) {
				case KEY_UP:
					playerDirection = Direction::Up;
					nextY--;
					break;
				case KEY_DOWN:
					playerDirection = Direction::Down;
					nextY++;
					break;
				case KEY_LEFT:
					playerDirection = Direction::Left;
					nextX--;
					break;
				case KEY_RIGHT:
					playerDirection = Direction::Right;
					nextX++;
					break;
				case 'q':
					running = false;
					break;
				case ':':
					mode = Mode::Command;
					break;
				case 'c':
					if(chopTree()) {
						player.gain_xp(Skill::Woodcutting, 25);
					}
					break;
			}
	
			if (nextY > 0 && nextY < rows-1 && nextX > 0 && nextX < cols-1 && map[nextY][nextX] == ' ') {
				playerY = nextY;
				playerX = nextX;
			}
		}

		if (mode == Mode::Command) {
			int c = getch();

			if (c == 27) { // ESC
				mode = Mode::Normal;
				command.clear();
			}
			else if (c == '\n' || c == KEY_ENTER) {
				if (command == "test") {
					message = "HELLO";
					command.clear();      // stay in command mode
				}
				else if (command == "quit" || command == "q") {
					running = false;
				}
				else {
					message = "Unknown command: " + command;
					command.clear();      // stay in command mode
				}
			}
			else if (c == KEY_BACKSPACE || c == 127 || c == 8) {
				if (!command.empty()) {
					command.pop_back();
				}
			}
			else if (std::isprint(c)) {
				command.push_back(static_cast<char>(c));
			}
	}


	}
	finish(0);
}

static void finish(int sig)
{
	endwin();
	exit(0);
}







