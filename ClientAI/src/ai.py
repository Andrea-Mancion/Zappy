##
## EPITECH PROJECT, 2023
## ai.py
## File description:
## ai
##

import sys

def printHelp():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

def main(ac, av):
    if (ac == 2 and av[1] == "-help"):
        printHelp()


if __name__ == "__main__":
   main(len(sys.argv), sys.argv)