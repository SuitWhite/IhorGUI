# IhorGUI
This is graphical user interface (GUI) library for my course work. It was created only using OpenGL libraries, without ready solutions.
In this library you can find base classes to work with GUI: window, button, label, textbox. 

# Install
Try execute install.sh file to install this library

# Use
You can use this library in your app by CMake command find_package(IhorGUI REQUIRED). Example of using this library you can find in app branch

# Window
Window class will help you with simple creation of windows, because
it has all needed methods for work with, like setting color of window, size of window, title of window. 
Be carefull with creating more than one window. This possibility was not fully finished.

# Button
Simple button class, that you can use for interact with user. You can easily attach some function to button by method setOnClick()
Button already have possibility to change it`s color, when you place cursor on it, or when you click.

# Label
Label class provides possibility to create text on your window. You can set Font, color and text of label ( but only in constructor. I was too lazy for create set method. ).

# TextBox
Beatiful class to interact with input user text. You can set text by entering it from keyboard, or paste text by pressing Ctrl + V. You can also copy text from box
by pressing ctrl + V. Work only with latin symbols.

# Conclusion
So, i was created a simple GUI library, that can be used for different goals, like creating chat-bot, simple widgets, or just like demonstration of creation new library.
It`s sad that i will not finish my library, because work that i done enough for my course work. I just have no time for continue work with it, but i proud already achieved result.
