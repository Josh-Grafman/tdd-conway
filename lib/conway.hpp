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
}