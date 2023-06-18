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
        std::unordered_map<std::string, bool(Commands::*)(Map *map, std::vector<std::string> cmd)> _cmdList;
        bool msz(Map *map, std::vector<std::string> cmd);
        bool bct(Map *map, std::vector<std::string> cmd);
        bool tna(Map *map, std::vector<std::string> cmd);
        bool pnw(Map *map, std::vector<std::string> cmd);
        bool ppo(Map *map, std::vector<std::string> cmd);
        bool plv(Map *map, std::vector<std::string> cmd);
        bool pin(Map *map, std::vector<std::string> cmd);
        bool pex(Map *map, std::vector<std::string> cmd);
        bool pbc(Map *map, std::vector<std::string> cmd);
        bool pic(Map *map, std::vector<std::string> cmd);
        bool pie(Map *map, std::vector<std::string> cmd);
        bool pfk(Map *map, std::vector<std::string> cmd);
        bool pdr(Map *map, std::vector<std::string> cmd);
        bool pgt(Map *map, std::vector<std::string> cmd);
        bool pdi(Map *map, std::vector<std::string> cmd);
        bool enw(Map *map, std::vector<std::string> cmd);
        bool ebo(Map *map, std::vector<std::string> cmd);
        bool edi(Map *map, std::vector<std::string> cmd);
        bool sgt(Map *map, std::vector<std::string> cmd);
        bool sst(Map *map, std::vector<std::string> cmd);
        bool seg(Map *map, std::vector<std::string> cmd);
        bool smg(Map *map, std::vector<std::string> cmd);
        bool suc(Map *map, std::vector<std::string> cmd);
        bool sbp(Map *map, std::vector<std::string> cmd);
    public:
        Commands();
        ~Commands() = default;
        bool doCommand(const std::string &type, Map *map, std::vector<std::string> cmd);
};