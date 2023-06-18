#!/usr/bin/env python3
import random
import sys
import socket
import time
import os

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
    if (rec == "ok\n"):
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
    if (rec == "ok\n"):
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
    if (rec == "ok\n"):
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
    if (rec == None):
        print("Look KO")
    else:
        print("Look OK")
        return rec

def nbTeams(ai_socket, name):
    ai_socket.send(str.encode("Connect_nbr\n"))
    nbValue = ai_socket.recv(1024).decode()
    print("value: " + nbValue)
    return nbValue

def setObjectDown(ai_socket, item):
    # NE PAS OUBLIER DE VERIFIER SI ON POSSEDE BIEN L'OBJET QU'ON VEUT POSER
    # REFLECHIR A COMMENT SAVOIR QUELLE OBJET DEPOSER (PS: Grace au lvl et au 2ème paramètre)
    # Utiliser la function look pour recuperer les informations des case et split sur les virgules
    # Voici la variable qui va contenir les données du look
    itemsLook = []
    itemsLook_split = itemsLook[0].split(" ")
    # Voici la variable qui va contenir les données du inventory
    itemsGet = []
    # Check si on est bien seul et sans object sur la case (grace au split)
    if (len(itemsLook_split) == 1):
        for element in itemsGet:
            if (element == item):
                print("item " + item)
                ai_socket.send(str.encode("Set " + item + "\n"))
                serverString = ai_socket.recv(2046).decode()
                print("1 " + serverString)
                if (serverString == "ok"):
                    print("Object set down")
                else:
                    print("Object not set down")
                break

# Function to call when we need to Start the elevation

def canSetObject(ai_socket, lvl):
    if (lvl == 1):
        setObjectDown(ai_socket, "linemate")
    elif (lvl == 2):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "sibur")
    elif (lvl == 3):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "phiras")
        setObjectDown(ai_socket, "phiras")
    elif (lvl == 4):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "phiras")
    elif (lvl == 5):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "mendiane")
        setObjectDown(ai_socket, "mendiane")
        setObjectDown(ai_socket, "menidane")
    elif (lvl == 6):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "phiras")
    elif (lvl == 7):
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "linemate")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "deraumere")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "sibur")
        setObjectDown(ai_socket, "mendiane")
        setObjectDown(ai_socket, "mendiane")
        setObjectDown(ai_socket, "phiras")
        setObjectDown(ai_socket, "phiras")
        setObjectDown(ai_socket, "thystame")

def StartElevation(ai_socket, lvl):
    # Recuperer les élements de la fonction look pour check si on est sur une case vide
    # Voici la variable qui va recuperer le tableau
    object_look = []
    object_split = object_look[0].split(" ")
    if (len(object_split) == 1):
        # Appeler la fonction qui va permettre de faire le set Object down avec en paramettre la socket et le lvl
        ai_socket.send(str.encode("Incantation\n"))
        serverString = ai_socket.recv(2046).decode()
        if (serverString != "ko\n"):
            #Recuperer le lvl que le serveur envoie
            print(serverString)
            lvl += 1
            print("Here my new lvl: " + lvl)
    return lvl

def canTakeObject(ai_socket):
    # Faire la condition pour check si quand on look on est sur un objet (n'importe lequel, et n'importe quelle nombre), si c'est le cas on peut prendre un objet qui est sur cette case
    # Voici la variable objectArray, celui va contenir les objects que nous renvoi la fonction look. (a split)
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
                    if (serverString == "ok\n"):
                        print("I take the " + element)
                    else:
                        print("I can't take the " + element)
    else:
        print("Can't take object, i'm not in a object case")

def forkPlayer(ai_socket, name):
    # Si je ne m'abuse the nbValue est le resultat de combien de place il reste dans la team

    nbValue = nbTeams(ai_socket, name)
    if (nbValue > 0):
        ai_socket.send(str.encode("Fork\n"))
        serverSting = ai_socket.recv(1024).decode()
        print("Server2: " + serverSting)
        if (serverSting == "ok\n"):
            print("Forking")
            pip = os.fork()
            if (pip == 0):
                print("I'm the child")

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
    # D'ailleur ne pas oublier de faire ceci que dans le cas ou on veut faire un level up
    lvl = 1
    x = 0
    nbValue, mapWidth, mapHeight = firstCommunication(ai_socket, name)
    while not False:
        canTakeObject(ai_socket)
        objectArray = look(ai_socket)
        print("ObjectArray2: " + objectArray)
        is_empty = not bool(objectArray[1])
        is_empty_too = not bool(objectArray[2])
        if (is_empty == False):
            forward(ai_socket)
            left(ai_socket)
            forward(ai_socket)
        elif (is_empty_too == False):
            forward(ai_socket)
            right(ai_socket)
            forward(ai_socket)
        else:
            forward(ai_socket)
        x += 1
        # add a condition of if there is a new character
        # forkPlayer(ai_socket, name)
        #lvl = StartElevation(ai_socket, lvl)
        if (x == 2):
            break

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
