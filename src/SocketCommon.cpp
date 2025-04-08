/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : SocketCommon.cpp
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu 14 Mar 2024 10:22:15 PM CST
================================================================*/

#include "SocketCommon.hh"

std::string GenError(const std::string& error_msg) {
    std::string msg = "\033[31m" + error_msg + "\033[0m";
    return msg;
}

std::string GenSucceed(const std::string& succeed_msg) {
    std::string msg = "\033[32m" + succeed_msg + "\033[0m";
    return msg;
}

void PrintMsg(const std::string& ok_msg) {
    std::cout << "[INFO] " << ok_msg << std::endl;
}

void PrintErrorMsg(const std::string& error_msg) {
    std::cout << GenError("[ ERROR ] ") << error_msg << std::endl;
}

void PrintSucceedMsg(const std::string& succeed_msg) {
    std::cout << GenSucceed("[SUCCEED] ") << succeed_msg << std::endl;
}

void GetIPName(int socket, std::string& ip, int& port) {
    struct sockaddr_in peer_addr;
    socklen_t          peer_addr_len = sizeof(peer_addr);
    if (getpeername(socket, (struct sockaddr*)&peer_addr, &peer_addr_len) == -1) {
        PrintErrorMsg("GetPeerName failed");
    }

    // get ipname and port.
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &peer_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

    ip                 = std::string(client_ip);
    port               = int(ntohs(peer_addr.sin_port));
    std::string ipname = std::string(client_ip) + ":" + std::to_string(ntohs(peer_addr.sin_port));
}