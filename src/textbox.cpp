#include "IhorGUI/textbox.h"
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "IhorGUI/window.h"

// Конструктор кнопки с параметрами
  TextBox::TextBox(float x, float y, float width, float height, std::string text) {
    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;
    
    this->text = text;
    this->textBoxState = NOTFOCUSED;
  }

  // Метод для отрисовки кнопки
  void TextBox::draw() {
    // Встановлюємо матрицю проекції у режим ортогональної проекції
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, parentWindow->getSize().x, 0, parentWindow->getSize().y, -1, 1);

    // Встановлюємо матрицю моделі-виду у одиничну матрицю
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(0.f, 0.f, 0.f, 1.0f);
    // Рисуем текст на кнопке с помощью библиотеки GLUT


    // TMP
    int symbol_width = 8;
    int symbol_height = 13;

    glRasterPos2f(x + symbol_width/2, y + height - symbol_height);

    int line_width = symbol_width/2;
    int lines = 1;
    for (char c : text) {
        line_width += symbol_width;

        if (line_width >= width - symbol_width/2){
            lines += 1;
            line_width = 0;
            glRasterPos2f(x + symbol_width/2, y + height - symbol_height*lines);
        }

        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);

    }

    // Малюємо прямокутник з вибраним кольором
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
  }

  // Метод для проверки попадания курсора в область кнопки
  bool TextBox::isInside(float mouseX, float mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
  }

// Функція для обробки подій курсора
void TextBox::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
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
            //buttonState = PRESSED;
        } else {
            //buttonState = HOVER;
        }
    } else {
        // Якщо ні, то змінюємо стан кнопки на NORMAL
        //buttonState = NORMAL;
    }
}

// Функція для обробки подій миші
void TextBox::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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
            textBoxState = FOCUSED;
            std::cout << "IM FOCUSED NOW";
        } else if (action == GLFW_RELEASE) {
            //buttonState = HOVER;
            // Тут можна додати дію, яку виконує кнопка при натисканні
            //press();
        }
    }
}

void TextBox::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (action == GLFW_RELEASE && textBoxState == FOCUSED){
        text += "s";
    }
}