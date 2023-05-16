#include "IhorGUI/eventmanager.h"
#include "IhorGUI/widget.h"
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

using namespace std::placeholders;

void EventManager::addComponent(Widget *widget){
    components.push_back(widget);

    this->cursorposfun = [](GLFWwindow* w, double a, double b)
    {
        static_cast<EventManager*>(glfwGetWindowUserPointer(w))->cursorPositionCallbacks( w, a, b );
    };

    this->mousebuttonfun = [](GLFWwindow* w, int a, int b , int c)
    {
        static_cast<EventManager*>(glfwGetWindowUserPointer(w))->mouseButtonCallbacks( w, a, b, c );
    };

    this->keyfun = [](GLFWwindow* w, int a, int b , int c, int d)
    {
        static_cast<EventManager*>(glfwGetWindowUserPointer(w))->keyCallbacks( w, a, b, c, d );
    };
}

void EventManager::cursorPositionCallbacks(GLFWwindow* window, double xpos, double ypos){
    for (const auto &elem: components){
        elem->cursorPositionCallback(window, xpos, ypos);
    }
}

void EventManager::mouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods){
    for (const auto &elem: components){
        elem->mouseButtonCallback(window, button, action, mods);
    }
}

void EventManager::keyCallbacks(GLFWwindow *window, int key, int scancode, int action, int mods){
    for (const auto &elem: components){
        elem->keyCallback(window, key, scancode, action, mods);
    }
}