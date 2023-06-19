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

bool Commands::doCommand(Map *map, std::vector<std::string> cmd, Server server)
{
    if (this->_cmdList.find(cmd[0]) == this->_cmdList.end())
		throw ServerWarning(std::cerr, "Warning: '" + cmd[0] + "': unknow command");
    try {
        return this->_cmdList[cmd[0]];
    } catch (ServerWarning &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

//map size
bool Commands::msz(Map *map, std::vector<std::string> cmd, Server server)
{
    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    map->setDimension(std::atoi(cmd[1].c_str()), std::atoi(cmd[2].c_str()));
    //server.sendMessage("msz\n");
    return true;
}

//content of a tile
bool Commands::bct(Map *map, std::vector<std::string> cmd, Server server)
{

    //if (cmd.size() == 10) {
    //    for (size_t i = 1; i < cmd.size(); i++)
    //        for (size_t j = 0; j < cmd[i].length(); j++)
    //            if (!std::isdigit(cmd[i][j]))
    //                throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    //} else if (cmd.size() % 10 == 0) {
    //    for (size_t i = 0; i < cmd.size(); i += 10)
    //        for (size_t j = i + 1; j < i + 10; j++)
    //            for (size_t k = 0; j < cmd[j].length(); j++)
    //                if (!std::isdigit(cmd[j][k]))
    //                    throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    //
    //} else
    //    throw ServerWarning(std::cerr, "Warning: incorrect command bct syntax");
    return false;
}

//name of all the teams
bool Commands::tna(Map *map, std::vector<std::string> cmd, Server server)
{
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
    return true;
}

//player’s position
bool Commands::ppo(Map *map, std::vector<std::string> cmd, Server server)
{
    Player *player;

    if (cmd.size() != 5)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    player = map->getPlayer(std::atoi(cmd[1].c_str()));
    player->setPos(std::make_pair(std::atoi(cmd[2].c_str()), std::atoi(cmd[3].c_str())));
    //server.sendMessage("ppo " + cmd[1] + "\n");
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
    //server.sendMessage("plv " + cmd[1] + "\n");
    return true;
}

//player’s inventory
bool Commands::pin(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//expulsion
bool Commands::pex(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//broadcast
bool Commands::pbc(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//start of an incantation (by the first player)
bool Commands::pic(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//end of an incantation
bool Commands::pie(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//egg laying by the player
bool Commands::pfk(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//resource dropping
bool Commands::pdr(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//resource collecting
bool Commands::pgt(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//death of a player
bool Commands::pdi(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//an egg was laid by a player
bool Commands::enw(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//player connection for an egg
bool Commands::ebo(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//death of an egg
bool Commands::edi(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//time unit request
bool Commands::sgt(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//time unit modification
bool Commands::sst(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//end of game
bool Commands::seg(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//message from the server
bool Commands::smg(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//unknown command
bool Commands::suc(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

//command parameter
bool Commands::sbp(Map *map, std::vector<std::string> cmd, Server server)
{
    return false;
}

bool Commands::welcome(Map *map, std::vector<std::string> cmd, Server server)
{
    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command pnw syntax");
    server.sendMessage("GRAPHIC");
    return true;
}
