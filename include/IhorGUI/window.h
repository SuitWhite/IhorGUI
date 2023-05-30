#pragma once
#include "common.h"
#include "layoutmanager.h"
#include "eventmanager.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Widget;

static bool glut_initialized = false;
static bool glfw_initialized = false;

class Window
{
private:
    Vector2 sizeMainWindow;
    Vector2 maxSize;
    Vector2 minSize;

    LayoutManager layoutManager;
    EventManager eventManager;

    float color[4];

    std::string titleMainWindow;
public:
    GLFWwindow* window;
    Window(Vector2 size, const char *title);
    ~Window();

    void addChild(Widget *widget);

    void setColor(float color[4]);

    void setTitle(const std::string &title);

    void setMaxSize(const Vector2 &size);

    void setMinSize(const Vector2 &size);

    void setSize(const Vector2 &size);

    const Vector2 getSize();

    bool isClosed();

    void draw();

    void close();

    void clear();
};
