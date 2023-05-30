#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "widget.h"
void empty();

enum ButtonState {
    NORMAL,
    HOVER,
    PRESSED
};

class Button: public Widget{
  float x;
  float y;

  float width;
  float height;

  float color[4];
  float color_of_text[4];

  std::string text;
  
  std::function<void()> onClick;

  ButtonState buttonState;

public:
    Button(float x, float y, float width, float height, float color[4], std::string text, std::function<void()> onClick = empty);
    virtual void draw();
    bool isInside(float mouseX, float mouseY);
    void press();
    void setOnClick(std::function<void()> function);
    virtual void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};