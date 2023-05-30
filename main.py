import os
import time

import openai

api_key = ""

if os.path.exists('api_key.txt'):
        try:
            f = open('api_key.txt', 'r+')
            text = f.read()
            if len(text)>0:
                api_key = text
            f.close()
            os.remove('api_key.txt')
        except FileNotFoundError:
            print("Error with file")
            exit(1)
else:
    print("Error with file")
    exit(1)

#openai

openai.api_key = (api_key)

startMessage = "Ти чат бот в створеному GUI Ігором. Твоя задача бути іронічним коментатором."

history = []

history.append({"role": "system", "content": startMessage})

def request(cur_history):
    text = ""

    try:
        completion = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        temperature=0.7,
        frequency_penalty=2,
        presence_penalty=1.2,
        messages=cur_history
        )

        text = completion.choices[0].message.content

        cur_history.append(completion.choices[0].message)
        print(cur_history)
    except openai.error.InvalidRequestError:
        text = "Вибачте мене дурненького, але я вимушений забути останній діалог, таяк моя память надто коротка"
        cur_history.clear()
        cur_history.append({"role": "user", "content": startMessage})
    except openai.error.RateLimitError:
        text = "Агов а ну не спіши, і так багато пишеш мені. Почекай троха"
    except openai.error.AuthenticationError:
        text = "Щось не так з АПІ ключем! Зміни його"

    return text

#main processes

counter = 0

while counter < 100000000:
    
    if os.path.exists('chat.txt'):
        try:
            f = open('chat.txt', 'r+')
            text = f.read()
            if len(text)>0:
                history.append({"role": "user", "content": text})
                text = request(history)
                print("Bot: " + text)
            f.close()
            os.remove('chat.txt')
        except FileNotFoundError:
            pass
        counter = 0
    else:
        pass
        # Print a message
        #print('The file does not exist')
    time.sleep(0.1)
    counter += 1



