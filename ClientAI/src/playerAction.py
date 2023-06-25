import logging
import time
from os import getpid


logger = logging.getLogger(str(getpid()))

class PlayerAction:
    def __init__(self, socket, teamNumbers, name):
        self.socket = socket
        self.teamNumbers = teamNumbers
        self.nameTeam = name

    def checkTheDirection(self, direction):
        direction = direction.split(",")[0]
        logger.debug(f"Moving to direction: {direction}")
        if "0" in str(direction):
            logger.debug("Direction 0")
            self.broadcast("I am here")
        elif "1" in str(direction):
            logger.debug("Direction 1")
            self.forward()
        elif "2" in str(direction):
            logger.debug("Direction 2")
            self.forward()
        elif "3" in str(direction):
            logger.debug("Direction 3")
            self.left()
        elif "4" in str(direction):
            logger.debug("Direction 4")
            self.left()
        elif "5" in str(direction):
            logger.debug("Direction 5")
            self.left()
        elif "6" in str(direction):
            logger.debug("Direction 6")
            self.right()
        elif "7" in str(direction):
            logger.debug("Direction 7")
            self.right()
        elif "8" in str(direction):
            logger.debug("Direction 8")
            self.forward()
        else:
            logger.warning("There is no direction")
        self.checkTheDirection("-1")

    def look(self):
        self.socket.send("Look\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            if self.handle_broadcast(msg["broadcast"]):
                return None
        if (msg["response"] == None or msg["response"] == "ko\n"):
            logger.warning("Look KO")
            return None
        msg = msg["response"].replace("[ ", "").replace(" ]", "").split(",")
        return msg

    def canTakeObject(self, ressource):
        repLook = self.look()
        if (repLook == None):
            return False
        repLook = repLook[0].split(" ")
        if (len(repLook) > 0):
            for resource_name, amount in ressource.items():
                if amount == 0:
                    continue
                for element in repLook:
                    if element == "player":
                        continue
                    if element in resource_name or "food" in resource_name:
                        logger.debug(f"Found {element}")
                        self.socket.send("Take " + element + "\n")
                        msg = self.socket.receive()
                        if (msg["broadcast"] != None):
                            if self.handle_broadcast(msg["broadcast"]):
                                return False
                        if (msg["response"] == "ok\n"):
                            logger.debug("take the " + element)
                            return True
                        elif (msg["response"] == "ko\n"):
                            logger.debug("can't take the " + element)
                            return False
        else:
            logger.warn("Can't take object, I'm not in an object case")
            return False

    def forward(self):
        self.socket.send("Forward\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            self.handle_broadcast(msg["broadcast"])
        if (msg["response"] == "ok\n"):
            logger.debug("Forward OK")

    def right(self):
        self.socket.send("Right\n")
        msg = self.socket.receive()
        if msg["broadcast"] != None:
            self.handle_broadcast(msg["broadcast"])
        if (msg["response"] == "ok\n"):
            logger.debug("Right OK")

    def left(self):
        self.socket.send("Left\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            self.handle_broadcast(msg["broadcast"])
        if (msg["response"] == "ok\n"):
            logger.debug("Left OK")

    def getInventory(self):
        self.socket.send("Inventory\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            self.handle_broadcast(msg["broadcast"])
        if (msg["response"] == None or msg["response"] == "ko\n"):
            logger.warning("can't get my inventory")
            return None
        # logger.info("I get my inventory")
        return msg["response"]

    def setObjectDown(self, item):
        itemDrop_split = item.split(" ")
        repLook = self.look()
        repLook = repLook[0].split(" ")
        itemsGet = self.getInventory()
        itemsGet = itemsGet.replace("[ ", "").replace(" ]", "")
        itemsList = itemsGet.split(", ")
        myInventory = []
        for item2 in itemsList:
            item_split = item2.split()
            myInventory.extend(item_split)
        print(myInventory)
        for i in range(len(myInventory)):
            for element in itemDrop_split:
                if (myInventory[i] == element):
                    if i + 1 < len(myInventory):
                        number = myInventory[i + 1]
                    try:
                        if (int(number) > 0):
                            self.socket.send("Set " + element + "\n")
                            msg = self.socket.receive()
                            if (msg["broadcast"] != None):
                                self.handle_broadcast(msg["broadcast"])
                            if (msg == "ok\n"):
                                logger.info(f"Object set down {element}")
                            elif (msg == "ko\n"):
                                logger.warning(f"Object not set down {element}")
                                return False
                        else:
                            logger.warning("don't have the Resources")
                            return False
                    except ValueError:
                        logger.warning("The Server doesn't send the right thing")
        return True

    def canSetObject(self, itemlist):
        for item, amount in itemlist.items():
            for _ in range(amount):
                if (self.setObjectDown(item) == False):
                    return False
        return True

    def nbTeams(self):
        self.socket.send("Connect_nbr\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            self.handle_broadcast(msg["broadcast"])
        try:
            return int(msg["response"])
        except Exception as e:
            logger.warning(f"The server doesn't send the right number of teams: {e}")

    def broadcast(self, message):
        self.socket.send("Broadcast " + message + "\n")
        msg = self.socket.receive()
        if (msg["broadcast"] != None):
            self.handle_broadcast(msg["broadcast"])
        if (msg["response"] == "ok\n"):
            logger.info("Broadcast " + message + " OK")
        else:
            logger.warning("Broadcast KO") 

    def peopleInCase(self, level):
        time.sleep(2)
        counter = 0
        self.broadcast("level up help")
        repLook = self.look()
        repLook = repLook[0].split(" ")
        for element in repLook:
            if (element == "player"):
                counter += 1
        if level == 1 and counter >= 2:
            return True
        elif level == 2 and counter >= 2:
            return True
        elif level == 3 and counter >= 4:
            return True
        elif level == 4 and counter >= 4:
            return True
        elif level == 5 and counter >= 6:
            return True
        elif level == 6 and counter >= 6:
            return True
        return False

    def startElevation(self, resource, level):
        repLook = self.look()
        repLook = repLook[0].split(" ")
        logger.info(f"Atempting to level-up to {level + 2}")
        if self.canSetObject(resource) == True:
            if (level >= 1):
                self.broadcast("count yourself")
                self.look()
                while (self.peopleInCase(level) == False):
                    logger.info("Waiting for people")
            self.socket.send("Incantation\n")
            msg = self.socket.receive()
            if (msg["broadcast"] != None):
                self.handle_broadcast(msg["broadcast"])
            if (msg["response"] != "ko\n"):
                #Recuperer le lvl que le serveur envoie
                logger.debug(f"First message from server {msg}")
                msg = self.socket.receive()
                logger.debug(f"Second message from server {msg}")
                if (msg["broadcast"] != None):
                    self.handle_broadcast(msg["broadcast"])
                if (msg["response"].startswith("Current level:") == True):
                    level += 1
                    logger.info(f"Here my new lvl: {level + 1}")
                    self.broadcast("level up done")
            else:
                logger.warning("failed to level-up\n")
        else:
            logger.warning("Can't level up 'cause i didn't have the ressources")
        return level

    def move(self, movement):
        if movement == "forward":
            self.forward()
        elif movement == "left":
            self.left()
        elif movement == "right":
            self.right()
        else:
            logger.warning(f"Wrong movement: {movement}")

    def look_for(self, item: str):
        try:
            respLook = self.look()
            logger.debug(f"resplook: {respLook}, his length: {len(respLook)}")
            count_per_tile = []
            for tile in range(len(respLook)):
                count_per_tile.append(0)
                for element in respLook[tile].split(" "):
                    if item in element:
                        count_per_tile[tile] += 1
            if count_per_tile[0] > 0:
                return 0
            if max(count_per_tile) == 0:
                return -1
            return count_per_tile.index(max(count_per_tile))
        except:
            logger.warning("Error in the look for")

    def handle_broadcast(self, msg):
        data = {
            "origin": msg.split(" ")[1],
            "content": msg.split(", ")[1]
        }
        if data["content"] == "count yourself\n":
            logger.debug(f"count yourself from {data['origin']}")
            self.broadcast("I am here")
        elif data["content"] == "I am here\n":
            logger.debug(f"I am here from {data['origin']}")
            return False
        elif data["content"] == "level up help\n":
            logger.debug(f"level up help from {data['origin']}")
            self.checkTheDirection(data["origin"])
            return True
        elif data["content"] == "level up done\n":
            logger.debug(f"Elevation done from {data['origin']}")
            return False
        return False
