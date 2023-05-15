#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class Window;

class Widget{
protected:
    Window* parentWindow;
public:
    virtual void draw();
    friend class Window;
    virtual void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};