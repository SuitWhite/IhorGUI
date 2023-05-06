#pragma once

class Window;

class Widget{
protected:
    Window* parentWindow;
public:
    virtual void draw();
    friend class Window;
};