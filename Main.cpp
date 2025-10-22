#include "Game.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(0)));

    Game game;
    game.start_game();

    return 0;
}
