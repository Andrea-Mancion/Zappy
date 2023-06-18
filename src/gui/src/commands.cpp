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
}

bool Commands::doCommand(const std::string &type, Map *map, std::vector<std::string> cmd)
{
    if (this->_cmdList.find(type) == this->_cmdList.end())
		throw ServerWarning(std::cerr, "Warning: '" + type + "': unknow command");
    try {
        return this->_cmdList[type];
    } catch (ServerWarning &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool Commands::msz(Map *map, std::vector<std::string> cmd)
{
    if (cmd.size() != 3)
        throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    for (size_t i = 1; i < cmd.size(); i++)
        for (size_t j = 0; j < cmd[i].length(); j++)
            if (!std::isdigit(cmd[i][j]))
                throw ServerWarning(std::cerr, "Warning: incorrect command msz syntax");
    map->setDimension(std::atoi(cmd[1].c_str()), std::atoi(cmd[2].c_str()));

    return true;
}