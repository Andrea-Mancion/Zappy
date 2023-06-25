import logging
import os
from playerAction import PlayerAction

logger = logging.getLogger(str(os.getpid()))

class Player:
    def __init__(self, socket, name, teamNumber):
        self.level = 0
        self.teamNumbers = teamNumber
        self.food = 0
        self.actions = PlayerAction(socket, self.teamNumbers, name)
        self.socket = socket
        self.socket.receive()
        self.socket.send(name + '\n')
        msg = self.socket.receive()
        if msg["response"] == "ko":
            logger.error("Team name already taken, exiting...")
            exit(84)
        logger.debug(f"msg: {msg}")
        msg = msg["response"].split('\n')
        self.map = {
            "nbValue": msg[0],
            "Width": msg[1].split(" ")[0],
            "Height": msg[1].split(" ")[1]
        }
        self.resources = [
            "food",
            "linemate",
            "deraumere",
            "sibur",
            "mendiane",
            "phiras",
            "thystame"
        ]
        self.need_resources = [
            {
                "linemate": 1,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            {
                "linemate": 1,
                "deraumere": 1,
                "sibur": 1,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            {
                "linemate": 2,
                "deraumere": 0,
                "sibur": 1,
                "mendiane": 0,
                "phiras": 2,
                "thystame": 0
            },
            {
                "linemate": 1,
                "deraumere": 1,
                "sibur": 2,
                "mendiane": 0,
                "phiras": 1,
                "thystame": 0
            },
            {
                "linemate": 1,
                "deraumere": 2,
                "sibur": 1,
                "mendiane": 3,
                "phiras": 0,
                "thystame": 0
            },
            {
                "linemate": 1,
                "deraumere": 2,
                "sibur": 3,
                "mendiane": 0,
                "phiras": 1,
                "thystame": 0
            },
            {
                "linemate": 2,
                "deraumere": 2,
                "sibur": 2,
                "mendiane": 2,
                "phiras": 2,
                "thystame": 1
            }
        ]
        self.moves = [
            [],
            ["forward", "left", "forward"],
            ["forward"],
            ["forward", "right", "forward"],
            ["forward", "forward", "left", "forward", "forward"],
            ["forward",  "forward", "left", "forward"],
            ["forward", "forward"],
            ["forward", "forward", "right", "forward"],
            ["forward", "forward", "right", "forward", "forward"],
            ["forward", "forward", "forward", "left", "forward", "forward", "forward"],
            ["forward", "forward", "forward", "left", "forward", "forward"],
            ["forward", "forward", "forward", "left", "forward"],
            ["forward", "forward", "forward"],
            ["forward", "forward", "forward", "right", "forward"],
            ["forward", "forward", "forward", "right", "forward", "forward"],
            ["forward", "forward", "forward", "right", "forward", "forward", "forward"]
        ]

    def checkIfEnoughFood(self):
        inventory = self.actions.getInventory()
        inventory = inventory.replace("[ ", "").replace(" ]", "").split(", ")
        myInventory = {}
        for item in inventory:
            item = item.split()
            myInventory[item[0]] = int(item[1])

        for itemInventory, inventoryAmount in myInventory.items():
            if itemInventory == "food" and inventoryAmount <= 5:
                # self.forkPlayer()
                logger.debug(f"We have {inventoryAmount} food")
                return True
        return False

    def checkInInventory(self):
        inventory = self.actions.getInventory()
        inventory = inventory.replace("[ ", "").replace(" ]", "").split(", ")
        myInventory = {}
        for item in inventory:
            item = item.split()
            myInventory[item[0]] = int(item[1])
        logger.debug(f"myInventory: {myInventory}")
        logger.debug(f"need: {self.need_resources[self.level]}")

        for itemInventory, inventoryAmount in myInventory.items():
            if itemInventory == "food":
                continue
            if inventoryAmount >= self.need_resources[self.level][itemInventory]:
                logger.debug(f"Item {itemInventory} is enough")
                continue
            else:
                logger.debug(f"Item {itemInventory} is not enough")
                return True
        return False

    def run(self):
        logger.debug("Run")
        if self.map["nbValue"] == 0:
            logger.error("No more place in the server")
            exit(0)
        while True:
            while (self.checkIfEnoughFood() == True):
                repTile = self.actions.look_for("food")
                if repTile == -1:
                    self.actions.forward()
                for move in self.moves[repTile]:
                    self.actions.move(move)
                self.actions.canTakeObject({"food": 5})

            if self.checkInInventory() is False:
                self.level = self.actions.startElevation(self.need_resources[self.level], self.level)
            else:
                for resource, amount in self.need_resources[self.level].items():
                    if amount == 0:
                        continue
                    for _ in range(amount):
                        repTile = self.actions.look_for(resource)
                        logger.debug(f"moving to tile: {repTile}")
                        if repTile == -1:
                            self.actions.forward()
                            continue
                        logger.debug(f"moves: {self.moves[repTile]}")
                        for move in self.moves[repTile]:
                            self.actions.move(move)
                        self.actions.canTakeObject(self.need_resources[self.level])
            # if self.teamNumbers <= self.level + 1:
            #     self.forkPlayer()

    # def forkPlayer(self):
    #     try:
    #         if (self.actions.nbTeams() > 0):
    #             self.socket.send("Fork\n")
    #             msg = self.socket.receive()
    #             if (msg == "ok\n"):
    #                 logger.info("Creating child")
    #                 pip = os.fork()
    #                 if (pip == 0):
    #                     logger.debug("I'm the child")
    #                     os.system("zappy_ai.py -p " + str(self.port) + " -n " + self.team + " -h " + self.host)
    #                     exit(0)
    #             else:
    #                 try:
    #                     self.getBroadcast(msg)
    #                 except Exception as e:
    #                     raise f"Broadcast failed: {e}"
    #     except Exception as e:
    #         logger.warning(f"Caught exception: {e}")