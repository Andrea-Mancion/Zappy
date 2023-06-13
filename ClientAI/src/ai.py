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
    nbValue, mapWidth, mapHeight = firstCommunication(ai_socket, name)


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
