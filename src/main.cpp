
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mainMenu.cpp"
#include "game.cpp"
using namespace std;

int main(int argc, char const** argv)
{
  //sets window size and name
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  int width = mode.width;
  int height = mode.height;
  sf::RenderWindow window(mode,"Sudoku");
  //while the window is open, continues with game
  while (window.isOpen())
  {
    //activates window for rendering
    window.setActive();
    //creates menu and then game
    mainMenu* m = new mainMenu(window,width,height);
    game *g = new game(m->chooseDifficulty(),m);
    //starts the game and continues until it is over
    g->startGame();

    //add an end screen or option to go again?

  }
  return 0;
}
