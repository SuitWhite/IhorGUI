#include "IhorGUI/window.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


Window::Window(Vector2 size, const char *title){
    if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
  }

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
  }

  
}

void Window::drawLoop(){
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
}

Window::~Window(){ return; }