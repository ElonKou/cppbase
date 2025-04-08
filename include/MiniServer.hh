#pragma once

#include "SocketCommon.hh"
#include <csignal>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class MiniServer {
  public:
    int port; // server port.

    int                server_fd;  // server file descriptor.
    static int         new_socket; // soket
    struct sockaddr_in address;    // server soket address

    bool        is_listening;       // whether server is listening flag.
    bool        is_connected;       // whether has client connected.
    char        buffer[4096] = {0}; // [1K] buffer for data.
    std::string ipname       = "";  // client ip.

  public:
    MiniServer() {
        port         = 12345;
        new_socket   = 0;
        is_listening = false;
        is_connected = false;
    }
    ~MiniServer() { TerminateServer(); }

    static void handleSignal(int signum) {
        close(MiniServer::new_socket);
        PrintSucceedMsg("Terminate server.");
        exit(signum);
    }

    void Listen();

    void TerminateServer();

    bool ReadMsg(std::string& ret);

    // for other process use.
    virtual void Process();
};
