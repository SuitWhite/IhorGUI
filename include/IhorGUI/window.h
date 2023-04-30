#pragma once
#include "common.h"
#include "layoutmanager.h"
#include "eventmanager.h"
#include "widget.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    Vector2 sizeMainWindow;
    Vector2 maxSize;
    Vector2 minSize;

    LayoutManager layoutManager;
    EventManager eventManager;

    std::string titleMainWindow;

    GLFWwindow* window;
public:
    Window(Vector2 size, const char *title);
    ~Window();

    void addChild(Widget *widget);

    void setTitle(const std::string &title);

    void setMaxSize(const Vector2 &size);

    void setMinSize(const Vector2 &size);

    bool isClosed();

    void draw();
};
