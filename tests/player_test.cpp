#include <gtest/gtest.h>
#include "player.h"

// XP

TEST(PlayerTest, StartsWithZeroXp) {
    Player player("Test");
    EXPECT_EQ(player.GetXp(Skill::Woodcutting), 0);
    EXPECT_EQ(player.GetXp(Skill::Mining), 0);
}

TEST(PlayerTest, GainXpIncreasesXp) {
    Player player("Test");
    player.GainXp(Skill::Woodcutting, 25);
    EXPECT_EQ(player.GetXp(Skill::Woodcutting), 25);
}

TEST(PlayerTest, GainXpAccumulates) {
    Player player("Test");
    player.GainXp(Skill::Woodcutting, 25);
    player.GainXp(Skill::Woodcutting, 25);
    EXPECT_EQ(player.GetXp(Skill::Woodcutting), 50);
}

TEST(PlayerTest, GainXpDoesNotAffectOtherSkills) {
    Player player("Test");
    player.GainXp(Skill::Woodcutting, 25);
    EXPECT_EQ(player.GetXp(Skill::Mining), 0);
}

// Level

TEST(PlayerTest, StartsAtLevelOne) {
    Player player("Test");
    EXPECT_EQ(player.GetLevel(Skill::Woodcutting), 1);
    EXPECT_EQ(player.GetLevel(Skill::Mining), 1);
}

TEST(PlayerTest, LevelUpIncreasesLevel) {
    Player player("Test");
    player.LevelUp(Skill::Woodcutting);
    EXPECT_EQ(player.GetLevel(Skill::Woodcutting), 2);
}

// Position

TEST(PlayerTest, SetAndGetY) {
    Player player("Test");
    player.SetY(5);
    EXPECT_EQ(player.GetY(), 5);
}

TEST(PlayerTest, SetAndGetX) {
    Player player("Test");
    player.SetX(10);
    EXPECT_EQ(player.GetX(), 10);
}

// Direction

TEST(PlayerTest, DefaultDirectionIsRight) {
    Player player("Test");
    EXPECT_EQ(player.GetDirection(), Direction::Right);
}

TEST(PlayerTest, SetAndGetDirection) {
    Player player("Test");
    player.SetDirection(Direction::Up);
    EXPECT_EQ(player.GetDirection(), Direction::Up);
}
