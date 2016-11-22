
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mainMenu.cpp"
#include "game.cpp"
using namespace std;

int main(int argc, char const** argv)
{
  //sets window size and name

  //while the window is open, continues with game
  bool again = true;
  while (again == true){
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    int width = mode.width;
    int height = mode.height;
    sf::RenderWindow window(mode,"Sudoku");
    while (window.isOpen())
    {
      //activates window for rendering
      window.setActive();
      //creates menu and then game
      mainMenu* m = new mainMenu(window,width,height);
      game *g = new game(m->chooseDifficulty(),m);
      //starts the game and continues until it is over

      g->drawCurrentBoard(0,0,sf::Color::Red,0);
      again = g->play(0,0);
      g->clearMemory();

    }
  }
  exit (EXIT_SUCCESS);
  return 0;
}
