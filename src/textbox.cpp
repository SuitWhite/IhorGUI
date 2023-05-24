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

    std::string text;

    if (this->text.size() > 0){
        text = this->text;
        glColor4f(0.f, 0.f, 0.f, 1.0f);
    } else{
        text = this->placeholderText;
        glColor4f(0.f, 0.f, 0.f, 0.35f);
    }

    // TMP
    double symbol_width = 8;
    double symbol_height = 13;

    glRasterPos2f(x + symbol_width/2, y + height - symbol_height);

    double line_width = symbol_width / 2.;
    int lines = 1;
    for (char c : text) {
        line_width += symbol_width;

        if (line_width >= width - symbol_width/2.){
            lines += 1;
            line_width = symbol_width/2. + symbol_width;
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
        } else if (action == GLFW_RELEASE) {
            //buttonState = HOVER;
            // Тут можна додати дію, яку виконує кнопка при натисканні
            //press();
        }
    }
}

void TextBox::setPlaceholder(std::string str){
    placeholderText = str;
};

void TextBox::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    
    if (textBoxState == FOCUSED && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && key == GLFW_KEY_V && action == GLFW_RELEASE){
        text += glfwGetClipboardString(window);
        return;
    }

    if (textBoxState == FOCUSED && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && key == GLFW_KEY_C && action == GLFW_RELEASE){
        glfwSetClipboardString(window, text.c_str());
        return;
    }

    if (textBoxState == FOCUSED && key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS){
        text = text.substr(0, text.length()-1);
        return;
    }

    if (action == GLFW_RELEASE && textBoxState == FOCUSED ){
        switch (key)
        {
        case GLFW_KEY_0:
            text += "0";
            break;
        case GLFW_KEY_1:
            text += "1";
            break;
        case GLFW_KEY_2:
            text += "2";
            break;
        case GLFW_KEY_3:
            text += "3";
            break;
        case GLFW_KEY_4:
            text += "4";
            break;
        case GLFW_KEY_5:
            text += "5";
            break;
        case GLFW_KEY_6:
            text += "6";
            break;
        case GLFW_KEY_7:
            text += "7";
            break;
        case GLFW_KEY_8:
            text += "8";
            break;
        case GLFW_KEY_9:
            text += "9";
            break;
        

        
        default:
            break;
        }
    }

    if (action == GLFW_RELEASE && textBoxState == FOCUSED && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        switch (key)
        {
        case GLFW_KEY_A:
            text += "A";
            break;
        case GLFW_KEY_B:
            text += "B";
            break;
        case GLFW_KEY_C:
            text += "C";
            break;
        case GLFW_KEY_D:
            text += "D";
            break;
        case GLFW_KEY_E:
            text += "E";
            break;
        case GLFW_KEY_F:
            text += "F";
            break;
        case GLFW_KEY_G:
            text += "G";
            break;
        case GLFW_KEY_H:
            text += "H";
            break;
        case GLFW_KEY_I:
            text += "I";
            break;
        case GLFW_KEY_J:
            text += "J";
            break;
        case GLFW_KEY_K:
            text += "K";
            break;
        case GLFW_KEY_L:
            text += "L";
            break;
        case GLFW_KEY_M:
            text += "M";
            break;
        case GLFW_KEY_N:
            text += "N";
            break;
        case GLFW_KEY_O:
            text += "O";
            break;
        case GLFW_KEY_P:
            text += "P";
            break;
        case GLFW_KEY_Q:
            text += "Q";
            break;
        case GLFW_KEY_R:
            text += "R";
            break;
        case GLFW_KEY_S:
            text += "S";
            break;
        case GLFW_KEY_T:
            text += "T";
            break;
        case GLFW_KEY_U:
            text += "U";
            break;
        case GLFW_KEY_V:
            text += "V";
            break;
        case GLFW_KEY_W:
            text += "W";
            break;
        case GLFW_KEY_X:
            text += "X";
            break;
        case GLFW_KEY_Y:
            text += "Y";
            break;
        case GLFW_KEY_Z:
            text += "Z";
            break;
        
        default:
            break;
        }
    }
    else if (action == GLFW_RELEASE && textBoxState == FOCUSED ){
        switch (key)
        {
        case GLFW_KEY_A:
            text += "a";
            break;
        case GLFW_KEY_B:
            text += "b";
            break;
        case GLFW_KEY_C:
            text += "c";
            break;
        case GLFW_KEY_D:
            text += "d";
            break;
        case GLFW_KEY_E:
            text += "e";
            break;
        case GLFW_KEY_F:
            text += "f";
            break;
        case GLFW_KEY_G:
            text += "g";
            break;
        case GLFW_KEY_H:
            text += "h";
            break;
        case GLFW_KEY_I:
            text += "i";
            break;
        case GLFW_KEY_J:
            text += "j";
            break;
        case GLFW_KEY_K:
            text += "k";
            break;
        case GLFW_KEY_L:
            text += "l";
            break;
        case GLFW_KEY_M:
            text += "m";
            break;
        case GLFW_KEY_N:
            text += "n";
            break;
        case GLFW_KEY_O:
            text += "o";
            break;
        case GLFW_KEY_P:
            text += "p";
            break;
        case GLFW_KEY_Q:
            text += "q";
            break;
        case GLFW_KEY_R:
            text += "r";
            break;
        case GLFW_KEY_S:
            text += "s";
            break;
        case GLFW_KEY_T:
            text += "t";
            break;
        case GLFW_KEY_U:
            text += "u";
            break;
        case GLFW_KEY_V:
            text += "v";
            break;
        case GLFW_KEY_W:
            text += "w";
            break;
        case GLFW_KEY_X:
            text += "x";
            break;
        case GLFW_KEY_Y:
            text += "y";
            break;
        case GLFW_KEY_Z:
            text += "z";
            break;
        
        default:
            break;
        }
    }
}