#include "IhorGUI/button.h"
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "IhorGUI/window.h"

void empty(){
    return;
}

  Button::Button(float x, float y, float width, float height, float color[4], std::string text, std::function<void()> onClick) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    for (int i = 0; i < 4; i++) {
      this->color[i] = color[i];
    }
    color_of_text[0] = 1.f; color_of_text[1] = 1.f; color_of_text[2] = 1.f; color_of_text[3] = 1.f;
    this->text = text;
    this->buttonState = NORMAL;
    this->onClick = onClick;
  }

  void Button::draw() {
    if (buttonState == NORMAL){
        color[4] = 0.8;
    } else if (buttonState == HOVER){
      color[4] = 0.3;
    } else if (buttonState == PRESSED){
      color[4] = 1;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, parentWindow->getSize().x, 0, parentWindow->getSize().y, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(color_of_text[0], color_of_text[1], color_of_text[2], color_of_text[3]);
    glRasterPos2f(x + width/2 - text.length()*5.5, y + height / 2 - 4.5f);
    for (char c : text) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glColor4f(color[0], color[1], color[2], color[4]);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
  }


  bool Button::isInside(float mouseX, float mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
  }


  void Button::press() {
    if (onClick) {
      onClick();
    }
  }

    void Button::setOnClick(std::function<void()> function){
        this->onClick = function;
    }


void Button::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);


    xpos = xpos;
    ypos = windowHeight - ypos;


    if (isInside(xpos, ypos)) {

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            buttonState = PRESSED;
        } else {
            buttonState = HOVER;
        }
    } else {

        buttonState = NORMAL;
    }
}


void Button::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);



    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos;
    ypos = windowHeight - ypos;


        if (isInside(xpos, ypos) && button == GLFW_MOUSE_BUTTON_LEFT) {

        if (action == GLFW_PRESS) {
            buttonState = PRESSED;
        } else if (action == GLFW_RELEASE) {
            buttonState = HOVER;

            press();
        }
    }
}