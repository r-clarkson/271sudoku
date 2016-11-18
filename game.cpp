#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.cpp"
using namespace std;

class game{
public:
  char difficulty;
  game(sf::RenderWindow &window, char d){
    difficulty = d;
  }

  bool generateBoard(tile **puzzle);
  bool generatePuzzle();
  void runGame();
};

bool game::generateBoard(tile **puzzle){
  return true;
}

bool game::generatePuzzle(){
  cout << difficulty << endl;
  return true;
}
