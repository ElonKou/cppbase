/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : MiniServer.cpp
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu 14 Mar 2024 11:33:32 AM CST
================================================================*/

#include "MiniServer.hh"

int MiniServer::new_socket = 0;

void MiniServer::Listen() {
    try {
        int addrlen = sizeof(address);

        // create socket file
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            PrintErrorMsg("sever created failed.");
            exit(EXIT_FAILURE);
        }

        // set time-wait status, for reused address
        int optval = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

        address.sin_family      = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port        = htons(port);

        // bind socket to port
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            PrintErrorMsg("Bind failed port: " + std::to_string(port));
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 3) < 0) {
            is_listening = false;
            PrintErrorMsg("Listen failed: " + std::to_string(port));
            exit(EXIT_FAILURE);
        } else {
            is_listening = true;
            PrintSucceedMsg("Listen port: " + std::to_string(port));
        }

        // start listen
        while (is_listening) {
            PrintSucceedMsg("Waiting for connections...");

            // check accepted?
            if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                PrintErrorMsg("Accept client failed.");
                is_connected = false;
                exit(EXIT_FAILURE);
            } else {
                std::string name;
                int         ipport;
                GetIPName(new_socket, name, ipport);
                ipname = name + ":" + std::to_string(ipport);

                PrintSucceedMsg("Connection from " + ipname);
                is_connected = true; // connected
            }
            // process msg
            Process();
        }
        throw std::runtime_error("Exception from thread");
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in thread: " << e.what() << '\n';
    }
}

void MiniServer::TerminateServer() {
    is_listening = false;
    if (is_connected) {
        is_connected = false;
        PrintSucceedMsg("Terminate server."); // terminate
        close(new_socket);                    // close and wait next connetions.
    }
}

bool MiniServer::ReadMsg(std::string& ret) {
    int valread = read(new_socket, buffer, 4096);
    if (valread == 0) { // client closed
        is_connected = false;

        PrintSucceedMsg("Disconnect at: " + ipname);
        close(new_socket); // close and wait next connetions.
        return false;
    }
    ret = std::string(buffer);

    memset(buffer, 0, 4096); // clear buffer
    return true;
}

void MiniServer::Process() {
    while (is_connected) {
        std::string msg;
        if (ReadMsg(msg)) {
            std::cout << "   ";
            PrintMsg("[" + ipname + "]: " + msg); // print message.
        }
    }
}