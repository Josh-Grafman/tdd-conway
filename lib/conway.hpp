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
            LifeBoard(int size) { setSize(size); };

            void setSize(int size) {
                if(size >= 3)
                    this->size = size;
            }
            int getSize() { return size; }
        private:
            int size;
            std::vector<std::vector<CellState>> grid;
            std::vector<std::vector<CellState>> gridBuff; //store states that will be rendered on next cycle
    };
}