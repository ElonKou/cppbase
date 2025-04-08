/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : MiniClient.cpp
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu 14 Mar 2024 11:33:39 AM CST
================================================================*/

#include "MiniClient.hh"

int MiniClient::ip_port = 12345; // init as default value.
int MiniClient::sock    = 0;     // init as default value.

bool MiniClient::Connect(std::string ipadd, int port) {
    MiniClient::ip_add  = ipadd;
    MiniClient::ip_port = port;
    MiniClient::sock    = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        PrintErrorMsg("Socket creation error");
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(ip_port);

    if (inet_pton(AF_INET, ip_add.c_str(), &serv_addr.sin_addr) <= 0) {
        PrintErrorMsg("Invalid address, Address not supported");
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        PrintErrorMsg("Connection Failed at: " + std::to_string(ip_port));
        return false;
    } else {
        is_connected = true;

        std::string ipname;
        int         ipport;
        GetIPName(sock, ipname, ipport);
        std::string ipaddress = ipname + ":" + std::to_string(ipport);

        PrintSucceedMsg("Connected to server: " + ipaddress);
    }

    return true; // create succeed
}

void MiniClient::CloseConnection() {
    if (is_connected) {
        is_connected = false;
        close(sock);
        PrintSucceedMsg("Disconnected from server.");
    }
}

bool MiniClient::SendMsg(std::string msg) {
    if (is_connected) {
        int v = send(sock, msg.c_str(), msg.length(), 0);
        if (v < 0) {
            PrintErrorMsg("Send failed.");
            return false;
        } else if (v == 0) {
            CloseConnection(); // server is terminated.
            return false;
        }
    } else {
        PrintErrorMsg("Not connected to server.");
        return false;
    }
    return true;
}

void MiniClient::Update() {
    while (is_connected) {
        std::string words;
        std::cout << "Enter message: ";
        std::getline(std::cin, words);

        if (words == "exit") {
            CloseConnection();
            break;
        } else {
            SendMsg(words);
        }
    }
}