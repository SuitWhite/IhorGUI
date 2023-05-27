#include "IhorGUI/window.h"
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "IhorGUI/widget.h"

Window::Window(Vector2 size, const char *title): minSize(200, 200), maxSize(800, 600), sizeMainWindow(size){
    int argc = 1;
    char **argv = new char*[argc];
    argv[0] = "";

    if (!glut_initialized)
    glutInit(&argc, argv);

    glut_initialized = true;

    this->color[0] = 1.f; this->color[1] = 1.f; this->color[2] = 1.f; this->color[3] = 1.f;

    if (!glfw_initialized){
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
        }
    }

    glfw_initialized = true;

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
    glClearColor(color[0], color[1], color[2], color[3]);

    glfwSetWindowUserPointer(window, &eventManager);
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
    eventManager.addComponent(widget);
    layoutManager.addComponent(widget);

    glfwSetCursorPosCallback(window, NULL);
    glfwSetCursorPosCallback(window, eventManager.cursorposfun);

    glfwSetMouseButtonCallback(window, NULL);
    glfwSetMouseButtonCallback(window, eventManager.mousebuttonfun);

    glfwSetKeyCallback(window, NULL);
    glfwSetKeyCallback(window, eventManager.keyfun);
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

void Window::setColor(float color[4]){
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];

    glClearColor(color[0], color[1], color[2], color[3]);   
}

void Window::close(){
    glfwSetWindowShouldClose(window, GLFW_FALSE);
}

void Window::setSize(const Vector2 &size){
    glfwSetWindowSize(window, size.x, size.y);
}

void Window::clear(){
    layoutManager.clearComponents();
    eventManager.clearComponents();
}
