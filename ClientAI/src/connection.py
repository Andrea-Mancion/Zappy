import socket
import logging
from os import getpid


logger = logging.getLogger(str(getpid()))

class Connexion:
    def __init__(self, host, port):
        self.host = host
        self.port = int(port)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))
        logger.info("Connection established")

    def send(self, msg):
        # logger.debug(f"Sending message '{msg}'")
        try:
            self.socket.send(str.encode(msg))
        except:
            logger.critical("Error while sending message")
            exit(1)
        else:
            return True

    def receive(self):
        # logger.debug("Waiting for message")
        msg = {
            "response": None,
            "broadcast": None
        }
        try:
            msg["response"] = self.socket.recv(2048).decode()
        except:
            logger.critical("Error while receiving message")
            exit(1)
        else:
            if (msg["response"] == "dead\n"):
                logger.info("I died, exiting...")
                exit(0)
            elif ("message" in msg["response"]):
                msg["broadcast"] = msg["response"]
                msg["response"] = self.receive()["response"]
                logger.debug(f"Broadcast message: {msg}")
            return msg

    def close(self):
        if self.socket is None:
            logger.debug("Connection already closed")
            return
        self.socket.close()
        logger.info("Connection closed")
        self.socket = None

    def __del__(self):
        if self.socket is not None:
            self.close()