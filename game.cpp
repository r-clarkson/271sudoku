#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.cpp"
#include "puzzleGenerator.cpp"

using namespace std;

class game{
public:
  char difficulty;
  sf::RenderWindow *window;
  mainMenu *menu;
  bool gameOver;
  puzzleGenerator* p;
  game(char d, mainMenu *m){
    bool gameOver = false;
    difficulty = d;
    menu = m;
    p = new puzzleGenerator();
    p->generatePuzzle(1,1);
  }

  bool startGame();
};
/**
* Clears and resets background, then continues in loop of:
* 1: Display current puzzle (uses display puzzle function)
* 2: Get user input (uses user input function)
* 3: Update current puzzle (uses update puzzle function)
*/
bool game::startGame(){

  p->printPuzzle();
  window = menu->getWindow();
  
  //reset background
  sf::Texture texture;
  if(!texture.loadFromFile("background.jpg")){
    cout << "Background error" << endl;
  }
  sf::Sprite background(texture);
  window->draw(background);
  window->display();

  while (gameOver==false){

    //Display current puzzle

    // Event processing, get user input
    sf::Event event;
    while (window->waitEvent(event))
    {
      // Request for closing the window
      if (event.type == sf::Event::Closed){
        window->close();
        return false;
      }
    }
  }
}
