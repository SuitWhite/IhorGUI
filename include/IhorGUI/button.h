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

// Класс кнопки на основе OpenGL
class Button: public Widget{
  // Координаты левого нижнего угла кнопки
  float x;
  float y;
  // Ширина и высота кнопки
  float width;
  float height;
  // Цвет кнопки в формате RGBA
  float color[4];
  // Текст на кнопке
  std::string text;
  // Функция, которая вызывается при нажатии на кнопку
  std::function<void()> onClick;

  ButtonState buttonState;

public:
    Button(float x, float y, float width, float height, float color[4], std::string text, std::function<void()> onClick = empty);
    virtual void draw();
    bool isInside(float mouseX, float mouseY);
    void press();
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};