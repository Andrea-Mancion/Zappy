#!/usr/bin/env python3

import sys
import socket
import time

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

def createClock(ai_socket, name):
    # Avoir le lvl du joueur (recuperer soit au tout debut (base 1) soit a chaque elevation)
    # D'ailleur ne pas oublier de faire ceci que dans le cas ou on veut faire un level up
    lvl = 1
    while not False:
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
