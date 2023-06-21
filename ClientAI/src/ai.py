#!/usr/bin/env python3
import random
import sys
import socket
import time
import os
import re

Ressources = [
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
]

max_ressources = {"linemate": 9, "deraumere": 8, "sibur": 10, "mendiane": 5, "phiras": 6, "thystame": 1}

need_ressources = [
    {
        "linemate": 1,
        "deraumere": 0,
        "sibur": 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 1,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 2,
        "deraumere": 0,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 2,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 1,
        "sibur": 2,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 2,
        "sibur": 1,
        "mendiane": 3,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 2,
        "sibur": 3,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "linemate": 2,
        "deraumere": 2,
        "sibur": 2,
        "mendiane": 2,
        "phiras": 2,
        "thystame": 1
    }
]

def printHelp():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

def checkNumber(number):
    try:
        int(number)
        return True
    except ValueError:
        return False

def checkString(string):
    if (string == ""):
        return False
    return True

def forward(ai_socket):
    print("Command: Forward")
    cmd = "Forward\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print("Forward OK")
    else:
        print("Forward KO")
    print(rec)


def right(ai_socket):
    print("Command: Right")
    cmd = "Right\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print("Right OK")
    else:
        print("Right KO")
    print(rec)


def left(ai_socket):
    print("Command: Left")
    cmd = "Left\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print("Left OK")
    else:
        print("Left KO")
    print(rec)


def look(ai_socket):
    cmd = "Look\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (rec == None):
        print("Look KO")
    else:
        print("Look OK")
        print(rec)
        return rec

def broadcast(ai_socket, message):
    cmd = "Broadcast " + message + "\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print("Broadcast " + message + " OK")
    else:
        print("Broadcast KO")
    print(rec)
    serverString = ai_socket.recv(2046).decode()
    print("serverString8: " + serverString)
    if (serverString == "dead\n"):
        print("I died")
        sys.exit(0)

def nbTeams(ai_socket, name):
    ai_socket.send(str.encode("Connect_nbr\n"))
    nbValue = ai_socket.recv(1024).decode()
    print("value: " + nbValue)
    if (nbValue == "dead\n"):
        print("I died")
        sys.exit(0)
    try:
        return int(nbValue)
    except ValueError:
        print("The server doesn't send the right number of teams")

def getInventory(ai_socket):
    ai_socket.send(str.encode("Inventory\n"))
    serverString = ai_socket.recv(2046).decode()
    if (serverString == "dead\n"):
        print("I died")
        sys.exit(0)
    elif (serverString != "ko\n"):
        print("I get my inventory")
        print(serverString)
    else:
        print("I can't get my inventory")
    return serverString

def getInventory(ai_socket):
    ai_socket.send(str.encode("Inventory\n"))
    serverString = ai_socket.recv(2046).decode()
    if (serverString != "ko\n"):
        print("I get my inventory")
    else:
        print("I can't get my inventory")
    return serverString

def setObjectDown(ai_socket, item):
    itemsLook = look(ai_socket)
    itemsLook_split = itemsLook[0].split(" ")
    itemsGet = getInventory(ai_socket)
    print("Here's my inventory: " + itemsGet)
    itemsGet = itemsGet.strip("[]")
    itemsList = itemsGet.split(", ")
    myInventory = []
    for item2 in itemsList:
        item_split = item2.split()
        myInventory.extend(item_split)
    print(myInventory)
    if (len(itemsLook_split) == 1):
        for i in range(len(myInventory)):
            if (myInventory[i] == item):
                if i + 1 < len(myInventory):
                    number = myInventory[i + 1]
                try:
                    if (int(number) > 0):
                        print("item " + item)
                        ai_socket.send(str.encode("Set " + item + "\n"))
                        serverString = ai_socket.recv(2046).decode()
                        print("1 " + serverString)
                        if (serverString == "dead\n"):
                            print("I died")
                            sys.exit(0)
                        elif (serverString == "ok\n"):
                            print("Object set down")
                            return True
                        else:
                            print("Object not set down")
                            return False
                except ValueError:
                    print("The Server doesn't send the right thing")
            else:
                print("I don't have this item")

def canSetObject(ai_socket, lvl):
    if (lvl == 1):
        if setObjectDown(ai_socket, "linemate") == True:
            return True
    elif (lvl == 2):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True:
            return True
    elif (lvl == 3):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
    elif (lvl == 4):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
    elif (lvl == 5):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "menidane") == True:
            return True
    elif (lvl == 6):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
    elif (lvl == 7):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "thystame") == True:
            return True

def StartElevation(ai_socket, lvl):
    object_look = look(ai_socket)
    object_split = object_look.split(",")[0].split(" ")
    object_split.pop(0)
    print("Here's where i am: " + str(object_split) + "\n" + str(len(object_split)))
    if (len(object_split) == 1):
        if canSetObject(ai_socket, lvl) == True:
            ai_socket.send(str.encode("Incantation\n"))
            serverString = ai_socket.recv(2046).decode()
            if (serverString == "dead\n"):
                print("I died")
                sys.exit(0)
            elif (serverString != "ko\n"):
                #Recuperer le lvl que le serveur envoie
                print("2 " + serverString)
                serverString = ai_socket.recv(2046).decode()
                print("3 " + serverString)
                if (serverString == "dead\n"):
                    print("I died")
                    sys.exit(0)
                lvl += 1
                print("Here my new lvl: " + str(lvl))
            else:
                print("I failed to level-up\n")
    return lvl

def canTakeObject(ai_socket):
    objectArray = look(ai_socket)
    print("ObjectArray: " + objectArray)
    element_split = objectArray.split(",")[0].split(" ")
    element_split.pop(0)
    if (len(element_split) > 1):
        for item in Ressources:
            for element in element_split:
                if (item == element):
                    print("element: " + element)
                    ai_socket.send(str.encode("Take " + element + "\n"))
                    serverString = ai_socket.recv(2046).decode()
                    print("Server3: " + serverString)
                    if (serverString == "dead\n"):
                        print("I died")
                        sys.exit(0)
                    elif (serverString == "ok\n"):
                        print("I take the " + element)
                    else:
                        print("I can't take the " + element)
    else:
        print("Can't take object, i'm not in a object case")

def childProcess(ai_socket, name):
    createClock(ai_socket, name)
    ai_socket.close()
    print("The child is dead")

def forkPlayer(ai_socket, name):
    nbValue = nbTeams(ai_socket, name)
    try:
        if (nbValue > 0):
            ai_socket.send(str.encode("Fork\n"))
            serverSting = ai_socket.recv(1024).decode()
            print("Server2: " + serverSting)
            if (serverSting == "dead\n"):
                print("I died")
                sys.exit(0)
            elif (serverSting == "ok\n"):
                print("Forking")
                pip = os.fork()
                if (pip == 0):
                    print("I'm the child")
    except TypeError:
        print("TypeError 'cause the server doesn't send the right value team")

def firstCommunication(ai_socket, name):
    serverString = ai_socket.recv(2048).decode()
    print(serverString)
    ai_socket.send(str.encode(name + "\n"))
    serverString = ai_socket.recv(2048).decode()
    if (serverString == "ko\n"):
        print("Bad team name")
        exit(84)
    nbValue = serverString.split("\n")[0]
    print("number of slots unused: " + nbValue)
    serverSplit = serverString.split("\n")[1].split(" ")
    mapWidth = serverSplit[0]
    mapHeight = serverSplit[1]
    print(mapWidth + " " + mapHeight)
    return nbValue, mapWidth, mapHeight

def createClock(ai_socket, name):
    # Avoir le lvl du joueur (recuperer soit au tout debut (base 1) soit a chaque elevation)
    lvl = 1
    nbValue, mapWidth, mapHeight = firstCommunication(ai_socket, name)
    if (nbValue == 0):
        print("No more place in the server")
        exit(0)
    while not False:
        canTakeObject(ai_socket)
        # add a condition of if there is a new character
        #forkPlayer(ai_socket, name)
        lvl = StartElevation(ai_socket, lvl)
        print("my current level: " + str(lvl))
        objectArray = look(ai_socket)
        print("ObjectArray2: " + objectArray)
        is_empty = not bool(objectArray.split(",")[1])
        is_empty_too = not bool(objectArray.split(",")[2])
        if (is_empty == False):
            forward(ai_socket)
            left(ai_socket)
            forward(ai_socket)
            canTakeObject(ai_socket)
        elif (is_empty_too == False):
            forward(ai_socket)
        else:
            forward(ai_socket)
            right(ai_socket)
            forward(ai_socket)

def beginning(port, name, machine):
    ai_socket = socket.socket()
    ai_socket.connect((machine, int(port)))
    print("Connected to server")
    createClock(ai_socket, name)
    ai_socket.close()
    print("Disconnected from server")

def main(ac, av):
    if (ac == 2 and av[1] == "-help"):
        printHelp()
    elif(ac == 7):
        if (av[1] != "-p" or checkNumber(av[2]) == False or av[3] != "-n" or checkString(av[4]) == False or av[5] != "-h"):
            print("Bad arguments")
            printHelp()
            exit(84)
        beginning(av[2], av[4], av[6])
    else:
        print("Bad arguments")
        printHelp()
        exit(84)


if __name__ == "__main__":
   main(len(sys.argv), sys.argv)
