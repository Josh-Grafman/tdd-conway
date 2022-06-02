#include "../lib/conway.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

    int bSize = 15;
    conway::LifeBoard b(bSize);

    b.setCellState(0, 2, conway::ALIVE);
    b.setCellState(1, 0, conway::ALIVE);
    b.setCellState(2, 1, conway::ALIVE);
    b.setCellState(2, 2, conway::ALIVE);
    b.setCellState(1, 2, conway::ALIVE);

    int clock = 0;
    while(clock < 10000000000) {
        cout << '\n';
        b.renderBoard();
        b.updateBoard();
        usleep(280000);
    }

    return 0;
}