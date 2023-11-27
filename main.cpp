#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <fstream>

int main()
{
    Game g("config.txt");
    g.run();
    return 0;
}
