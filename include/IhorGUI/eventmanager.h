#pragma once
#include "common.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class Widget;

class EventManager{
    private:
    std::vector<Widget*> components;
public:
    void addComponent(Widget* component);
    void cursorPositionCallbacks(GLFWwindow* window, double xpos, double ypos);
    void mouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods);

    GLFWcursorposfun cursorposfun;
    GLFWmousebuttonfun mousebuttonfun;
};