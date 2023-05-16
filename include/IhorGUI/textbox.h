#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "widget.h"
void empty();

enum TextBoxState {
    NOTFOCUSED,
    FOCUSED
};

class TextBox: public Widget{
  // Координати лівого нижнього кута 
  float x;
  float y;
  // Ширина і висота текстового поля
  float width;
  float height;
  // Колір тексту в формате RGBA
  float color[4];
  // Текст на кнопке
  std::string text;

  TextBoxState textBoxState;

public:
    TextBox(float x, float y, float width, float height, std::string text="");
    virtual void draw();
    bool isInside(float mouseX, float mouseY);

    virtual void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};