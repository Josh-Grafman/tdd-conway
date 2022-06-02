#include <vector>
#include <iostream>

//declared namespace for this library
namespace conway {

    enum CellState {DEAD, ALIVE, ERRSTATE};

    class LifeRules {
        public:
            CellState GetNewState(CellState currentState, int liveNeighbors) const {
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
    } const LR; //global constant instance responsible for running rules

    class LifeBoard {
        public:
            LifeBoard(int size) {
                setSize(size);

                std::vector<CellState> cv;
                //create vector of CellStates
                for (int i = 0; i < this->size; i++)
                    cv.push_back(DEAD);
                //create vector of CellState vectors 
                for (int i = 0; i < this->size; i++)
                    grid.push_back(cv);
            }
            LifeBoard(std::vector<std::vector<CellState>> grid) {
                this->grid = grid;
            }
            ~LifeBoard() {}

            void setSize(int size) {
                if(size >= 3)
                    this->size = size;
            }
            int getSize() const { return size; }

            int getColumnSize() const { return this->grid.size(); }
            int getRowSize() const { return this->grid[0].size(); }   //assume all rows are same length

            CellState getCellState(int x, int y) const {
                CellState state;
                if(-1 < x && x < size && -1 < y && y < size)    //avoid segfault
                    state = grid[x][y];
                else
                    state = ERRSTATE; //read nonexistent cell
                return state;
            }

            void setCellState(int x, int y, CellState state) { grid[x][y] = state; }

            int liveNeighbors(int x, int y) const {
                int nAlive = 0;

                for (int i = -1; i <= 1; i++)
                    for (int j = -1; j <= 1; j++)
                        if (getCellState((x + j + size) % size, (y + i + size) % size) == ALIVE && !(i == 0 && j == 0)) //skip ourself
                            nAlive++;
                return nAlive;
            }

            void renderBoard() {
                
                for (int y = 0; y < size; y++) {
                    for (int x = 0; x < size; x++) {
                        char symbol = '.';
                        if (getCellState(x, y) == ALIVE)
                            symbol = '#';
                        std::cout << symbol << ' ';
                    }
                    std::cout << '\n';
                }
            }

            void updateBoard() {
                std::vector<std::vector<CellState>> newGrid;    //contains cellstates post rule application

                for (int y = 0; y < size; y++) {
                    std::vector<CellState> row;
                    for (int x = 0; x < size; x++) {
                        row.push_back(LR.GetNewState(getCellState(x, y), liveNeighbors(x, y)));
                    }
                    newGrid.push_back(row);
                }

                this->grid = newGrid;
            }

        private:
            int size;
            std::vector<std::vector<CellState>> grid;
    };
}