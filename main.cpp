#include <SFML/Window.hpp>

int main(){

  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 2;

  //Request OpenGL Version 3.2
  settings.majorVersion = 3;
  settings.minorVersion = 2;
  settings.attributeFlags = sf::ContextSettings::Core;

  sf::Window window(sf::VideoMode(800,600), "OpenGL 3.2 Test", sf::Style::Close, settings);

  sf::Event e;


  bool running = true;
  while(running){
    
    while(window.pollEvent(e)){
      
      switch(e.type){
      case sf::Event::Closed:
	running = false;
	break;

      case sf::Event::KeyPressed:
	if(e.key.code == sf::Keyboard::Escape){
	  running = false;
	}
	break;
      }
      
    }
  }
  
  return 0;
}