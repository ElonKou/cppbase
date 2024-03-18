#pragma once

#include "SocketCommon.hh"
#include <csignal>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

// search port:  ss -tuln | grep :8080

class MiniClient {
  public:
    std::string        ip_add;       // server ip.
    static int         ip_port;      // server port.
    static int         sock;         // server handle.
    struct sockaddr_in serv_addr;    // server whole address.
    bool               is_connected; // whether is connected.

  public:
    MiniClient() {
        is_connected = false;       // not connected.
        ip_add       = "127.0.0.1"; // default value.
        ip_port      = 12345;       // default value.
        sock         = 0;           // connect handle.
    }
    ~MiniClient() {
        CloseConnection();
    }

    static void handleSignal(int signum) {
        close(MiniClient::sock);
        PrintSucceedMsg("Disconnected from server.");
        exit(signum);
    }

    bool Connect(std::string ipadd, int port);

    void CloseConnection();

    bool SendMsg(std::string msg);

    virtual void Update();
};