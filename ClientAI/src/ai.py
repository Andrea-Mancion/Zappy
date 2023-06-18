#!/usr/bin/env python3
import random
import sys
import socket
import time
import os

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
    if (len(element_split) > 1):
        for item in Ressources:
            for element in element_split:
                if (item == element):
                    ai_socket.send(str.encode("Take " + element + "\n"))
                    serverString = ai_socket.recv(2046).decode()
                    if (serverString == "ok\n"):
                        print("I take the object")
                    else:
                        print("I can't take the object")
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

def createClock(ai_socket, name):
    serverSting = ai_socket.recv(2046).decode()
    if (serverSting == "WELCOME\n"):
        ai_socket.send(str.encode(name + "\n"))
    serverSting = ai_socket.recv(2046).decode()
    print("Server1: " + serverSting)
    while not False:
        canTakeObject(ai_socket)
        forkPlayer(ai_socket, name)
        break
        # add a condition of if there is a new character

        
def nbTeams(ai_socket, name):
    ai_socket.send(str.encode("Connect_nbr\n"))
    nbValue = ai_socket.recv(1024).decode()
    print(nbValue)
    return nbValue


def beginning(port, name, machine):
    ai_socket = socket.socket()
    ai_socket.connect((machine, int(port)))
    print("Connected to server")
    createClock(ai_socket, name)
    move_ia(ai_socket)
    ai_socket.close()
    print("Disconnected from server")


def move_ia(ai_socket):
    while not False:
        time.sleep(0.5)
        value = random.randint(0, 2)
        if value == 0:
            forward(ai_socket)
        if value == 1:
            right(ai_socket)
        if value == 2:
            left(ai_socket)
        if value == 4:
            look(ai_socket)


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
        print("Forward OK")
    else:
        print("Forward KO")
    print(rec)


def left(ai_socket):
    print("Command: Left")
    cmd = "Left\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == "ok\n"):
        print("Forward OK")
    else:
        print("Forward KO")
    print(rec)


def look(ai_socket):
    print("Command: Look")
    cmd = "Look\n"
    cmd = cmd.encode()
    ai_socket.send(cmd)
    rec = ai_socket.recv(1024)
    rec = rec.decode()
    if (rec == None):
        print("Look KO")
    else:
        print("Look OK")
    print(rec)

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
