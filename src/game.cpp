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
    window = menu->getWindow();
  }

  bool startGame();
  void drawBoard();
  void drawPuzzle();
  void play();
};
/**
* Clears and resets background, then continues in loop of:
* 1: Display current puzzle (uses display puzzle function)
* 2: Get user input (uses user input function)
* 3: Update current puzzle (uses update puzzle function)
*/
bool game::startGame(){

  p->printPuzzle();
  drawBoard();
  //reset background

  while (gameOver==false){

    //Display current puzzle; fill board

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
  return true;
}

void game::drawBoard(){
  sf::Texture texture;
  if(!texture.loadFromFile("resources/background.jpg")){
    cout << "Background error" << endl;
  }
  sf::Sprite background(texture);
  window->draw(background);

  //make blank board
  sf::RectangleShape board;
  board.setSize(sf::Vector2f(1400,1200));
  board.setFillColor(sf::Color::White);
  board.setOutlineColor(sf::Color::Black);
  board.setOutlineThickness(10);
  sf::FloatRect temp = board.getLocalBounds();
  board.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  board.setPosition(sf::Vector2f(menu->getWidth()/2.1f,menu->getHeight()/2.5f));
  window->draw(board);
  //vertical lines
  sf::RectangleShape verticalLines[8];
  int spacer = menu->getWidth()/2.1f;
  for (int i = 0; i < 8; i++){
    verticalLines[i] = sf::RectangleShape(sf::Vector2f(2,1200));
    verticalLines[i].setFillColor(sf::Color::Black);
    verticalLines[i].setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
    verticalLines[i].setPosition(sf::Vector2f(spacer+155.5,menu->getHeight()/2.5f));
    if (i == 2 || i == 5){
      verticalLines[i].setOutlineColor(sf::Color::Black);
      verticalLines[i].setOutlineThickness(5);
    }
    window->draw(verticalLines[i]);
    spacer += 155.5;
  }
  //horizontal lines
  sf::RectangleShape horizontalLines[8];
  spacer = menu->getHeight()/2.5f;
  for (int i = 0; i < 8; i++){
    horizontalLines[i] = sf::RectangleShape(sf::Vector2f(1400,2));
    horizontalLines[i].setFillColor(sf::Color::Black);
    horizontalLines[i].setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
    horizontalLines[i].setPosition(sf::Vector2f(menu->getWidth()/2.1f,spacer+133.3));
    if (i == 2 || i == 5){
      horizontalLines[i].setOutlineColor(sf::Color::Black);
      horizontalLines[i].setOutlineThickness(5);
    }
    window->draw(horizontalLines[i]);
    spacer += 133.3;
  }

  sf::Font font;
  if (!font.loadFromFile("resources/CourierNew.ttf")){
    cout << "font error" << endl;
    window->close();
  }
  sf::Text **tiles;
  tiles = new sf::Text*[9];
  for (int i = 0; i < 9; ++i){
    tiles[i] = new sf::Text[9];
  }
  sf::FloatRect pos = board.getLocalBounds();
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j){
      int width = 155.5*(i+1);
      int height = 133.3*(i+1);
      int positionWidth = pos.left + (155.5*(i+1));
      int positionHeight = pos.top - (133.3*(j+1));
      tiles[i][j] = sf::Text("0",font);
      tiles[i][j].setCharacterSize(50);
      tiles[i][j].setFillColor(sf::Color::Black);
      tiles[i][j].setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
      tiles[i][j].setPosition(sf::Vector2f(positionWidth,positionHeight));
      window->draw(tiles[i][j]);
    }
  }
  window->display();
}
