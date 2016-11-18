
#include <stdio.h>
#include <iostream>
#include "mainMenu.cpp"
using namespace std;

int main(int argc, char const** argv)
{
  mainMenu *m = new mainMenu();

  game game = m->chooseDifficulty();

  game.generatePuzzle();

  return 0;
}
