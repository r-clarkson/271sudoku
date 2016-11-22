#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.cpp"
#include "puzzleGenerator.cpp"
#include "game.h"

using namespace std;

/**
* Clears and resets background, then continues in loop of:
* 1: Display current puzzle (uses display puzzle function)
* 2: Get user input (uses user input function)
* 3: Update current puzzle (uses update puzzle function)
*/

sf::Text game::enterValue(int row, int col, int val){
  sf::Font font;
  if (!font.loadFromFile("resources/CourierNew.ttf")){
    cout << "font error" << endl;
    window->close();
  }
  if (val == 10){
    for (int i = 0; i < 9; i ++){
      for (int j = 0; j < 9; j++){
        if (tiles[i][j].getString() == ""){
          tiles[i][j].setFont(font);
          tiles[i][j].setString(to_string(p->getVal(i,j)));
          tiles[i][j].setFillColor(sf::Color::Red);
          window->draw(tiles[i][j]);
          return tiles[i][j];
        }
      }
    }
  }
  else{

    tiles[row][col].setFont(font);
    tiles[row][col].setFillColor(sf::Color::Black);
    tiles[row][col].setOutlineColor(sf::Color::Black);
    tiles[row][col].setOutlineThickness(2);
    tiles[row][col].setString(to_string(val));
    window->draw(tiles[row][col]);
    Index temp(row,col);
    if (val == p->getVal(row,col)){
      correct.push_back(temp);
      correct[numCorrect].row = row;
      correct[numCorrect].col = col;
      numCorrect++;
    }
    else{
      wrong.push_back(temp);
      wrong[numWrong].row = row;
      wrong[numWrong].col = col;
      numWrong++;
    }

    return tiles[row][col];
  }
}

bool game::valueCorrect(int row, int col){
  if (tiles[row][col].getString() == to_string(p->getVal(row,col))){
    return true;
  }
  return false;
}

void game::drawBoardBackground(){
  sf::Font font;
  if (!font.loadFromFile("resources/CourierNew.ttf")){
    cout << "font error" << endl;
    window->close();
  }
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
    verticalLines[i] = sf::RectangleShape(sf::Vector2f(4,1200));
    verticalLines[i].setFillColor(sf::Color::Black);
    verticalLines[i].setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
    verticalLines[i].setPosition(sf::Vector2f(spacer+155.5,menu->getHeight()/2.5f));
    if (i == 2 || i == 5){
      verticalLines[i].setOutlineColor(sf::Color::Black);
      verticalLines[i].setOutlineThickness(6);
    }
    window->draw(verticalLines[i]);
    spacer += 155.5;
  }
  //horizontal lines
  sf::RectangleShape horizontalLines[8];
  spacer = menu->getHeight()/2.5f;
  for (int i = 0; i < 8; i++){
    horizontalLines[i] = sf::RectangleShape(sf::Vector2f(1400,4));
    horizontalLines[i].setFillColor(sf::Color::Black);
    horizontalLines[i].setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
    horizontalLines[i].setPosition(sf::Vector2f(menu->getWidth()/2.1f,spacer+133.3));
    if (i == 2 || i == 5){
      horizontalLines[i].setOutlineColor(sf::Color::Black);
      horizontalLines[i].setOutlineThickness(6);
    }
    window->draw(horizontalLines[i]);
    spacer += 133.3;
  }


}

sf::Text** game::drawInitialBoard(){
  drawBoardBackground();
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
  for (int i = 0; i < 9; i ++){
    for (int j = 0; j < 9; j++){
      tiles[i][j] = sf::Text("A",font);
    }
    //hint and solve buttons
    sf::RectangleShape hintButton;
    hintButton.setSize(sf::Vector2f(400,150));
    hintButton.setPosition(sf::Vector2f(700,1300));
    hintButton.setFillColor(sf::Color::Black);
    hintButton.setOutlineColor(sf::Color::White);
    hintButton.setOutlineThickness(5);
    window->draw(hintButton);
    hintText.setString("Hint");
    hintText.setFont(font);
    hintText.setCharacterSize(100);
    hintText.setFillColor(sf::Color::White);
    hintText.setPosition(775,1300);
    //hintText.setOrigin(hintButton.getOrigin()+25);
    window->draw(hintText);

    sf::RectangleShape solveButton;
    solveButton.setSize(sf::Vector2f(400,150));
    solveButton.setPosition(sf::Vector2f(1325,1300));
    solveButton.setFillColor(sf::Color::Black);
    solveButton.setOutlineColor(sf::Color::White);
    solveButton.setOutlineThickness(5);
    window->draw(solveButton);
    solveText.setString("Solve");
    solveText.setFont(font);
    solveText.setCharacterSize(100);
    solveText.setFillColor(sf::Color::White);
    solveText.setPosition(1375,1300);
    //solveText.setOrigin(solveButton.getOrigin());
    window->draw(solveText);
  }


  switch(difficulty){

    case 'e':
    blankSpaces = rand() % 7 + 34;
    break;
    case 'm':
    blankSpaces = rand() % 7 + 43;
    break;
    case 'h':
    blankSpaces = rand() % 7 + 50;
    break;
  }
  int count = 0;
  while (count != blankSpaces){
    int random1 = rand() % 9;
    int random2 = rand() % 9;
    if (tiles[random1][random2].getString() != ""){
      tiles[random1][random2].setString("");
      count++;
    }
  }

  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j){
      int positionWidth = (155.5*(i+1));
      int positionHeight = (133.3*(j+1));
      tiles[i][j].setCharacterSize(50);
      tiles[i][j].setOrigin( width/100.0f, height/7.0f);
      tiles[i][j].setPosition(sf::Vector2f(positionWidth+450,positionHeight));

      if (tiles[i][j].getString() == "A"){
        tiles[i][j].setString(to_string(p->getVal(i,j)));
        tiles[i][j].setFillColor(sf::Color::Black);
      }
      window->draw(tiles[i][j]);
    }
  }

  window->display();
  return tiles;
}

void game::drawCurrentBoard(int row, int col, sf::Color color, int val){
  window->clear(sf::Color::Black);
  drawBoardBackground();
  window->display();
  if (val!=0){
    enterValue(row,col,val);
  }
  window->draw(setSpot(row,col,color));
  window->display();
}

sf::RectangleShape game::setSpot(int row, int col, sf::Color color){
  sf::RectangleShape spot(sf::Vector2f(100,100));
  spot.setPosition(tiles[row][col].getPosition());
  spot.setOrigin(width/100.0f+40, (height/7.0f)+10);
  spot.setOutlineColor(color);
  spot.setFillColor(sf::Color::Transparent);
  spot.setOutlineThickness(3);
  return spot;
}

bool game::play(int currentRow, int currentCol){

  sf::Event event;
  while (window->waitEvent(event)){
    if(event.type == sf::Event::Closed){
      window->close();
    }
    else if (event.type == sf::Event::MouseButtonPressed){
      if (hintText.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        drawCurrentBoard(currentRow,currentCol,sf::Color::Red,10);
        play(currentRow,currentCol);
      }
      else if (solveText.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return endScreen();
      }

    }
    else if (event.type == sf::Event::KeyPressed){
      drawCurrentBoard(currentRow,currentCol,sf::Color::White,0);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if (currentRow!=0){
          drawCurrentBoard(currentRow-1,currentCol,sf::Color::Red,0);
          play(currentRow-1,currentCol);
        }
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (currentRow!=8){
          drawCurrentBoard(currentRow+1,currentCol,sf::Color::Red,0);
          play(currentRow+1,currentCol);
        }
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if (currentCol!=0){
          drawCurrentBoard(currentRow,currentCol-1,sf::Color::Red,0);
          play(currentRow,currentCol-1);
        }
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (currentCol!=8){
          drawCurrentBoard(currentRow,currentCol+1,sf::Color::Red,0);
          play(currentRow,currentCol+1);
        }
      }
      else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
          numberPressed = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
          numberPressed = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
          numberPressed = 3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
          numberPressed = 4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
          numberPressed = 5;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
          numberPressed = 6;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
          numberPressed = 7;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
          numberPressed = 8;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
          numberPressed = 9;
        }
        drawCurrentBoard(currentRow,currentCol,sf::Color::Red,numberPressed);
        play(currentRow,currentCol);
      }
    }
  }
}
bool game::endScreen(){
  drawBoardBackground();
  sf::Font font;
  if (!font.loadFromFile("resources/CourierNew.ttf")){
    cout << "font error" << endl;
    window->close();
  }
  for (int i = 0; i < 9; i++){
    for (int j =0; j<9; j++){
      tiles[i][j].setFont(font);
      tiles[i][j].setFillColor(sf::Color::Black);
      if (tiles[i][j].getString() == ""){
        tiles[i][j].setString(to_string(p->getVal(i,j)));
        tiles[i][j].setFillColor(sf::Color::Red);
      }
      for (int r = 0; r < correct.size(); r++){
        if (correct[r].row == i && correct[r].col == j){
          tiles[i][j].setFillColor(sf::Color::Green);
        }
      }
      for (int q = 0; q < wrong.size(); q++){
        if (wrong[q].row == i && wrong[q].col == j){
          tiles[i][j].setString(to_string(p->getVal(i,j)));
          tiles[i][j].setFillColor(sf::Color::Red);
        }

      }
      window->draw(tiles[i][j]);
    }
  }
  sf::RectangleShape replayButton;
  sf::Text replayText("Replay",font);

  replayButton.setSize(sf::Vector2f(250,100));
  replayButton.setPosition(sf::Vector2f(100,200));

  replayButton.setOutlineColor(sf::Color::White);
  replayButton.setFillColor(sf::Color::Black);
  replayButton.setOutlineThickness(5);

  replayText.setFillColor(sf::Color::White);
  replayText.setCharacterSize(50);
  replayText.setPosition(130,210);
  window->draw(replayButton);
  window->draw(replayText);

  sf::RectangleShape exitButton;
  sf::Text exitText("Quit",font);

  exitButton.setSize(sf::Vector2f(250,100));
  exitButton.setPosition(sf::Vector2f(100,400));

  exitButton.setOutlineColor(sf::Color::White);
  exitButton.setFillColor(sf::Color::Black);
  exitButton.setOutlineThickness(5);

  exitText.setFillColor(sf::Color::White);
  exitText.setCharacterSize(50);
  exitText.setPosition(150,410);
  window->draw(exitButton);
  window->draw(exitText);


  sf::RectangleShape resultButton;
  sf::Text resultText;
  resultButton.setSize(sf::Vector2f(1000,150));
  resultButton.setPosition(sf::Vector2f(725,1300));

  resultButton.setOutlineColor(sf::Color::White);
  resultButton.setOutlineThickness(5);

  if (correct.size() == blankSpaces){
    resultButton.setFillColor(sf::Color::Green);
    resultText.setString("You solved it!");
  }
  else{
    resultButton.setFillColor(sf::Color::Red);
    resultText.setString("Sorry, you lost!");
  }

  resultText.setFont(font);
  resultText.setCharacterSize(100);
  resultText.setFillColor(sf::Color::White);
  resultText.setPosition(740,1300);

  window->draw(resultButton);
  window->draw(resultText);


  window->display();
  sf::Event event;
  while (window->waitEvent(event)){
    if(event.type == sf::Event::Closed){
      window->close();
    }
    else if (event.type == sf::Event::MouseButtonPressed){
      if (replayText.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return true;
      }
      else if (exitText.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return false;
      }

    }
}
}
void game::clearMemory(){
  delete tiles;
  delete p;
}
