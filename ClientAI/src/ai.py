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

def createClock(ai_socket, name):
    lvl = 1
    while not False:
        lvl = StartElevation(ai_socket, lvl)
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
