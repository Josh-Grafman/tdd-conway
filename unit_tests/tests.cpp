#include <gtest/gtest.h>
#include "../lib/conway.hpp"

using namespace conway;

TEST(RulesTests, AliveLessThanTwoNeighborsDies) {
    //Any live cell with fewer than two live neighbours dies
    
    //arrange
    CellState current = ALIVE;
    int liveNeighbors = 1;

    //act
    CellState result = LR.GetNewState(current, liveNeighbors);

    //assert
    EXPECT_EQ(result, DEAD);
}

TEST(RulesTests, AliveTwoToThreeNeighborsLives) {
    //Any live cell with two or three live neighbours lives on to the next generation

    //arrange
    CellState current = ALIVE;
    int liveNeighbors = 3;
    
    //act
    CellState result = LR.GetNewState(current, liveNeighbors);

    //assert
    EXPECT_EQ(result, ALIVE);
}

TEST(RulesTests, AliveMoreThanThreeNeighborsDies) {
    //Any live cell with more than three live neighbours dies

    //arrange
    CellState current = ALIVE;
    int liveNeighbors = 4;

    //act
    CellState result = LR.GetNewState(current, liveNeighbors);
    
    //assert
    EXPECT_EQ(result, DEAD);
}

TEST(RulesTests, DeadThreeNeighborsLives) {
    //Any dead cell with exactly three live neighbours becomes a live cell

    //arrange
    CellState current = DEAD;
    int liveNeighbors = 3;

    //act
    CellState result = LR.GetNewState(current, liveNeighbors);

    //assert
    EXPECT_EQ(result, ALIVE);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}