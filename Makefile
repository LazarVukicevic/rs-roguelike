CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc
LDFLAGS = -lncurses

SRCS = src/main.cpp src/game.cpp src/player.cpp src/player_controller.cpp src/map.cpp
TARGET = roguelike

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
