/*
** EPITECH PROJECT, 2023
** server.hpp
** File description:
** server
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
    printf("GUI: Initialize server ...\n");
    if (!this->areArgumentsCorrect(ac, av))
        throw ServerError(std::cerr, "GUI: Incorrect arguments");
    if ((this->_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw ServerError(std::cerr, "GUI: Error while creating socket");
    this->_s_addr.sin_family = AF_INET;
    this->_s_addr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
    this->_s_addr.sin_port = htons(this->_port);
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
    this->_port = std::atoi(av[pos]);
    pos = -1;
    for (int i = 1; i < ac - 1; i++) {
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
        if (std::count(ip.begin(), ip.end(), '.') != 3)
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
    timeval time;

    time.tv_usec = 1;
    time.tv_sec = 0;
    FD_ZERO(&this->_rfds);
    FD_SET(this->_sd, &this->_rfds);
    if (this->_activity == 1)
        return false;
    this->_activity = select(this->_sd + 1, &this->_rfds, NULL, NULL, &time);
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
    std::string str = "";
    char part[65536 + 1];
    int len;
    std::string commandPart;

    this->_transmission.clear();
    if ((len = read(this->_sd, &part, 65536)) > 0) {
        part[len - 1] = '\0';
        str += part;
    }
    while (str.find_last_of('\n') != std::string::npos) {
        len = str.find_first_of('\n');
        commandPart = str.substr(0, len);
        str = str.substr(len + 1, str.size());
        this->_transmission.push_back(commandPart);
    }
    this->_transmission.push_back(str);
    this->ParseTransmission();
    this->_activity = 0;
}

void Server::ParseTransmission()
{
    std::vector<std::string> parsed;
    std::string commandPart;
    int len;

    this->_cmds.clear();
    for (int i = 0; i < this->_transmission.size(); i++) {
        parsed.clear();
        commandPart.clear();
        while (this->_transmission[i].find_last_of(' ') != std::string::npos) {
            len = this->_transmission[i].find_first_of(' ');
            commandPart = this->_transmission[i].substr(0, len);
            this->_transmission[i] = this->_transmission[i].substr(len + 1, this->_transmission[i].size());
            parsed.push_back(commandPart);
        }
        parsed.push_back(this->_transmission[i]);
        this->_cmds.push_back(parsed);
    }
}

std::vector<std::vector<std::string>> Server::getTransmission() const
{
    return this->_cmds;
}

void Server::sendMessage(std::string msg)
{
    printf("GUI: Message sent : '%s'\n", msg.c_str());
    msg += "\n";
    dprintf(this->_sd, "%s", msg.c_str());
}
