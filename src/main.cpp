
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mainMenu.cpp"
#include "game.cpp"
using namespace std;

int main(int argc, char const** argv)
{
  //sets window size and name, defines replay boolean as true
  bool again = true;
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  int width = mode.width;
  int height = mode.height;
  sf::RenderWindow window(mode,"Sudoku");
  //activates window for rendering
  window.setActive();
  do{
      //creates menu and then game
      mainMenu* m = new mainMenu(window,width,height);
      game *g = new game(m->chooseDifficulty(),m);
      //starts the game and continues until it is over
      g->drawCurrentBoard(0,0,sf::Color::Red,0);
      again = g->play(0,0);
      //deletes game and mainmenu so that new ones can be created if looping again
      delete m;
      delete g;
    } while (again == true);
  //exits game successfully if user pressed quit
  if (again == false){
    exit (EXIT_SUCCESS);
  }
  return 0;
}
