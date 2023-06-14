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

def StartElevation(ai_socket):
    #Check if dans l'inventaire on possède bien les ressources nécessaires pour l'incantation
    #Si oui, on drop les objets (dans une case vide de préférence), puis start l'incantation
    if (1):
        ai_socket.send(b"Icantation\n").encode()
        serverString = ai_socket.recv(2046).decode()
        if (serverString != "ko\n"):
            #Recuperer le lvl que le serveur envoie
            lvl += 1
            print("Here my new lvl: " + lvl)

def createClock(ai_socket, name):
    while not False:
        StartElevation(ai_socket)
        break


def beginning(port, name, machine):
    print("Port: " + port)
    print("Name: " + name)
    print("Machine: " + machine)
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
