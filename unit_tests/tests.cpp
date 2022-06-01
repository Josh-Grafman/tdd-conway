#include <gtest/gtest.h>
#include "../lib/conway.hpp"

using namespace conway;

TEST(RulesTests, AliveLessThanTwoNeighborsDies) {
    //Any live cell with fewer than two live neighbours dies
    
    //arrange
    CellState current = ALIVE;
    int liveNeighborsZero = 0;
    int liveNeighborsOne = 1;

    //act
    CellState resultZero = LR.GetNewState(current, liveNeighborsZero);
    CellState resultOne = LR.GetNewState(current, liveNeighborsOne);

    //assert
    EXPECT_EQ(resultZero, DEAD);
    EXPECT_EQ(resultOne, DEAD);
}

TEST(RulesTests, AliveTwoToThreeNeighborsLives) {
    //Any live cell with two or three live neighbours lives on to the next generation

    //arrange
    CellState current = ALIVE;
    int liveNeighborsTwo = 2;
    int liveNeighborsThree = 3;
    
    //act
    CellState resultTwo = LR.GetNewState(current, liveNeighborsTwo);
    CellState resultThree = LR.GetNewState(current, liveNeighborsThree);

    //assert
    EXPECT_EQ(resultTwo, ALIVE);
    EXPECT_EQ(resultThree, ALIVE);
}

TEST(RulesTests, AliveMoreThanThreeNeighborsDies) {
    //Any live cell with more than three live neighbours dies

    //arrange
    CellState current = ALIVE;
    int liveNeighborsFour = 4;
    int liveNeighborsFive = 5;
    int liveNeighborsSix = 6;
    int liveNeighborsSeven = 7;
    int liveNeighborsEight = 8;

    //act
    CellState resultFour = LR.GetNewState(current, liveNeighborsFour);
    CellState resultFive = LR.GetNewState(current, liveNeighborsFive);
    CellState resultSix = LR.GetNewState(current, liveNeighborsSix);
    CellState resultSeven = LR.GetNewState(current, liveNeighborsSeven);
    CellState resultEight = LR.GetNewState(current, liveNeighborsEight);

    //assert
    EXPECT_EQ(resultFour, DEAD);
    EXPECT_EQ(resultFive, DEAD);
    EXPECT_EQ(resultSix, DEAD);
    EXPECT_EQ(resultSeven, DEAD);
    EXPECT_EQ(resultEight, DEAD);    
}

TEST(RulesTests, DeadThreeNeighborsLives) {
    //Any dead cell with exactly three live neighbours becomes a live cell

    //arrange
    CellState current = DEAD;
    int liveNeighborsZero = 0;
    int liveNeighborsOne = 1;
    int liveNeighborsTwo = 2;
    int liveNeighborsThree = 3;
    int liveNeighborsFour = 4;
    int liveNeighborsFive = 5;
    int liveNeighborsSix = 6;
    int liveNeighborsSeven = 7;
    int liveNeighborsEight = 8;

    //act
    CellState resultZero = LR.GetNewState(current, liveNeighborsZero);
    CellState resultOne = LR.GetNewState(current, liveNeighborsOne);
    CellState resultTwo = LR.GetNewState(current, liveNeighborsTwo);
    CellState resultThree = LR.GetNewState(current, liveNeighborsThree);
    CellState resultFour = LR.GetNewState(current, liveNeighborsFour);
    CellState resultFive = LR.GetNewState(current, liveNeighborsFive);
    CellState resultSix = LR.GetNewState(current, liveNeighborsSix);
    CellState resultSeven = LR.GetNewState(current, liveNeighborsSeven);
    CellState resultEight = LR.GetNewState(current, liveNeighborsEight);

    //assert
    EXPECT_EQ(resultZero, DEAD);
    EXPECT_EQ(resultOne, DEAD);
    EXPECT_EQ(resultTwo, DEAD);
    EXPECT_EQ(resultThree, ALIVE);
    EXPECT_EQ(resultFour, DEAD);
    EXPECT_EQ(resultFive, DEAD);
    EXPECT_EQ(resultSix, DEAD);
    EXPECT_EQ(resultSeven, DEAD);
    EXPECT_EQ(resultEight, DEAD);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}