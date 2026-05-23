#include "game.h"

const std::string filepath = "assets/map.txt";
const std::string playername = "Lazar";

int main() {
	Game game(playername, filepath);
	game.Run();
}






