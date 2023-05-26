#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "widget.h"

class Label: public Widget{
  // Координати лівого нижнього кута 
  float x;
  float y;
  // Ширина і висота текстового поля
  float width;
  float height;

  float color[4];

  std::string text;
  
  void* font;
  int symbol_width, symbol_height;

public:
    Label(float x, float y, float width, float height, std::string text="");
    void setFont(void* font, int symbol_width, int symbol_height);
    void setColor(float color[4]);
    virtual void draw();
};