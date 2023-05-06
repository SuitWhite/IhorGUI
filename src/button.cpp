#include "IhorGUI/button.h"
#include <functional>
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
    this->text = text;
    this->buttonState = NORMAL;
    this->onClick = onClick;
  }

  // Метод для отрисовки кнопки
  void Button::draw() {
    // Встановлюємо матрицю проекції у режим ортогональної проекції
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, parentWindow->getSize().x, 0, parentWindow->getSize().y, -1, 1);

    // Встановлюємо матрицю моделі-виду у одиничну матрицю
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::string text = "Bruh";
    glColor4f(0.3f, 0.2f, 0.8f, 1.0f);
    // Рисуем текст на кнопке с помощью библиотеки GLUT
    glRasterPos2f(x + width/2 - text.length()*5.5, y + height / 2 - 4.5f);
    for (char c : text) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    // Малюємо прямокутник з вибраним кольором
    glColor3f(color[0], color[1], color[2]);
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

// Функція для обробки подій курсора
void Button::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    // Переводимо координати курсора у систему координат OpenGL
    xpos = xpos;
    ypos = height - ypos;

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
    // Переводимо координати курсора у систему координат OpenGL
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos;
    ypos = height - ypos;

    // Перевіряємо чи курсор знаходиться над кнопкою і чи натиснута ліва кнопка
        if (isInside(xpos, ypos) && button == GLFW_MOUSE_BUTTON_LEFT) {
        // Якщо так, то змінюємо стан кнопки на PRESSED або HOVER залежно від того чи відпущена кнопка миші
        if (action == GLFW_PRESS) {
            buttonState = PRESSED;
        } else if (action == GLFW_RELEASE) {
            buttonState = HOVER;
            // Тут можна додати дію, яку виконує кнопка при натисканні
            //std::cout << "Button clicked!\n";
        }
    }
}