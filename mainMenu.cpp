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
};

sf::RenderWindow* mainMenu::getWindow(){
  return window;
}

char mainMenu::chooseDifficulty(){
  // Event processing
  sf::Event event;
  sf::Texture texture;
  if(!texture.loadFromFile("background.jpg")){
    cout << "Background error" << endl;
  }
  sf::Sprite background(texture);

  //set font for text
  sf::Font font;
  if (!font.loadFromFile("CourierNew.ttf")){
    window->close();
    cout << "Font Error" << endl;

  }
  sf::Text start("Sudoku",font);
  start.setCharacterSize(150);
  start.setColor(sf::Color::White);
  start.setOutlineColor(sf::Color::Black);
  start.setOutlineThickness(7);


  //to center text
  sf::FloatRect temp = start.getLocalBounds();
  start.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  start.setPosition(sf::Vector2f(width/2.1f,height/8.0f));
  //black background of first button
  sf::RectangleShape r1;
  r1.setSize(sf::Vector2f(start.getLocalBounds().width+10,start.getLocalBounds().height+10));
  r1.setPosition(sf::Vector2f(width/2.1f,height/6.5f));
  r1.setOrigin(start.getOrigin());
  r1.setFillColor(sf::Color::Black);
  r1.setOutlineColor(sf::Color::White);
  r1.setOutlineThickness(5);

  //create text for buttons
  sf::Text e("EASY",font);
  e.setCharacterSize(150);
  e.setColor(sf::Color::White);
  e.setOutlineColor(sf::Color::Black);
  e.setOutlineThickness(7);
  //center text
  temp = e.getLocalBounds();
  e.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  e.setPosition(sf::Vector2f(width/2.1f,height/4.0f));
  //medium button
  sf::Text m("MEDIUM",font);
  m.setCharacterSize(150);
  m.setColor(sf::Color::White);
  m.setOutlineColor(sf::Color::Black);
  m.setOutlineThickness(7);
  //centering
  temp = m.getLocalBounds();
  m.setOrigin(temp.left + temp.width/2.0f, temp.top  + temp.height/2.0f);
  m.setPosition(sf::Vector2f(width/2.1f,height/2.5f));
  //hard button
  sf::Text h("HARD",font);
  h.setCharacterSize(150);
  h.setColor(sf::Color::White);
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
    switch (event.type)
    {
      // window closed
      case sf::Event::Closed:
      window->close();
      break;

      case sf::Event::MouseButtonPressed:
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
}
