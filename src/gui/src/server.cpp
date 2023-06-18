/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#include "../inc/gui.hpp"

const char *ServerError::what() const throw()
{
	return this->_msg.c_str();
}

const char *ServerWarning::what() const throw()
{
	return this->_msg.c_str();
}

Server::Server(int ac, char **av)
{
    int port;
    std::string ip;

    printf("GUI: Initialize server ...\n");
    if (!this->areArgumentsCorrect(ac, av))
        throw ServerError(std::cerr, "GUI: Incorrect arguments");
    if ((this->_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw ServerError(std::cerr, "GUI: Error while creating socket");
    this->_s_addr.sin_family = AF_INET;
    this->_s_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    this->_s_addr.sin_port = htons(port);
    if (setsockopt(this->_sd, SOL_SOCKET, SO_REUSEADDR, &this->_s_addr, sizeof(int)) == -1)
        throw ServerError(std::cerr, "GUI: Error setting socket options");
    if (connect(this->_sd, (struct sockaddr *)&this->_s_addr, sizeof(this->_s_addr)) == -1)
        throw ServerError(std::cerr, "GUI: Error while trying to connect to the server");
}

bool Server::isNumber(std::string str)
{
    for (int i = 0; i < str.length(); i++)
        if (!std::isdigit(str[i]))
            return false;
    return true;
}

bool Server::areArgumentsCorrect(int ac, char **av)
{
    int pos = -1;
    std::string ip;
    std::string str;

    if (ac < 3)
        return false;
    for (int i = 1; i < ac - 1; i++) {
        if (!strcmp(av[i], "-p")) {
            pos = i + 1;
            break;
        }
    }
    if (pos == -1)
        return false;
    if (!this->isNumber((std::string)av[pos]))
        return false;
    this->_port = std::atoi(av[pos + 1]);
    for (int i = 1, pos = -1; i < ac - 1; i++) {
        if (!strcmp(av[i], "-h")) {
            pos = i + 1;
            break;
        }
    }
    if (pos == -1) {
        this->_ip = "127.0.0.1";
        return true;
    } else {
        ip = (std::string)av[pos];
        if (std::count(ip.begin(), ip.end(), '.') != 4)
            return false;
        while (ip.find_last_of('.') != std::string::npos) {
            str = str.substr(0, ip.find_last_of('.'));
            if (!this->isNumber(str))
                return false;
            ip = ip.substr(ip.find_last_of('.') + 1, ip.size());
        }
        if (!this->isNumber(ip))
            return false;
        this->_ip = (std::string)av[pos];
        return true;
    }
}

bool Server::isReceivingTransmission()
{
    FD_ZERO(&this->_rfds);
    FD_SET(this->_sd, &this->_rfds);
    if (this->_activity == 1)
        return false;
    this->_activity = select(this->_sd + 1, &this->_rfds, NULL, NULL, 0);
    if (this->_activity > 0) {
        this->readTransmission();
        return true;
    } else if (this->_activity == -1)
        throw ServerError(std::cerr, "GUI: Error during select");
    else
        return false;
}

void Server::readTransmission()
{
    std::string str;
    char part[1000 + 1];
    int len;
    std::string commandPart;

    this->_transmission.clear();
    while ((len = read(this->_sd, &part, 1000)) > 0) {
        part[len] = '\0';
        str += len;
        printf("DEBUG: actual transmission received : '%s'\n", str.c_str());
    }
    if (!str.empty()) {
        str.pop_back();
        if (!str.empty())
            str.pop_back();
    }
    printf("DEBUG: Before parsing: '%s'\n", str.c_str());
    while (str.find_last_of('\n') != std::string::npos) {
        len = str.find_first_of('\n');
        commandPart = str.substr(0, len);
        str = str.substr(len + 1, str.size());
        this->_transmission.push_back(commandPart);
    }
   this->_activity = 0;
}

std::vector<std::string> Server::getTransmission() const
{
    return this->_transmission;
}

void Server::sendMessage(std::string msg)
{
    dprintf(this->_sd, msg.c_str());
}
