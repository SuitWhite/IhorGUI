#include "IhorGUI/label.h"
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "IhorGUI/window.h"

Label::Label(float x, float y, float width, float height, std::string text) {
    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    this->color[0] = 1.f; this->color[1] = 1.f; this->color[2] = 1.f; this->color[3] = 1.f;


    this->text = text;
    this->font = GLUT_BITMAP_8_BY_13;
    this->symbol_width = 8;
    this->symbol_height = 13;
  }


  void Label::draw() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, parentWindow->getSize().x, 0, parentWindow->getSize().y, -1, 1);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(color[0], color[1], color[2], color[3]);

    glRasterPos2f(x + symbol_width/2, y + height - symbol_height);

    double line_width = symbol_width / 2.;
    int lines = 1;
    int total_height_of_text = symbol_height;
    for (char c : text) {
        line_width += symbol_width;

        if (line_width >= width - symbol_width/2.){
            lines += 1;

            total_height_of_text += symbol_height;
            line_width = symbol_width/2. + symbol_width;
            glRasterPos2f(x + symbol_width/2, y + height - symbol_height*lines);
        }

        if (total_height_of_text <= height)
            glutBitmapCharacter(font, c);

    }
  }

void Label::setFont(void* font, int symbol_width, int symbol_height){
    this->font = font;
    this->symbol_width = symbol_width;
    this->symbol_height = symbol_height;
}

void Label::setColor(float color[4]){
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
}