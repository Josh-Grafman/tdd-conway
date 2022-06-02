#include <vector>

//declared namespace for this library
namespace conway {

    enum CellState {DEAD, ALIVE};

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
            int getSize() { return size; }

            int getColumnSize() { return this->grid.size(); }
            int getRowSize() { return this->grid[0].size(); }   //assume all rows are same length
        private:
            int size;
            std::vector<std::vector<CellState>> grid;
            std::vector<std::vector<CellState>> gridBuff; //store states that will be rendered on next cycle
    };
}