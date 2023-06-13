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

def setObjectDown(ai_socket):
    # NE PAS OUBLIER DE VERIFIER SI ON POSSEDE BIEN L'OBJET QU'ON VEUT POSER
    # REFLECHIR A COMMENT SAVOIR QUELLE OBJET DEPOSER
    # Utiliser la function look pour recuperer les informations des case et split sur les virgules
    # Voici la variable qui va contenir les données du look
    itemsLook = []
    # Check si on est bien seul et sans object sur la case (grace au split)
    if (1):
        ai_socket.send(b"Set Object\n").encode()
        serverString = ai_socket.recv(2046).decode()
        if (serverString == "ok"):
            print("Object set down")
            ai_socket.send(b"drop this object (change it)\n").encode()

def createClock(ai_socket, name):
    while not False:
        setObjectDown(ai_socket)
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
