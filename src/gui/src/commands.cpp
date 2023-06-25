/*
** EPITECH PROJECT, 2023
** commands.cpp
** File description:
** commands
*/

#include "../inc/gui.hpp"

Commands::Commands()
{
    this->_cmdList["msz"] = &Commands::msz;
    this->_cmdList["bct"] = &Commands::bct;
    this->_cmdList["tna"] = &Commands::tna;
    this->_cmdList["pnw"] = &Commands::pnw;
    this->_cmdList["ppo"] = &Commands::ppo;
    this->_cmdList["plv"] = &Commands::plv;
    this->_cmdList["pin"] = &Commands::pin;
    this->_cmdList["pex"] = &Commands::pex;
    this->_cmdList["pbc"] = &Commands::pbc;
    this->_cmdList["pic"] = &Commands::pic;
    this->_cmdList["pie"] = &Commands::pie;
    this->_cmdList["pfk"] = &Commands::pfk;
    this->_cmdList["pdr"] = &Commands::pdr;
    this->_cmdList["pgt"] = &Commands::pgt;
    this->_cmdList["pdi"] = &Commands::pdi;
    this->_cmdList["enw"] = &Commands::enw;
    this->_cmdList["ebo"] = &Commands::ebo;
    this->_cmdList["edi"] = &Commands::edi;
    this->_cmdList["sgt"] = &Commands::sgt;
    this->_cmdList["sst"] = &Commands::sst;
    this->_cmdList["seg"] = &Commands::seg;
    this->_cmdList["smg"] = &Commands::smg;
    this->_cmdList["suc"] = &Commands::suc;
    this->_cmdList["sbp"] = &Commands::sbp;
    this->_cmdList["WELCOME"] = &Commands::welcome;
}

bool Commands::doCommand(Map *map, std::vector<std::vector<std::string>> cmd, Server server)
{
    bool result = true;

    for (int j = 0; j < cmd.size(); j++) {
        bool(Commands::*ptr)(Map *map, std::vector<std::string> cmd, Server server);
        if (this->_cmdList.find(cmd[j][0]) == this->_cmdList.end())
            throw ServerWarning(std::cerr, "Warning: '" + cmd[j][0] + "': unknow command");
        try {
            ptr = this->_cmdList[cmd[j][0]];
            (this->*ptr)(map, cmd[j], server);

        } catch (ServerWarning &e) {
            std::cerr << e.what() << std::endl;
            result = false;
        }
    }
    return result;
}

//map size
bool Commands::msz(Map *map, std::vector<std::string> cmd, Server server)
{
    Inventory *inv;
    std::vector<Inventory> invLine;
    std::vector<std::vector<Inventory>> inventory;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    map->setDimension(std::atoi(cmd[1].c_str()), std::atoi(cmd[2].c_str()));
    for (int i = 0; i < map->getDimension().second; i++) {
        inv = new Inventory();
        invLine.push_back(*inv);
    }
    for (int i = 0; i < map->getDimension().first; i++)
        inventory.push_back(invLine);
    map->setTiles(inventory);
    printf("GUI-COMMAND: Update map size to %s %s\n", cmd[1].c_str(), cmd[2].c_str());
    return true;
}

//content of a tile
bool Commands::bct(Map *map, std::vector<std::string> cmd, Server server)
{
    Inventory *inv;
    int quantity = 0;

    if (cmd.size() == 10) {
        for (size_t i = 1; i < cmd.size(); i++)
            for (size_t j = 0; j < cmd[i].length(); j++)
                if (!std::isdigit(cmd[i][j]))
                    throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
        inv = map->getTile(atoi(cmd[1].c_str()), atoi(cmd[2].c_str()));
        inv->setItem(Stones::FOOD, atoi(cmd[3].c_str()));
        inv->setItem(Stones::LINEMATE, atoi(cmd[4].c_str()));
        inv->setItem(Stones::DERAUMERE, atoi(cmd[5].c_str()));
        inv->setItem(Stones::SIBUR, atoi(cmd[6].c_str()));
        inv->setItem(Stones::MENDIANE, atoi(cmd[7].c_str()));
        inv->setItem(Stones::PHIRAS, atoi(cmd[8].c_str()));
        inv->setItem(Stones::THYSTAME, atoi(cmd[9].c_str()));
        for (size_t i = 4; i < cmd.size(); i++)
            quantity += std::atoi(cmd[i].c_str());
        if (quantity == 0)
            printf("GUI-COMMAND: Tile '%s' '%s' is empty\n", cmd[1].c_str(), cmd[2].c_str());
        else {
            printf("GUI-COMMAND: Tile '%s' '%s' contain:\n", cmd[1].c_str(), cmd[2].c_str());
            if (inv->getItem(Stones::FOOD))
                printf("   - FOOD     : '%d'\n", inv->getItem(Stones::FOOD));
            if (inv->getItem(Stones::LINEMATE))
                printf("   - LINEMATE : '%d'\n", inv->getItem(Stones::LINEMATE));
            if (inv->getItem(Stones::DERAUMERE))
                printf("   - DERAUMERE: '%d'\n", inv->getItem(Stones::DERAUMERE));
            if (inv->getItem(Stones::SIBUR))
                printf("   - SIBUR    : '%d'\n", inv->getItem(Stones::SIBUR));
            if (inv->getItem(Stones::MENDIANE))
                printf("   - MENDIANE : '%d'\n", inv->getItem(Stones::MENDIANE));
            if (inv->getItem(Stones::PHIRAS))
                printf("   - PHIRAS   : '%d'\n", inv->getItem(Stones::PHIRAS));
            if (inv->getItem(Stones::THYSTAME))
                printf("   - THYSTAME : '%d'\n", inv->getItem(Stones::THYSTAME));
        }
    } else
        throw ServerWarning(std::cerr, "Warning: incorrect command bct syntax");
    return true;
}

//name of all the teams
bool Commands::tna(Map *map, std::vector<std::string> cmd, Server server)
{
    if (cmd.size() != 2)
        throw ServerWarning(std::cerr, "Warning: incorrect command tna syntax");
    map->addTeamName(cmd[1].c_str());
    printf("GUI-COMMAND: Add the team '%s' to the list\n", cmd[1].c_str());
    this->updateLeaderBoard(map, server);
    return true;
}

//connection of a new player
bool Commands::pnw(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList;
    Player *newPlayer;

    if (cmd.size() != 7)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    for (size_t i = 1; i < cmd.size() - 1; i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    newPlayer = new Player();
    newPlayer->setId(std::atoi(cmd[1].c_str()));
    newPlayer->setPos(std::make_pair(std::atoi(cmd[2].c_str()), std::atoi(cmd[3].c_str())));
    newPlayer->setOrientation(std::atoi(cmd[4].c_str()));
    newPlayer->setLevel(std::atoi(cmd[5].c_str()));
    newPlayer->setTeam(cmd[6]);
    newPlayer->setSprite("assets/player/dino_sprite.png");
    map->addPlayer(*newPlayer);
    playerList = map->getPlayers();
    for (int i = 0; i < playerList->size(); i++) {
        if (playerList->at(i).getId() == std::atoi(cmd[1].c_str())) {
            printf("GUI-COMMAND: Connection of a new player:\n");
            printf("   - ID: '%zu'\n", playerList->at(i).getId());
            printf("   - Position: '%ld' '%ld'\n", playerList->at(i).getPos().first, playerList->at(i).getPos().second);
            printf("   - Orientation: '%d'\n", playerList->at(i).getOrientation());
            printf("   - Level: '%zu'\n", playerList->at(i).getLevel());
            printf("   - Team: '%s'\n", playerList->at(i).getTeam().c_str());
        }
    }
    return true;
}

//player’s position
bool Commands::ppo(Map *map, std::vector<std::string> cmd, Server server)
{
    if (cmd.size() != 5)
        throw ServerWarning(std::cerr, "Warning: incorrect command ppo syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command ppo syntax");
    map->getPlayerFromId(std::atoi(cmd[1].c_str()))->setPos(std::make_pair(std::atoi(cmd[2].c_str()), std::atoi(cmd[3].c_str())));
    printf("GUI-COMMAND: Update player ID '%zu' position to '%zu' '%zu'\n", map->getPlayerFromId(std::atoi(cmd[1].c_str()))->getId(), map->getPlayerFromId(std::atoi(cmd[1].c_str()))->getPos().first, map->getPlayerFromId(std::atoi(cmd[1].c_str()))->getPos().second);
    return true;
}

//player’s level
bool Commands::plv(Map *map, std::vector<std::string> cmd, Server server)
{
    Player *player;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command plv syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command plv syntax");
    player = map->getPlayerFromId(std::atoi(cmd[1].c_str()));
    player->setLevel(std::atoi(cmd[2].c_str()));
    printf("GUI-COMMAND: Set player ID '%s' level to '%s'\n", cmd[1].c_str(), cmd[2].c_str());
    return true;
}

//player’s inventory
bool Commands::pin(Map *map, std::vector<std::string> cmd, Server server)
{
    Player *player;
    Inventory inv;
    int quantity = 0;

    if (cmd.size() == 11) {
        for (size_t i = 1; i < cmd.size(); i++)
            for (size_t j = 0; j < cmd[i].length(); j++)
                if (!std::isdigit(cmd[i][j]))
                    throw ServerWarning(std::cerr, "Warning: incorrect command pin syntax");
        player = map->getPlayerFromId(std::atoi(cmd[1].c_str()));
        inv.setItem(Stones::FOOD, atoi(cmd[4].c_str()));
        inv.setItem(Stones::LINEMATE, atoi(cmd[5].c_str()));
        inv.setItem(Stones::DERAUMERE, atoi(cmd[6].c_str()));
        inv.setItem(Stones::SIBUR, atoi(cmd[7].c_str()));
        inv.setItem(Stones::MENDIANE, atoi(cmd[8].c_str()));
        inv.setItem(Stones::PHIRAS, atoi(cmd[9].c_str()));
        inv.setItem(Stones::THYSTAME, atoi(cmd[10].c_str()));
        player->setInventory(inv);
        for (size_t i = 4; i < cmd.size(); i++)
            quantity += std::atoi(cmd[i].c_str());
        if (quantity == 0)
            printf("GUI-COMMAND: Player '%s' inventory is empty\n", cmd[1].c_str());
        else {
            printf("GUI-COMMAND: Update player '%s' inventory:\n", cmd[1].c_str());
            if (player->getInventory().getItem(Stones::FOOD))
                printf("   - FOOD     : '%d'\n", player->getInventory().getItem(Stones::FOOD));
            if (player->getInventory().getItem(Stones::LINEMATE))
                printf("   - LINEMATE : '%d'\n", player->getInventory().getItem(Stones::LINEMATE));
            if (player->getInventory().getItem(Stones::DERAUMERE))
                printf("   - DERAUMERE: '%d'\n", player->getInventory().getItem(Stones::DERAUMERE));
            if (player->getInventory().getItem(Stones::SIBUR))
                printf("   - SIBUR    : '%d'\n", player->getInventory().getItem(Stones::SIBUR));
            if (player->getInventory().getItem(Stones::MENDIANE))
                printf("   - MENDIANE : '%d'\n", player->getInventory().getItem(Stones::MENDIANE));
            if (player->getInventory().getItem(Stones::PHIRAS))
                printf("   - PHIRAS   : '%d'\n", player->getInventory().getItem(Stones::PHIRAS));
            if (player->getInventory().getItem(Stones::THYSTAME))
                printf("   - THYSTAME : '%d'\n", player->getInventory().getItem(Stones::THYSTAME));
        }
    }
    return true;
}

//expulsion
bool Commands::pex(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pex\n");
    return false;
}

//broadcast
bool Commands::pbc(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList = map->getPlayers();

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command plv syntax");
    for (size_t j = 0; j < cmd[1].length(); j++)
        if (!std::isdigit(cmd[1][j]))
            throw ServerWarning(std::cerr, "Warning: incorrect command plv syntax");
    for (size_t i = 0; i < playerList->size(); i++)
        if (playerList->at(i).getId() == std::atoi(cmd[1].c_str())) {
            map->addToBroadcastList(cmd[2], playerList->at(i).getId());
            printf("GUI-COMMAND: Receive player '%d' broadcast: \"%s\"\n", playerList->at(i).getId(), cmd[2].c_str());
            return true;
        }
    return false;
}

//start of an incantation (by the first player)
bool Commands::pic(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList = map->getPlayers();

    if (cmd.size() < 5)
        throw ServerWarning(std::cerr, "Warning: incorrect command pic syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pic syntax");
    for (size_t i = 4; i < cmd.size(); i++) {
        for (size_t j = 0; j < playerList->size(); j++) {
            if (playerList->at(j).getId() == std::atoi(cmd[i].c_str())) {
                if (playerList->at(j).getPos().first == std::atoi(cmd[1].c_str()) && playerList->at(j).getPos().second == std::atoi(cmd[2].c_str())) {
                    if (playerList->at(j).getLevel() == std::atoi(cmd[3].c_str())) {
                        if (playerList->at(j).getIncantationStatus() == false) {
                            if (i == 4)
                                printf("GUI-COMMAND: Player '%d' started an incantation \n", playerList->at(j).getId());
                            else
                                printf("GUI-COMMAND: Player '%d' joined an incantation \n", playerList->at(j).getId());
                            playerList->at(j).setIncantationStatus(true);
                        } else {
                            printf("GUI-COMMAND: Player '%d' can't do the incantation because he's already doing one now\n", playerList->at(i).getId());
                        }
                    } else {
                        printf("GUI-COMMAND: Player '%d' can't do the incantation because he does not have the right level\n", playerList->at(i).getId());
                    }
                } else {
                    printf("GUI-COMMAND: Player '%d' can't do the incantation because he is not in the right position\n", playerList->at(i).getId());
                }
            }
        }
    }
    return true;
}

//end of an incantation
bool Commands::pie(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList = map->getPlayers();

    if (cmd.size() < 4)
        throw ServerWarning(std::cerr, "Warning: incorrect command pie syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pie syntax");
    if (std::atoi(cmd[3].c_str())) {
        for (size_t i = 0; i < playerList->size(); i++) {
            if (playerList->at(i).getPos().first == std::atoi(cmd[1].c_str()) && playerList->at(i).getPos().second == std::atoi(cmd[2].c_str())) {
                if (playerList->at(i).getIncantationStatus()) {
                    playerList->at(i).setIncantationStatus(false);
                    playerList->at(i).setLevel(playerList->at(i).getLevel() + 1);
                    printf("GUI-COMMAND: Player '%d' is now level '%d'\n", playerList->at(i).getId(), playerList->at(i).getLevel());
                }
            }
        }
    }
    this->updateLeaderBoard(map, server);
    return true;
}

//egg laying by the player
bool Commands::pfk(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pfk\n");
    return false;
}

//resource dropping
bool Commands::pdr(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList = map->getPlayers();
    Inventory *tile;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command pdr syntax");
    for (size_t j = 0; j < cmd[1].length(); j++)
        if (!std::isdigit(cmd[1][j]))
            throw ServerWarning(std::cerr, "Warning: incorrect command pdr syntax");
    for (size_t i = 0; i < playerList->size(); i++)
        if (playerList->at(i).getId() == std::atoi(cmd[1].c_str())) {
            tile = map->getTile(playerList->at(i).getPos().first, playerList->at(i).getPos().second);
            switch (std::atoi(cmd[2].c_str())) {
                case Stones::FOOD:
                    playerList->at(i).setInventory(Stones::FOOD, playerList->at(i).getInventory().getItem(Stones::FOOD) - 1);
                    tile->setItem(Stones::FOOD, tile->getItem(Stones::FOOD) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Food' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::LINEMATE:
                    playerList->at(i).setInventory(Stones::LINEMATE, playerList->at(i).getInventory().getItem(Stones::LINEMATE) - 1);
                    tile->setItem(Stones::LINEMATE, tile->getItem(Stones::LINEMATE) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Linemate' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::DERAUMERE:
                    playerList->at(i).setInventory(Stones::DERAUMERE, playerList->at(i).getInventory().getItem(Stones::DERAUMERE) - 1);
                    tile->setItem(Stones::DERAUMERE, tile->getItem(Stones::DERAUMERE) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Deraumere' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::SIBUR:
                    playerList->at(i).setInventory(Stones::SIBUR, playerList->at(i).getInventory().getItem(Stones::SIBUR) - 1);
                    tile->setItem(Stones::SIBUR, tile->getItem(Stones::SIBUR) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Sibur' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::MENDIANE:
                    playerList->at(i).setInventory(Stones::MENDIANE, playerList->at(i).getInventory().getItem(Stones::MENDIANE) - 1);
                    tile->setItem(Stones::MENDIANE, tile->getItem(Stones::MENDIANE) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Mendiane' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::PHIRAS:
                    playerList->at(i).setInventory(Stones::PHIRAS, playerList->at(i).getInventory().getItem(Stones::PHIRAS) - 1);
                    tile->setItem(Stones::PHIRAS, tile->getItem(Stones::PHIRAS) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Phiras' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::THYSTAME:
                    playerList->at(i).setInventory(Stones::THYSTAME, playerList->at(i).getInventory().getItem(Stones::THYSTAME) - 1);
                    tile->setItem(Stones::THYSTAME, tile->getItem(Stones::THYSTAME) + 1);
                    printf("GUI-COMMAND: Player '%d' drop a 'Thystame' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                default:
                    printf("GUI-COMMAND: Player '%d' want to drop a 'UNKNOW' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return false;
            }
        }
    return false;
}

//resource collecting
bool Commands::pgt(Map *map, std::vector<std::string> cmd, Server server)
{
    std::vector<Player> *playerList = map->getPlayers();
    Inventory *tile;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command pgt syntax");
    for (size_t j = 0; j < cmd[1].length(); j++)
        if (!std::isdigit(cmd[1][j]))
            throw ServerWarning(std::cerr, "Warning: incorrect command pgt syntax");
    for (size_t i = 0; i < playerList->size(); i++)
        if (playerList->at(i).getId() == std::atoi(cmd[1].c_str())) {
            tile = map->getTile(playerList->at(i).getPos().first, playerList->at(i).getPos().second);
            switch (std::atoi(cmd[2].c_str())) {
                case Stones::FOOD:
                    playerList->at(i).setInventory(Stones::FOOD, playerList->at(i).getInventory().getItem(Stones::FOOD) + 1);
                    tile->setItem(Stones::FOOD, tile->getItem(Stones::FOOD) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Food' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::LINEMATE:
                    playerList->at(i).setInventory(Stones::LINEMATE, playerList->at(i).getInventory().getItem(Stones::LINEMATE) + 1);
                    tile->setItem(Stones::LINEMATE, tile->getItem(Stones::LINEMATE) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Linemate' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::DERAUMERE:
                    playerList->at(i).setInventory(Stones::DERAUMERE, playerList->at(i).getInventory().getItem(Stones::DERAUMERE) + 1);
                    tile->setItem(Stones::DERAUMERE, tile->getItem(Stones::DERAUMERE) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Deraumere' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::SIBUR:
                    playerList->at(i).setInventory(Stones::SIBUR, playerList->at(i).getInventory().getItem(Stones::SIBUR) + 1);
                    tile->setItem(Stones::SIBUR, tile->getItem(Stones::SIBUR) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Sibur' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::MENDIANE:
                    playerList->at(i).setInventory(Stones::MENDIANE, playerList->at(i).getInventory().getItem(Stones::MENDIANE) + 1);
                    tile->setItem(Stones::MENDIANE, tile->getItem(Stones::MENDIANE) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Mendiane' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::PHIRAS:
                    playerList->at(i).setInventory(Stones::PHIRAS, playerList->at(i).getInventory().getItem(Stones::PHIRAS) + 1);
                    tile->setItem(Stones::PHIRAS, tile->getItem(Stones::PHIRAS) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Phiras' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                case Stones::THYSTAME:
                    playerList->at(i).setInventory(Stones::THYSTAME, playerList->at(i).getInventory().getItem(Stones::THYSTAME) + 1);
                    tile->setItem(Stones::THYSTAME, tile->getItem(Stones::THYSTAME) - 1);
                    printf("GUI-COMMAND: Player '%d' collect a 'Thystame' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return true;
                default:
                    printf("GUI-COMMAND: Player '%d' want to collect a 'UNKNOW' ressource on tile x: %d y: %d\n", playerList->at(i).getId(), playerList->at(i).getPos().first, playerList->at(i).getPos().second);
                    return false;
            }
        }
    return false;
}

//death of a player
bool Commands::pdi(Map *map, std::vector<std::string> cmd, Server server)
{
    int pos = 0;
    std::vector<Player> *playerList = map->getPlayers();

    if (cmd.size() != 2)
        throw ServerWarning(std::cerr, "Warning: incorrect command pdi syntax");
    for (size_t j = 1; j < cmd[1].length(); j++)
        if (!std::isdigit(cmd[1][j]))
            throw ServerWarning(std::cerr, "Warning: incorrect command pdi syntax");
    for (int i = 0; i < playerList->size(); i++) {
        if (playerList->at(i).getId() == std::atoi(cmd[1].c_str())) {
            pos = i;
            break;
        }
    }
    playerList->erase(playerList->begin() + pos);
    printf("GUI-COMMAND: Death of player '%s'\n", cmd[1].c_str());
    return true;
}

//an egg was laid by a player
bool Commands::enw(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("enw\n");
    return false;
}

//player connection for an egg
bool Commands::ebo(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("ebo\n");
    return false;
}

//death of an egg
bool Commands::edi(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("edi\n");
    return false;
}

//time unit request
bool Commands::sgt(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("sgt\n");
    return false;
}

//time unit modification
bool Commands::sst(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("sst\n");
    return false;
}

//end of game
bool Commands::seg(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("seg\n");
    return false;
}

//message from the server
bool Commands::smg(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("smg\n");
    return false;
}

//unknown command
bool Commands::suc(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("suc\n");
    return false;
}

//command parameter
bool Commands::sbp(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("sbp\n");
    return false;
}

bool Commands::welcome(Map *map, std::vector<std::string> cmd, Server server)
{
    if (cmd.size() != 1)
        throw ServerWarning(std::cerr, "Warning: incorrect command welcomme syntax");
    server.sendMessage("GRAPHIC");
    return true;
}

void Commands::updateLeaderBoard(Map *map, Server server)
{
    std::vector<std::pair<std::string, std::vector<int>>> score;
    std::vector<std::string> leaderboard;
    std::vector<int> teamscore;
    std::vector<Player> *playerList = map->getPlayers();
    std::vector<std::string> teamname = map->getTeamNames();
    int best;
    int actual;
    int max;
    bool find = false;

    for (size_t i = 0; i < teamname.size(); i++) {
        teamscore.clear();
        for (size_t j = 0; j < 8; j++)
            teamscore.push_back(0);
        for (size_t j = 0; j < playerList->size(); j++) {
            if (playerList->at(j).getTeam() == teamname[i]) {
                teamscore[playerList->at(j).getLevel() - 1]++;
            }
        }
        score.push_back(std::make_pair(teamname[i], teamscore));
    }
    while (!score.empty()) {
        max = 7;
        find = false;
        best = 0;
        while (!find && max > 0) {
            for (size_t i = 0; i < score.size(); i++) {
                if (score.at(i).second.at(max) > score.at(best).second.at(max) && score.at(i).second.at(max) != 0) {
                    best = i;
                    find = true;
                }
            }
            max--;
        }
        printf("ADD %s to leaderboard\n", score.at(best).first.c_str());
        leaderboard.push_back(score.at(best).first);
        score.erase(score.begin() + best);
    }
    map->setLeaderboard(leaderboard);
}