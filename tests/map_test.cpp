#include <gtest/gtest.h>
#include "map.h"

// #####
// # T #
// #   #
// #####

const std::string TEST_MAP = "tests/test_map.txt";

// Dimensions

TEST(MapTest, GetHeight) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetHeight(), 4);
}

TEST(MapTest, GetWidth) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetWidth(), 5);
}

// GetTile

TEST(MapTest, GetTileWall) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetTile(0, 0), '#');
}

TEST(MapTest, GetTileSpace) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetTile(2, 2), ' ');
}

TEST(MapTest, GetTileTree) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetTile(1, 2), 'T');
}

TEST(MapTest, GetTileOutOfBoundsReturnsSentinel) {
    Map map(TEST_MAP);
    EXPECT_EQ(map.GetTile(-1, 0), '`');
    EXPECT_EQ(map.GetTile(0, -1), '`');
    EXPECT_EQ(map.GetTile(99, 0), '`');
}

// SetTile

TEST(MapTest, SetTileChangesTile) {
    Map map(TEST_MAP);
    map.SetTile(2, 2, '#');
    EXPECT_EQ(map.GetTile(2, 2), '#');
}

// IsWalkable

TEST(MapTest, WalkableTileReturnsTrue) {
    Map map(TEST_MAP);
    EXPECT_TRUE(map.IsWalkable(2, 2));
}

TEST(MapTest, WallTileReturnsFalse) {
    Map map(TEST_MAP);
    EXPECT_FALSE(map.IsWalkable(0, 0));
}

TEST(MapTest, BoundaryReturnsFalse) {
    Map map(TEST_MAP);
    EXPECT_FALSE(map.IsWalkable(0, 2));  // top edge
    EXPECT_FALSE(map.IsWalkable(3, 2));  // bottom edge
    EXPECT_FALSE(map.IsWalkable(2, 0));  // left edge
    EXPECT_FALSE(map.IsWalkable(2, 4));  // right edge
}
