#include <SFML/Window.hpp>
#include <GL/glew.h>

#include <fstream>

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

  //Open and compile vertex shader
  FILE * vertexFile = fopen("shaders/vertex.glsl", "r");
  if (vertexFile == NULL) {
    fprintf(stderr, "Could not load vertex shader.\n");
    return -1;
  }
  int len = 0;
  while (fgetc(vertexFile) != EOF)
    len++;
  fseek(vertexFile, 0, SEEK_SET);
  char * vertex = (char*) malloc(sizeof(char) * len + 1);
  fread(vertex, len, sizeof(char), vertexFile);
  vertex[len] = '\0';


  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex, NULL);

  glCompileShader(vertexShader);

  //Open and compile fragment shader
  FILE * fragmentFile = fopen("shaders/fragment.glsl", "r");
  if (fragmentFile == NULL) {
    fprintf(stderr, "Could not load fragment shader.\n");
    return -1;
  }
  len = 0;
  while (fgetc(fragmentFile) != EOF)
    len++;
  fseek(fragmentFile, 0, SEEK_SET);
  char * fragment = (char*) malloc(sizeof(char) * len + 1);
  fread(fragment, len, sizeof(char), fragmentFile);
  fragment[len] = '\0';


  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment, NULL);

  glCompileShader(fragmentShader);  

  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

  if(status == GL_TRUE){
    printf("Vertex shader was compiled successfully!\n");
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

  if(status == GL_TRUE){
    printf("Fragment shader was compiled successfully!\n");
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
