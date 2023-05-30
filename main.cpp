#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <IhorGUI/button.h>
#include <IhorGUI/textbox.h>
#include <IhorGUI/label.h>
#include <IhorGUI/common.h>
#include <IhorGUI/window.h>

using namespace std;

static bool askerDone = false;
static bool sendMessage = false;

void exitButtonFunc(){
    exit(0);
}

void doneButtonFunc(){
    askerDone = true;
}

void sendMessageFunc(){
    sendMessage = true;
}

int main(){
    Vector2 sizeOfWind(600, 600);
    Window mainWindow(sizeOfWind, "OpenAi API-key");
    string api_key;
    {
        
        float color_background[4] = {0.2f, 0.3f, 0.3f, 1.0f};
        mainWindow.setColor(color_background);

        string text_of_label_in_asker = "Welcome! Enter your api-key!";
        Label *welcometext = new Label(sizeOfWind.x/2-8*text_of_label_in_asker.size()/2, 350, 250, 20, text_of_label_in_asker);

        TextBox *apikeyfield = new TextBox(80, sizeOfWind.y/2, 430, 14, "");

        float color_of_buttons[4] = {0.5f, 0.5f, 0.3f, 1.0f};

        Button *donebutton = new Button(sizeOfWind.x/2-70-20, 200, 70, 40, color_of_buttons, "Done");
        donebutton->setOnClick(doneButtonFunc);

        Button *exitaskerbutton = new Button(sizeOfWind.x/2+20, 200, 70, 40, color_of_buttons, "Exit");
        exitaskerbutton->setOnClick(exitButtonFunc);

        mainWindow.addChild(apikeyfield);
        mainWindow.addChild(welcometext);
        mainWindow.addChild(donebutton);
        mainWindow.addChild(exitaskerbutton);

        while(!mainWindow.isClosed() && !askerDone){
            mainWindow.draw();
        }

        api_key = apikeyfield->getText();
        mainWindow.clear();

        delete welcometext;
        delete apikeyfield;
        delete donebutton;
        delete exitaskerbutton;
    }

    {
        int pid = fork();
        if (pid == 0)
        {
            // We are in the child process, execute the python command
            execl("/usr/bin/python3", "/usr/bin/python3", "/home/ihor/University/CourseWork/testProject/main.py", nullptr);
            // If execl returns, there was an error
            // Exit child process
            exit(1);
        }
        mainWindow.setTitle("ChatGPTGUI");

        string text_of_label = "Your chat with bot";
        Label *welcometext = new Label(sizeOfWind.x/2-8*text_of_label.size()/2, 500, 250, 20, text_of_label);

        TextBox *chat = new TextBox(100, 150, 400, 350, "");
        chat->setPlaceholder("Here will be your conversation with bot. ");

        TextBox *messageField = new TextBox(100, 100, 400, 40, "");
        messageField->setPlaceholder("Your message: ");

        float color_of_buttons[4] = {0.5f, 0.5f, 0.3f, 1.0f};
        Button *sendmessagebutton = new Button(250, 50, 100, 40, color_of_buttons, "Send message");
        sendmessagebutton->setOnClick(sendMessageFunc);

        std::ofstream giveapi ("api_key.txt");

        giveapi << api_key;

        giveapi.close();

        sendMessage = false;

        mainWindow.addChild(welcometext);
        mainWindow.addChild(chat);
        mainWindow.addChild(messageField);
        mainWindow.addChild(sendmessagebutton);
        while(!mainWindow.isClosed()){
            mainWindow.draw();

            if (sendMessage){
                std::ofstream outfile ("chat.txt");

                outfile << messageField->getText() << std::endl;

                outfile.close();

                sendMessage = false;
            }
        }
    }

    return 0;
}