#include "IhorGUI/window.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "IhorGUI/widget.h"

Window::Window(Vector2 size, const char *title): minSize(200, 200), maxSize(800, 600), sizeMainWindow(size){
    int argc = 1;
    char **argv = new char*[argc];
    argv[0] = "bruh";
    glutInit(&argc, argv);

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

    // Вмикаємо буфер глибини
    glEnable(GL_DEPTH_TEST);
    // Вмикаємо блендінг
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Встановлюємо кольор фону
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

bool Window::isClosed(){
    return glfwWindowShouldClose(window);
}

void Window::draw(){
    // Очищуємо буфери кольору і глибини
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    layoutManager.drawComponents();

    // Обмінюємо буфери вікна
    glfwSwapBuffers(window);

    // Обробляємо події вводу-виводу
    glfwPollEvents();
}

Window::~Window(){ 
    glfwTerminate();
    return; 
}

void Window::addChild(Widget *widget){
    widget->parentWindow = this;
    layoutManager.addComponent(widget);
}

const Vector2 Window::getSize(){
    return sizeMainWindow;
};

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
