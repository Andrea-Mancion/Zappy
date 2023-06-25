#!/usr/bin/env python3
import random
import sys
import socket
import time
import os
import re
import ast


## LOGGING ##
import logging
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)
#############


TotalPlayers = 0

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

def is_array(data):
    data = data.strip()
    if data.startswith('[') and data.endswith(']'):
        return True
    return False

def look(ai_socket):
    cmd = "Look\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print(str(os.getpid()) + " died")
        sys.exit(0)
    elif (rec == None or rec == "ko\n"):
        print(str(os.getpid()) + " Look KO")
    elif (is_array(rec) == True):
        print(str(os.getpid()) + " Look OK")
        print(rec)
        return rec
    else:
        try:
            getBroadcast(ai_socket, rec)
            return rec
        except TypeError:
            print(str(os.getpid()) + " Look KO and get Broadcast KO")
            return rec

def checkTheDirection(ai_socket, direction):
    if direction != "0":
        print(f"I need to continue \"{direction}\"")
        if str(direction) == "1":
            print("Direction 1")
            forward(ai_socket)
        elif str(direction) == "2":
            print("Direction 2")
            forward(ai_socket)
            left(ai_socket)
        elif str(direction) == "3":
            print("Direction 3")
            left(ai_socket)
        elif str(direction) == "4":
            print("Direction 4")
            left(ai_socket)
            forward(ai_socket)
            left(ai_socket)
        elif str(direction) == "5":
            print("Direction 5")
            left(ai_socket)
            left(ai_socket)
        elif str(direction) == "6":
            print("Direction 6")
            right(ai_socket)
            forward(ai_socket)
            right(ai_socket)
        elif str(direction) == "7":
            print("Direction 7")
            right(ai_socket)
        elif str(direction) == "8":
            print("Direction 8")
            forward(ai_socket)
            right(ai_socket)
        else:
            print("There is no direction")
        time.sleep(5)


def getBroadcast(ai_socket, message):
    print("Voici mon message " + str(message))
    message_split = message.split(" ")
    for i in range(len(message_split)):
        print("Element from the broadcast: " + str(message_split[i]))
        if (message_split[i] == "message"):
            checkTheDirection(ai_socket, message_split[i + 1].split(",")[0])


def forward(ai_socket):
    print(str(os.getpid()) + " Command: Forward")
    cmd = "Forward\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print(str(os.getpid()) + " died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print(str(os.getpid()) + " Forward OK")
    else:
        try:
            getBroadcast(ai_socket, rec)
        except TypeError:
            print(str(os.getpid()) + " Forward KO and get Broadcast KO")


def right(ai_socket):
    print(str(os.getpid()) + " Command: Right")
    cmd = "Right\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print(str(os.getpid()) + " died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print(str(os.getpid()) + " Right OK")
    else:
        try:
            getBroadcast(ai_socket, rec)
        except TypeError:
            print(str(os.getpid()) + " Right KO and get Broadcast KO")


def left(ai_socket):
    print(str(os.getpid()) + " Command: Left")
    cmd = "Left\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "dead\n"):
        print(str(os.getpid()) + " died")
        sys.exit(0)
    elif (rec == "ok\n"):
        print(str(os.getpid()) + " Left OK")
    else:
        try:
            getBroadcast(ai_socket, rec)
        except TypeError:
            print(str(os.getpid()) + " Left KO and get Broadcast KO")

def nbTeams(ai_socket):
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

def broadcast(ai_socket, message):
    global TotalPlayers
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
    if (TotalPlayers >= 2):
        serverString = ai_socket.recv(2046).decode()
        print("serverString8: " + serverString)
        if (serverString == "dead\n"):
            print("I died")
            sys.exit(0)

def getInventory(ai_socket):
    ai_socket.send(str.encode("Inventory\n"))
    serverString = ai_socket.recv(2046).decode()
    if (serverString == "dead\n"):
        print(str(os.getpid()) + " died")
        sys.exit(0)
    elif (serverString == None or serverString == "ko\n"):
        print(str(os.getpid()) + " can't get my inventory")
    elif (is_array(serverString) == True):
        print(str(os.getpid()) + " get my inventory")
        print(serverString)
    else:
        try:
            getBroadcast(ai_socket, serverString)
        except TypeError:
            print(str(os.getpid()) + " get inventory KO and get Broadcast KO")
    return serverString

def setObjectDown(ai_socket, item):
    print(str(os.getpid()) + " Here's the item i need to drop: " + str(item))
    itemDrop_split = item.split(" ")
    itemsLook = look(ai_socket)
    itemsLook_split = itemsLook[0].split(" ")
    itemsGet = getInventory(ai_socket)
    print(str(os.getpid()) + " Here's my inventory: " + itemsGet)
    itemsGet = itemsGet.strip("[]")
    itemsList = itemsGet.split(", ")
    myInventory = []
    for item2 in itemsList:
        item_split = item2.split()
        myInventory.extend(item_split)
    print(myInventory)
    if (len(itemsLook_split) == 1):
        for i in range(len(myInventory)):
            for element in itemDrop_split:
                if (myInventory[i] == element):
                    if i + 1 < len(myInventory):
                        number = myInventory[i + 1]
                    try:
                        if (int(number) > 0):
                            print(str(os.getpid()) + " element " + element)
                            ai_socket.send(str.encode("Set " + element + "\n"))
                            serverString = ai_socket.recv(2046).decode()
                            print(str(os.getpid()) + " 1 " + serverString)
                            if (serverString == "dead\n"):
                                print(str(os.getpid()) + " died")
                                sys.exit(0)
                            elif (serverString == "ok\n"):
                                print(str(os.getpid()) + " Object set down " + str(element))
                            elif (serverString == "ko\n"):
                                print(str(os.getpid()) + " Object not set down " + str(element))
                                return False
                            else:
                                try:
                                    getBroadcast(ai_socket, serverString)
                                    return False
                                except TypeError:
                                    print(str(os.getpid()) + " Can't get the broadcast")
                                    return False
                        else:
                            print(str(os.getpid()) + " don't have the Resources")
                            return False
                    except ValueError:
                        print("The Server doesn't send the right thing")
                else:
                    print(str(os.getpid()) + " don't have this item")
    return True

def canSetObject(ai_socket, lvl):
    if (lvl == 1):
        if setObjectDown(ai_socket, "linemate") == True:
            return True
        else:
            return False
    elif (lvl == 2):
        if setObjectDown(ai_socket, "linemate deraumere sibur") == True:
            return True
        else:
            return False
    elif (lvl == 3):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
        else:
            return False
    elif (lvl == 4):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
        else:
            return False
    elif (lvl == 5):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "menidane") == True:
            return True
        else:
            return False
    elif (lvl == 6):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "phiras") == True:
            return True
        else:
            return False
    elif (lvl == 7):
        if setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "linemate") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "deraumere") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "sibur") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "mendiane") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "phiras") == True and setObjectDown(ai_socket, "thystame") == True:
            return True
        else:
            return False

def peopleInCase(ai_socket, lvl):
    time.sleep(5)
    counter = 0
    broadcast(ai_socket, str(os.getpid()) + " Help")
    objectLook = look(ai_socket)
    print(str(os.getpid()) + " Here's what i see: " + str(objectLook))
    objectLook_split = objectLook.split(",")[0].split(" ")
    for element in objectLook_split:
        if (element == "player"):
            counter += 1
    if lvl == 2 and counter >= 2:
        return True
    elif lvl == 3 and counter >= 2:
        return True
    elif lvl == 4 and counter >= 4:
        return True
    elif lvl == 5 and counter >= 4:
        return True
    elif lvl == 6 and counter >= 6:
        return True
    elif lvl == 7 and counter >= 6:
        return True
    return False

def StartElevation(ai_socket, lvl):
    object_look = look(ai_socket)
    object_split = object_look.split(",")[0].split(" ")
    object_split.pop(0)
    print(str(os.getpid()) + " Here's where i am: " + str(object_split) + "\n" + str(len(object_split)))
    if (len(object_split) == 1):
        if canSetObject(ai_socket, lvl) == True:
            if (lvl == 2):
                while (peopleInCase(ai_socket, lvl) == False):
                    print(str(os.getpid()) + " Waiting for people")
            ai_socket.send(str.encode("Incantation\n"))
            serverString = ai_socket.recv(2046).decode()
            if (serverString == "dead\n"):
                print(str(os.getpid()) + " died")
                sys.exit(0)
            elif (serverString != "ko\n"):
                #Recuperer le lvl que le serveur envoie
                print(str(os.getpid()) + " 2 " + serverString)
                serverString = ai_socket.recv(2046).decode()
                print(str(os.getpid()) + " 3 " + serverString)
                if (serverString == "dead\n"):
                    print(str(os.getpid()) + " died")
                    sys.exit(0)
                if (serverString.startswith("Current level:") == True):
                    lvl += 1
                    print(str(os.getpid()) + " Here my new lvl: " + str(lvl))
            else:
                print(str(os.getpid()) + " failed to level-up\n")
        else:
            print(str(os.getpid()) + " Can't level up 'cause i didn't have the ressources")
    return lvl

def canTakeObject(ai_socket):
    objectArray = look(ai_socket)
    print(str(os.getpid()) + " ObjectArray: " + objectArray)
    element_split = objectArray.split(",")[0].split(" ")
    element_split.pop(0)
    if (len(element_split) > 1):
        for item in Ressources:
            for element in element_split:
                if (item == element):
                    print(str(os.getpid()) + " element: " + element)
                    ai_socket.send(str.encode("Take " + element + "\n"))
                    serverString = ai_socket.recv(2046).decode()
                    print(str(os.getpid()) + " Server3: " + serverString)
                    if (serverString == "dead\n"):
                        print(str(os.getpid()) + " I died")
                        sys.exit(0)
                    elif (serverString == "ok\n"):
                        print(str(os.getpid()) + " take the " + element)
                    elif (serverString == "ko\n"):
                        print(str(os.getpid()) + " can't take the " + element)
                    else:
                        try:
                            getBroadcast(ai_socket, serverString)
                        except TypeError:
                            print(str(os.getpid()) + " I can't split the Broadcast")
    else:
        print(str(os.getpid()) + " Can't take object, i'm not in a object case")

def childProcess(name):
    child_socket = socket.socket()
    child_socket.connect((sys.argv[6], int(sys.argv[2])))

    createClock(child_socket, name)
    child_socket.close()

def forkPlayer(ai_socket, name):
    nbValue = nbTeams(ai_socket)
    try:
        if (nbValue > 7):
            ai_socket.send(str.encode("Fork\n"))
            serverSting = ai_socket.recv(1024).decode()
            print("Server2: " + serverSting)
            if (serverSting == "dead\n"):
                print(str(os.getpid()) + " died")
                sys.exit(0)
            elif (serverSting == "ok\n"):
                print("Forking")
                pip = os.fork()
                if (pip == 0):
                    print("I'm the child " + str(os.getpid()))
                    ai_socket.close()
                    childProcess(name)
                    os._exit(0)
            else:
                try:
                    getBroadcast(ai_socket, serverSting)
                except TypeError:
                    print(str(os.getpid()) + " I can't split the Broadcast")
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
        sys.exit(0)
    while not False:
        canTakeObject(ai_socket)
        # add a condition of if there is a new character
        #forkPlayer(ai_socket, name)
        lvl = StartElevation(ai_socket, lvl)
        print(str(os.getpid()) + " current level: " + str(lvl))
        try:
            objectArray = look(ai_socket)
            print(str(os.getpid()) + " ObjectArray2: " + objectArray)
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
        except TypeError:
            print("TypeError 'cause the server doesn't send the right value look")
        except IndexError:
            print("The server send the broadcast message")

def beginning(port, name, machine):
    global TotalPlayers
    ai_socket = socket.socket()
    ai_socket.connect((machine, int(port)))
    TotalPlayers += 1
    print("Connected to server")
    createClock(ai_socket, name)
    ai_socket.close()
    print("Disconnected from server")

def main(ac, av):
    if (ac == 2 and av[1] == "-help"):
        printHelp()
    elif(ac == 7):
        if (av[1] != "-p" or checkNumber(av[2]) == False or av[3] != "-n" or checkString(av[4]) == False or av[5] != "-h"):
            logger.error("Bad arguments")
            printHelp()
            exit(84)
        beginning(av[2], av[4], av[6])
    else:
        logger.error("Bad arguments")
        printHelp()
        exit(84)


if __name__ == "__main__":
   main(len(sys.argv), sys.argv)