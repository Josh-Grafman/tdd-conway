#include "conway.hpp"

using namespace conway;

CellState LifeRules::GetNewState(CellState currentState, int liveNeighbors) const {
    CellState result = currentState;

    switch(currentState) {
        case ALIVE:
            if (liveNeighbors < 2 || liveNeighbors > 3)
                result = DEAD;
            break;
        case DEAD:
            if (liveNeighbors == 3)
                result = ALIVE;
            break;
        default:
            break;
    }
    return result;
}

LifeBoard::LifeBoard(int size) {
    setSize(size);

    std::vector<CellState> cv;
    //create vector of CellStates
    for (int i = 0; i < this->size; i++)
        cv.push_back(DEAD);
    //create vector of CellState vectors 
    for (int i = 0; i < this->size; i++)
        grid.push_back(cv);
}

LifeBoard::~LifeBoard() {}

void LifeBoard::setSize(int size) {
    if(size >= 3)
        this->size = size;
}

int LifeBoard::getSize() const { return size; }

int LifeBoard::getColumnSize() const { return this->grid.size(); }

int LifeBoard::getRowSize() const { return this->grid[0].size(); }

CellState LifeBoard::getCellState(int x, int y) const {
    CellState state;
    if(-1 < x && x < size && -1 < y && y < size)    //avoid segfault
        state = grid[x][y];
    else
        state = ERRSTATE; //read nonexistent cell
    return state;
}

void LifeBoard::setCellState(int x, int y, CellState state) { grid[x][y] = state; }

int LifeBoard::liveNeighbors(int x, int y) const {
    int nAlive = 0;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (getCellState((x + j + size) % size, (y + i + size) % size) == ALIVE && !(i == 0 && j == 0)) //skip ourself
                nAlive++;
    return nAlive;
}

void LifeBoard::renderBoard() {
    std::string printout;
                
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            std::string symbol = ".";
            if (getCellState(x, y) == ALIVE)
                symbol = "#";
            printout += symbol + ' ';
        }
        printout += '\n';
    }
    printout += "\n\n";
    std::cout << printout;
}

void LifeBoard::updateBoard() {
    std::vector<std::vector<CellState>> newGrid;    //contains cellstates post rule application

    for (int x = 0; x < size; x++) {
        std::vector<CellState> row;
        for (int y = 0; y < size; y++) {
            row.push_back(LR.GetNewState(getCellState(x, y), liveNeighbors(x, y)));
        }
        newGrid.push_back(row);
    }

    this->grid = newGrid;
}