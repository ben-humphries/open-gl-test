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


  float vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f

  };

  
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const char* vertexSource = R"glsl(
  #version 150 core

  in vec2 position;

  void main()
  {
  gl_Position = vec4(position, 0.0, 1.0);
  }
  )glsl";

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);

  glCompileShader(vertexShader);

  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

  if(!status == GL_TRUE){
    printf("Vertex shader was not compiled successfully!\n");
  }
  
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
