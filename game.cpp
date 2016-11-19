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
  game(char d, mainMenu *m){
    bool gameOver = false;
    difficulty = d;
    menu = m;
  }

  bool startGame();
};

bool game::startGame(){
  puzzleGenerator* p = new puzzleGenerator();
  p->generatePuzzle(1,1);
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
