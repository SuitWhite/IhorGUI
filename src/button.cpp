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

// Конструктор кнопки с параметрами
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

  // Метод для отрисовки кнопки
  void Button::draw() {
    if (buttonState == NORMAL){
        color[4] = 0.8;
    } else if (buttonState == HOVER){
      color[4] = 0.3;
    } else if (buttonState == PRESSED){
      color[4] = 1;
    }
    // Встановлюємо матрицю проекції у режим ортогональної проекції
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, parentWindow->getSize().x, 0, parentWindow->getSize().y, -1, 1);

    // Встановлюємо матрицю моделі-виду у одиничну матрицю
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(color_of_text[0], color_of_text[1], color_of_text[2], color_of_text[3]);
    // Малюємо текст через бібліотеку GLUT
    glRasterPos2f(x + width/2 - text.length()*5.5, y + height / 2 - 4.5f);
    for (char c : text) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    // Малюємо прямокутник з вибраним кольором
    glColor4f(color[0], color[1], color[2], color[4]);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
  }

  // Метод для проверки попадания курсора в область кнопки
  bool Button::isInside(float mouseX, float mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
  }

  // Метод для обработки нажатия на кнопку
  void Button::press() {
    if (onClick) {
      onClick();
    }
  }

    void Button::setOnClick(std::function<void()> function){
        this->onClick = function;
    }

// Функція для обробки подій курсора
void Button::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // now you can use width and height variables
    // Переводимо координати курсора у систему координат OpenGL
    xpos = xpos;
    ypos = windowHeight - ypos;

    // Перевіряємо чи курсор знаходиться над кнопкою
    if (isInside(xpos, ypos)) {
        // Якщо так, то змінюємо стан кнопки на HOVER або PRESSED залежно від того чи натиснута ліва кнопка миші
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            buttonState = PRESSED;
        } else {
            buttonState = HOVER;
        }
    } else {
        // Якщо ні, то змінюємо стан кнопки на NORMAL
        buttonState = NORMAL;
    }
}

// Функція для обробки подій миші
void Button::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // now you can use width and height variables

    // Переводимо координати курсора у систему координат OpenGL
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos;
    ypos = windowHeight - ypos;

    // Перевіряємо чи курсор знаходиться над кнопкою і чи натиснута ліва кнопка
        if (isInside(xpos, ypos) && button == GLFW_MOUSE_BUTTON_LEFT) {
        // Якщо так, то змінюємо стан кнопки на PRESSED або HOVER залежно від того чи відпущена кнопка миші
        if (action == GLFW_PRESS) {
            buttonState = PRESSED;
        } else if (action == GLFW_RELEASE) {
            buttonState = HOVER;
            // Тут можна додати дію, яку виконує кнопка при натисканні
            press();
        }
    }
}