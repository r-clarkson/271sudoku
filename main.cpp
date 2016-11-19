
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mainMenu.cpp"
#include "game.cpp"
using namespace std;

int main(int argc, char const** argv)
{
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  int width = mode.width;
  int height = mode.height;
  sf::RenderWindow window(mode,"Sudoku");
  while (window.isOpen())
  {
    //activate window for rendering
    window.setActive();

    mainMenu* m = new mainMenu(window,width,height);
    game *g = new game(m->chooseDifficulty(),m);

    g->startGame();


  }
  return 0;
}
