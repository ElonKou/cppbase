#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>

std::string GenError(const std::string& error_msg);

std::string GenSucceed(const std::string& succeed_msg);

void PrintMsg(const std::string& ok_msg);

void PrintErrorMsg(const std::string& error_msg);

void PrintSucceedMsg(const std::string& succeed_msg);

void GetIPName(int socket, std::string& ip, int& port);
