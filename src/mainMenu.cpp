#include <stdio.h>

#include <iostream>
using namespace std;

class mainMenu{
public:
  int width;
  int height;
  sf::RenderWindow *window;
  mainMenu(sf::RenderWindow& w, int wid, int h){
    width = wid;
    height = h;
    window = &w;
  }
  char chooseDifficulty();
  sf::RenderWindow *getWindow();
  int getWidth();
  int getHeight();
};
int mainMenu::getWidth(){
  return width;
}
int mainMenu::getHeight(){
  return height;
}
sf::RenderWindow* mainMenu::getWindow(){
  return window;
}
/**
* Uses SFML to make a main menu and let the user click on which difficulty they want to play
* Returns the char of difficulty clicked on
*/
char mainMenu::chooseDifficulty(){
  //sets background
  sf::Event event;
  sf::Texture texture;
  if(!texture.loadFromFile("resources/background.jpg")){
    cout << "Background error" << endl;
  }
  sf::Sprite background(texture);

  //set font for text
  sf::Font font;
  if (!font.loadFromFile("resources/CourierNew.ttf")){
    window->close();
    cout << "Font Error" << endl;

  }
  //creates Soduku title box
  sf::Text start("Sudoku",font);
  start.setCharacterSize(150);
  start.setFillColor(sf::Color::White);
  start.setOutlineColor(sf::Color::Black);
  start.setOutlineThickness(7);
  //to center text
  sf::FloatRect temp = start.getLocalBounds();
  start.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  start.setPosition(sf::Vector2f(width/2.1f,height/8.0f));
  //black background of title
  sf::RectangleShape r1;
  r1.setSize(sf::Vector2f(start.getLocalBounds().width+30,start.getLocalBounds().height+30));
  r1.setPosition(sf::Vector2f(width/2.12f,height/6.7f));
  r1.setOrigin(start.getOrigin());
  r1.setFillColor(sf::Color::Black);
  r1.setOutlineColor(sf::Color::White);
  r1.setOutlineThickness(5);

  //create text easy button
  sf::Text e("EASY",font);
  e.setCharacterSize(150);
  e.setFillColor(sf::Color::White);
  e.setOutlineColor(sf::Color::Black);
  e.setOutlineThickness(7);
  //center text
  temp = e.getLocalBounds();
  e.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  e.setPosition(sf::Vector2f(width/2.1f,height/4.0f));
  //medium button
  sf::Text m("MEDIUM",font);
  m.setCharacterSize(150);
  m.setFillColor(sf::Color::White);
  m.setOutlineColor(sf::Color::Black);
  m.setOutlineThickness(7);
  //centering
  temp = m.getLocalBounds();
  m.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  m.setPosition(sf::Vector2f(width/2.1f,height/2.5f));
  //hard button
  sf::Text h("HARD",font);
  h.setCharacterSize(150);
  h.setFillColor(sf::Color::White);
  h.setOutlineColor(sf::Color::Black);
  h.setOutlineThickness(7);
  //centering
  temp = h.getLocalBounds();
  h.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  h.setPosition(sf::Vector2f(width/2.1f,height/1.8f));

  //drawing all elements, then displaying
  window->draw(background);
  window->draw(r1);
  window->draw(e);
  window->draw(m);
  window->draw(h);
  window->draw(start);

  window->display();

  //returns the char e,m, or h depending on which button the user clicks
  while (window->waitEvent(event)){
    if(event.type == sf::Event::Closed){
      // window closed
      window->close();
    }

    else if (event.type == sf::Event::MouseButtonPressed){
      if (e.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return 'e';
      }
      else if (m.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return 'm';
      }
      else if(h.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        return 'h';
      }
    }
  }
  return 'q';
}
