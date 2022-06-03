#include <vector>
#include <iostream>
#include <string>

//declared namespace for this library
namespace conway {

    enum CellState {DEAD, ALIVE, ERRSTATE};

    class LifeRules {
        public:
            CellState GetNewState(CellState currentState, int liveNeighbors) const;
    } const LR; //global constant instance responsible for running rules

    class LifeBoard {
        public:
            LifeBoard(int size);
            ~LifeBoard();

            void setSize(int size);
            int getSize() const;

            int getColumnSize() const;
            int getRowSize() const;   //assume all rows are same length

            CellState getCellState(int x, int y) const;

            void setCellState(int x, int y, CellState state);

            int liveNeighbors(int x, int y) const;

            void renderBoard();

            void updateBoard();

        private:
            int size;
            std::vector<std::vector<CellState>> grid;
    };
}