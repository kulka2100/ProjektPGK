#include "stdafx.h"
#include "Game.h"

int main()
{
    Game game(800,600);
    while (game.getWindow().isOpen()) {
        game.update();
        game.render();
    }

    return 0;
}