#include "IhorGUI/window.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


Window::Window(Vector2 size, const char *title): minSize(200, 200), maxSize(800, 600){
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

bool Window::isClosed(){
    return glfwWindowShouldClose(window);
}

void Window::draw(){
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

Window::~Window(){ 
    glfwTerminate();
    return; 
}

void Window::addChild(Widget *widget){
    layoutManager.addComponent(widget);
}

void Window::setTitle(const std::string &title){
    glfwSetWindowTitle(window, title.c_str());
}

void Window::setMinSize(const Vector2 &size){
    minSize = size;
    glfwSetWindowSizeLimits(window, minSize.x, minSize.y, maxSize.x, maxSize.y);
}

void Window::setMaxSize(const Vector2 &size){
    maxSize = size;
    glfwSetWindowSizeLimits(window, minSize.x, minSize.y, maxSize.x, maxSize.y); 
}
