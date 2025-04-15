#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ChessBoard.h"
using namespace sf;
const float w = 500;
const float h = 500;
float scaleFactor = w / 894.0f;

class START
{
private:
  sf::Texture texture[3];
  sf::Sprite sprite[3];
  sf::RectangleShape rectangle;

public:
  START()
  {

    const float w = 500;
    const float h = 500;
    float scaleFactor = w / 894.0f;

    sf::RenderWindow window(sf::VideoMode(w, h), "Chess el ghaleba");

    // Load icon
    sf::Image icon;
    if (icon.loadFromFile("images/icon.png"))
      window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load images
    texture[0].loadFromFile("images/play-button.png");
    texture[2].loadFromFile("images/board.png");

    sprite[0].setTexture(texture[0]);
    sprite[2].setTexture(texture[2]);

    // Scale background
    sprite[2].setScale(0.73f, 0.73f);
    sprite[2].setPosition((w - sprite[2].getGlobalBounds().width) / 2.f, -120);

    sprite[0].setScale(0.4f, 0.4f); // Or whatever scale you use
    sprite[0].setPosition((w - sprite[0].getGlobalBounds().width) / 2.f, 400);

    while (window.isOpen())
    {
      Vector2i pos = Mouse::getPosition(window);
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          if (sprite[0].getGlobalBounds().contains(pos.x, pos.y))
          {
            window.close();
            ChessBoard graphics;
            graphics.MainFunctions(1);
          }
          if (sprite[1].getGlobalBounds().contains(pos.x, pos.y))
          {
            window.close();
            ifstream in, in2;
            in.open("spritepositions.txt");
            in2.open("boardpositions.txt");
            for (int j = 0; j < 64; j++)
            {
              int a, b;
              char c, d;
              in >> a >> c;
              spritepositions[j] = a;
              in2 >> b >> d;
              board[j] = b;
            }
            ChessBoard graphics;
            graphics.MainFunctions(0);
          }
        }
      }

      window.clear();
      window.draw(rectangle);
      window.draw(sprite[2]);
      window.draw(sprite[0]);
      window.draw(sprite[1]);
      window.display();
    }
  }
};