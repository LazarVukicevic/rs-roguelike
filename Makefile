CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc
LDFLAGS = -lncurses

SRCS = src/main.cpp src/game.cpp src/player.cpp src/player_controller.cpp src/map.cpp
TARGET = roguelike

TEST_SRCS = src/player.cpp src/map.cpp src/player_controller.cpp
TEST_OBJS = tests/player_test.cpp tests/map_test.cpp
TEST_TARGET = run_tests
TEST_FLAGS = -lgtest -lgtest_main -pthread

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRCS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) $(TEST_OBJS) $(TEST_FLAGS) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
