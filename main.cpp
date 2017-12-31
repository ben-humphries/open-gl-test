#include <SFML/Window.hpp>
#include <GL/glew.h>


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

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  printf("%u\n", vertexBuffer);
  
  bool running = true;
  while(running){

    sf::Event e;
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
