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

TEST(BoardTests, InitializeGrid) {
    //arrange
    int size = 3;
    LifeBoard b(size);

    //act
    int columns = b.getColumnSize();
    int rows = b.getRowSize();

    //assert
    EXPECT_EQ(columns, size);
    EXPECT_EQ(rows, size);
}

TEST(BoardTests, SetGetCellState) {
    //arrange
    int size = 3;
    int x = 1, y = 1;
    LifeBoard b(size);

    //act
    CellState beforeSet = b.getCellState(x, y);
    b.setCellState(x, y, ALIVE);
    CellState afterSet = b.getCellState(x, y);
    CellState outOfBoundsHigh = b.getCellState(x + 10, y + 10); //segfault if not caught
    CellState outOfBoundsLow = b.getCellState(x - 10, y - 10);

    //assert
    EXPECT_EQ(beforeSet, DEAD);
    EXPECT_EQ(afterSet, ALIVE);
    EXPECT_EQ(outOfBoundsHigh, ERRSTATE);
    EXPECT_EQ(outOfBoundsLow, ERRSTATE);
}

TEST(BoardTests, LiveNeighbors) {
    //arrange
    int size = 3;
    LifeBoard b(size);
    int x = 1, y = 1;
    std::vector<int> numAlive;

    //act
    numAlive.push_back(b.liveNeighbors(x, y));  //0
    b.setCellState(x - 1, y - 1, ALIVE);        //top left
    numAlive.push_back(b.liveNeighbors(x, y));  //1
    b.setCellState(x, y - 1, ALIVE);            //top
    numAlive.push_back(b.liveNeighbors(x, y));  //2
    b.setCellState(x + 1, y - 1, ALIVE);        //top right
    numAlive.push_back(b.liveNeighbors(x, y));  //3
    b.setCellState(x - 1, y, ALIVE);            //left
    numAlive.push_back(b.liveNeighbors(x, y));  //4
    b.setCellState(x, y, ALIVE);                //center (me)
    numAlive.push_back(b.liveNeighbors(x, y));  //4
    b.setCellState(x + 1, y, ALIVE);            //right
    numAlive.push_back(b.liveNeighbors(x, y));  //5
    b.setCellState(x - 1, y + 1, ALIVE);        //bottom left
    numAlive.push_back(b.liveNeighbors(x, y));  //6
    b.setCellState(x, y + 1, ALIVE);            //bottom
    numAlive.push_back(b.liveNeighbors(x, y));  //7
    b.setCellState(x + 1, y + 1, ALIVE);        //bottom right
    numAlive.push_back(b.liveNeighbors(x, y));  //8

    //assert
    EXPECT_EQ(numAlive[0], 0);
    EXPECT_EQ(numAlive[1], 1);
    EXPECT_EQ(numAlive[2], 2);
    EXPECT_EQ(numAlive[3], 3);
    EXPECT_EQ(numAlive[4], 4);
    EXPECT_EQ(numAlive[5], 4);
    EXPECT_EQ(numAlive[6], 5);
    EXPECT_EQ(numAlive[7], 6);
    EXPECT_EQ(numAlive[8], 7);
    EXPECT_EQ(numAlive[9], 8);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}