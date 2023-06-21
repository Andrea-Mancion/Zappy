/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#include "libs.hpp"
#include "map.hpp"
#include <unordered_map>

class Commands {
    private:
        std::unordered_map<std::string, bool(Commands::*)(Map *map, std::vector<std::string> cmd, Server server)> _cmdList;
        bool msz(Map *map, std::vector<std::string> cmd, Server server);
        bool bct(Map *map, std::vector<std::string> cmd, Server server);
        bool tna(Map *map, std::vector<std::string> cmd, Server server);
        bool pnw(Map *map, std::vector<std::string> cmd, Server server);
        bool ppo(Map *map, std::vector<std::string> cmd, Server server);
        bool plv(Map *map, std::vector<std::string> cmd, Server server);
        bool pin(Map *map, std::vector<std::string> cmd, Server server);
        bool pex(Map *map, std::vector<std::string> cmd, Server server);
        bool pbc(Map *map, std::vector<std::string> cmd, Server server);
        bool pic(Map *map, std::vector<std::string> cmd, Server server);
        bool pie(Map *map, std::vector<std::string> cmd, Server server);
        bool pfk(Map *map, std::vector<std::string> cmd, Server server);
        bool pdr(Map *map, std::vector<std::string> cmd, Server server);
        bool pgt(Map *map, std::vector<std::string> cmd, Server server);
        bool pdi(Map *map, std::vector<std::string> cmd, Server server);
        bool enw(Map *map, std::vector<std::string> cmd, Server server);
        bool ebo(Map *map, std::vector<std::string> cmd, Server server);
        bool edi(Map *map, std::vector<std::string> cmd, Server server);
        bool sgt(Map *map, std::vector<std::string> cmd, Server server);
        bool sst(Map *map, std::vector<std::string> cmd, Server server);
        bool seg(Map *map, std::vector<std::string> cmd, Server server);
        bool smg(Map *map, std::vector<std::string> cmd, Server server);
        bool suc(Map *map, std::vector<std::string> cmd, Server server);
        bool sbp(Map *map, std::vector<std::string> cmd, Server server);
        bool welcome(Map *map, std::vector<std::string> cmd, Server server);
    public:
        Commands();
        ~Commands() = default;
        bool doCommand(Map *map, std::vector<std::vector<std::string>> cmd, Server server);
};