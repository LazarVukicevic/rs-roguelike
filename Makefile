CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses

SRCS = main.cpp game.cpp player.cpp player_controller.cpp map.cpp
TARGET = roguelike

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
