/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#pragma once
#include "libs.hpp"
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

class Server {
    private:
    struct sockaddr_in _s_addr = {0};
    int _sd;
    fd_set _rfds;
    int _activity = 0;
    std::vector<std::string> _transmission;
    std::vector<std::vector<std::string>> _cmds;
    int _port;
    std::string _ip;

    public:
    Server(int ac, char **av);
    ~Server() = default;

    bool areArgumentsCorrect(int ac, char **av);
    void sendMessage(std::string msg);
    bool isReceivingTransmission();
    std::vector<std::vector<std::string>> getTransmission() const;
    void readTransmission();
    bool isNumber(std::string str);
    void ParseTransmission();
};

class ServerError: public std::exception {
	private:
	std::string _msg;
	std::ostream &_os;

	public:
	ServerError(std::ostream &os, const std::string &msg) throw() : _os(os), _msg(msg) {};
	virtual ~ServerError() throw() = default;
	const char *what() const throw();
};

class ServerWarning: public std::exception {
	private:
	std::string _msg;
	std::ostream &_os;

	public:
	ServerWarning(std::ostream &os, const std::string &msg) throw() : _os(os), _msg(msg) {};
	virtual ~ServerWarning() throw() = default;
	const char *what() const throw();
};