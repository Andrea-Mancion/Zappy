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

def canTakeObject(ai_socket):
    # Faire la condition pour check si quand on look on est sur un objet (n'importe lequel, et n'importe quelle nombre), si c'est le cas on peut prendre un objet qui est sur cette case
    # Voici la variable objectArray, celui va contenir les objects que nous renvoi la fonction look. (a split)
    objectArray = []
    element_split = objectArray[0].split(" ")
    if (element_split > 1):
        ai_socket.send(str.encode("Take object\n"))
        serverString = ai_socket.recv(2046).decode()
        if (serverString == "ok\n"):
            print("I take the object")
        else:
            print("I can't take the object")
    else:
        print("Can't take object, i'm not in a object case")

def createClock(ai_socket, name):
    while not False:
        canTakeObject(ai_socket)
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
