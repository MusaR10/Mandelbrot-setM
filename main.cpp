#include "ComplexPlane.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {

  int pixelWidth = VideoMode::getDesktopMode().width / 2;
  int pixelHeight = VideoMode::getDesktopMode().height / 2;

  VideoMode vm(pixelWidth, pixelHeight);
  RenderWindow window(vm, "Mandelbrot Set", Style::Default);
  ComplexPlane complexPlane(pixelWidth, pixelHeight);

  Font font;
  font.loadFromFile("KOMIKAP_.ttf");
  if (!font.loadFromFile("KOMIKAP_.ttf")) {
    cerr << "Something wrong with font" << endl;
    return 1;
  }

  Text text;
  text.setFont(font);
  text.setString("Instructions: ");
  text.setCharacterSize(20);
  text.setFillColor(Color::White);
  text.setStyle(Text::Bold);

  while (window.isOpen()) 
  {
    Event event;
    while (window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed) {window.close();}

      if (event.type == sf::Event::MouseButtonPressed) 
      {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
          cout << "Left click = Zooming in." << endl;
          cout << "Mouse x: " << event.mouseButton.x << endl;
          cout << "Mouse y: " << event.mouseButton.y << endl;

          complexPlane.zoomIn();
//          complexPlane.setCenter(
          Vector2i(event.mouseButton.x, event.mouseButton.y);
        }
       
        else if (event.mouseButton.button == sf::Mouse::Right) 
        {
        cout << "the right button was pressed" << endl;
        cout << "mouse x: " << event.mouseButton.x << endl;
        cout << "mouse y: " << event.mouseButton.y << endl;

        complexPlane.zoomOut();
  //      complexPlane.setCenter(
        Vector2i(event.mouseButton.x, event.mouseButton.y);
        }
      }
      else if (event.type == sf::Event::MouseMoved) 
      {
    //    complexPlane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
      }
        
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) 
    {
      window.close();
    }

   // complexPlane.updateRender();
    complexPlane.loadText(text);
      
    window.clear();
    window.draw(complexPlane);
    window.draw(text);
    window.display();
  }
}
