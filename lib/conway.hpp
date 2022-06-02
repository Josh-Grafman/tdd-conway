#include <vector>

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
        private:
            int size;
            std::vector<std::vector<CellState>> grid;
            std::vector<std::vector<CellState>> gridBuff; //store states that will be rendered on next cycle
    };
}