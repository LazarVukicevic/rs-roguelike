#include "game.h"

const std::string filename = "map.txt";
const std::string playername = "Lazar";

int main() {
	Game game(playername, filename);
	game.Run();
}






