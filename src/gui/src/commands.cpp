/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
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
    Inventory inv;
    std::vector<Inventory> invLine;
    std::vector<std::vector<Inventory>> inventory;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    map->setDimension(std::atoi(cmd[1].c_str()), std::atoi(cmd[2].c_str()));
    for (int i = 0; i < map->getDimension().first; i++)
        invLine.push_back(inv);
    for (int i = 0; i < map->getDimension().second; i++)
        inventory.push_back(invLine);
    map->setTiles(inventory);
    printf("GUI-COMMAND: Update map size to %s %s\n", cmd[1].c_str(), cmd[2].c_str());
    //server.sendMessage("msz\n");
    return true;
}

//content of a tile
bool Commands::bct(Map *map, std::vector<std::string> cmd, Server server)
{
    Inventory *inv;

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
        printf("GUI-COMMAND: Update tile '%s' '%s' data:\n", cmd[1].c_str(), cmd[2].c_str());
        printf("   - FOOD     : '%d'\n", inv->getItem(Stones::FOOD));
        printf("   - LINEMATE : '%d'\n", inv->getItem(Stones::LINEMATE));
        printf("   - DERAUMERE: '%d'\n", inv->getItem(Stones::DERAUMERE));
        printf("   - SIBUR    : '%d'\n", inv->getItem(Stones::SIBUR));
        printf("   - MENDIANE : '%d'\n", inv->getItem(Stones::MENDIANE));
        printf("   - PHIRAS   : '%d'\n", inv->getItem(Stones::PHIRAS));
        printf("   - THYSTAME : '%d'\n", inv->getItem(Stones::THYSTAME));
    } else
        throw ServerWarning(std::cerr, "Warning: incorrect command bct syntax");
    return false;
}

//name of all the teams
bool Commands::tna(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("tna\n");
    return false;
}

//connection of a new player
bool Commands::pnw(Map *map, std::vector<std::string> cmd, Server server)
{
    Player newPlayer;

    if (cmd.size() != 7)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    for (size_t i = 1; i < cmd.size() - 1; i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    newPlayer.setId(std::atoi(cmd[1].c_str()));
    newPlayer.setPos(std::make_pair(std::atoi(cmd[2].c_str()), std::atoi(cmd[3].c_str())));
    newPlayer.setOrientation(std::atoi(cmd[4].c_str()));
    newPlayer.setLevel(std::atoi(cmd[5].c_str()));
    newPlayer.setTeam(cmd[6]);
    map->addPlayer(newPlayer);
    printf("GUI-COMMAND: Connection of a new player:\n");
    printf("   - ID: '%s'\n", cmd[1].c_str());
    printf("   - Position: '%s' '%s'\n", cmd[2].c_str(), cmd[3].c_str());
    printf("   - Orientation: '%s'\n", cmd[4].c_str());
    printf("   - Level: '%s'\n", cmd[5].c_str());
    printf("   - Team: '%s'\n", cmd[6].c_str());
    return true;
}

//player’s position
bool Commands::ppo(Map *map, std::vector<std::string> cmd, Server server)
{
    Player *player;

    printf("ppo\n");
    if (cmd.size() != 5)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    player = map->getPlayer(std::atoi(cmd[1].c_str()));
    player->setPos(std::make_pair(std::atoi(cmd[2].c_str()), std::atoi(cmd[3].c_str())));
    printf("GUI-COMMAND: Update player ID '%s' position to '%s' '%s'\n", cmd[1].c_str(), cmd[2].c_str(), cmd[3].c_str());
    return true;
}

//player’s level
bool Commands::plv(Map *map, std::vector<std::string> cmd, Server server)
{
    Player *player;

    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    player = map->getPlayer(std::atoi(cmd[1].c_str()));
    player->setLevel(std::atoi(cmd[2].c_str()));
    printf("GUI-COMMAND: Set player ID '%s' level to '%s'\n", cmd[1].c_str(), cmd[2].c_str());
    //server.sendMessage("plv " + cmd[1] + "\n");
    return true;
}

//player’s inventory
bool Commands::pin(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pin\n");
    return false;
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
    printf("pbc\n");
    return false;
}

//start of an incantation (by the first player)
bool Commands::pic(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pic\n");
    return false;
}

//end of an incantation
bool Commands::pie(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pie\n");
    return false;
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
    printf("pdr\n");
    return false;
}

//resource collecting
bool Commands::pgt(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pgt\n");
    return false;
}

//death of a player
bool Commands::pdi(Map *map, std::vector<std::string> cmd, Server server)
{
    printf("pdi\n");
    return false;
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
