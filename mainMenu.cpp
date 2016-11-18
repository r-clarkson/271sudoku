#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.cpp"
using namespace std;

class mainMenu{
public:
  game chooseDifficulty();
};

game mainMenu::chooseDifficulty(){
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  int width = mode.width;
  int height = mode.height;
  sf::RenderWindow window(mode, "Sudoku");
  while (window.isOpen())
  {
    // Event processing
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Request for closing the window
      if (event.type == sf::Event::Closed)
      window.close();
    }
    //activate window for rendering and set background color
    window.setActive();
    sf::Texture texture;
    if(!texture.loadFromFile("background.jpg")){
      cout << "Background error" << endl;
    }
    sf::Sprite background(texture);

    //set font for text
    sf::Font font;
    if (!font.loadFromFile("CourierNew.ttf")){
      window.close();
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
    window.draw(background);
    window.draw(r1);
    window.draw(e);
    window.draw(m);
    window.draw(h);
    window.draw(start);

    window.display();
    //returns the char e,m, or h depending on which button the user clicks

    if (event.type == sf::Event::MouseButtonPressed){
      if (e.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        game g = game(window,'e');
        return g;
      }
      else if (m.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        game g = game(window,'m');
        return g;
      }
      else if(h.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
        game g = game(window,'h');
        return g;
      }
    }
  }
}
