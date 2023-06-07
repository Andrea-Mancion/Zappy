#!/usr/bin/env python3

import sys
import socket
import time
import pygame

pygame.init()

clock = pygame.time.Clock()

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

def createClock(ai_socket, name):
    serverString = ai_socket.recv(1024).decode()
    if (serverString == "WELCOME\n"):
        ai_socket.send(("TEAMNAME " + name + "\n").encode())
        serverString = ai_socket.recv(1024).decode()
        serverSplit = serverString.split(" ")
        if (serverSplit[0] == "CLIENT_NUM"):
            nbValue = serverSplit[1]
        serverString = ai_socket.recv(1024).decode()
        serverSplit = serverString.split(" ")
        if (serverSplit[0] == "X"):
            mapWidth = serverSplit[1]
        if (serverSplit[2] == "Y"):
            mapHeight = serverSplit[3]
    while not False:
        clock.tick(60)
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

pygame.quit()