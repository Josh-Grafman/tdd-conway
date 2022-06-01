//declared namespace for this library
namespace conway {

    enum CellState {DEAD, ALIVE};

    class LifeRules {
        public:
            CellState GetNewState(CellState currentState, int liveNeighbors) const {
                CellState result = currentState;
                if(currentState == ALIVE && liveNeighbors < 2)
                    result = DEAD;
                if(currentState == ALIVE && liveNeighbors > 3 )
                    result = DEAD;
                if(currentState == DEAD && liveNeighbors == 3)
                    result = ALIVE;
                return result;
            }
    } const LR; //global constant instance responsible for running rules
}