#include <gtest/gtest.h>
#include "../lib/conway.hpp"

using namespace conway;

TEST(RulesTests, AliveLessThanTwoNeighborsDies) {
    //Any live cell with fewer than two live neighbours dies
    
    //arrange
    CellState current = ALIVE;

    //act
    for(int liveNeighbors = 0; liveNeighbors <= 1; liveNeighbors++) {
        CellState result = LR.GetNewState(current, liveNeighbors);

        //assert
        EXPECT_EQ(result, DEAD);
    }
}

TEST(RulesTests, AliveTwoToThreeNeighborsLives) {
    //Any live cell with two or three live neighbours lives on to the next generation

    //arrange
    CellState current = ALIVE;
    
    //act
    for (int liveNeighbors = 2; liveNeighbors <= 3; liveNeighbors++) {
        CellState result = LR.GetNewState(current, liveNeighbors);

        //assert
        EXPECT_EQ(result, ALIVE);
    }
}

TEST(RulesTests, AliveMoreThanThreeNeighborsDies) {
    //Any live cell with more than three live neighbours dies

    //arrange
    CellState current = ALIVE;

    //act
    for (int liveNeighbors = 4; liveNeighbors <= 8; liveNeighbors++) {
        CellState result = LR.GetNewState(current, liveNeighbors);

        //assert
        EXPECT_EQ(result, DEAD);
    }
}

TEST(RulesTests, DeadThreeNeighborsLives) {
    //Any dead cell with exactly three live neighbours becomes a live cell

    //arrange
    CellState current = DEAD;

    //act
    for (int liveNeighbors = 0; liveNeighbors <= 8; liveNeighbors++) {
        CellState result = LR.GetNewState(current, liveNeighbors);

        //assert
        if(liveNeighbors == 3)
            EXPECT_EQ(result, ALIVE);
        else
            EXPECT_EQ(result, DEAD);
    }
}

TEST(BoardTests, InitializeSize) {
    //arrange
    int size = 3;
    LifeBoard b(size);
    
    //act/assert
    b.setSize(size);
    EXPECT_EQ(b.getSize(), size);

    //expect minimum board size of 3x3
    b.setSize(-1);
    EXPECT_GE(b.getSize(), 3);

    b.setSize(0);
    EXPECT_GE(b.getSize(), 3);

    b.setSize(2);
    EXPECT_GE(b.getSize(), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}