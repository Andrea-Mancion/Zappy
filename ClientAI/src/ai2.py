import argparse
import logging
import atexit
from os import getpid

from connection import Connexion
from player import Player


logging.basicConfig(level=logging.DEBUG, format='%(filename)s:%(funcName)s():%(lineno)d | %(levelname)s: %(message)s')
logger = logging.getLogger(str(getpid()))

parser = argparse.ArgumentParser(description='Client AI')
parser = argparse.ArgumentParser(add_help=False)
parser.add_argument('-p', type=int, metavar="4242", help='Port number')
parser.add_argument('-n', type=str, metavar="team1", help='Team name')
parser.add_argument('-h', type=str, metavar="127.0.0.1", help='Host name')
parser.add_argument('-help', "--help", action='help', help='Show this help message and exit')

teamNumber = 0

def main():
    global teamNumber
    args = parser.parse_args()
    if args.p is None or args.n is None or args.h is None:
        logger.error("Missing arguments, exiting...")
        exit(84)
    socket = Connexion(args.h, args.p)
    teamNumber += 1
    atexit.register(socket.close)
    player = Player(socket, args.n, teamNumber)
    logger.debug("Player created")
    player.run()
    socket.close()
    exit(0)

if __name__ == "__main__":
    main()