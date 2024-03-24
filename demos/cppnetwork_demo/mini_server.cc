/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : server.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Fri 15 Mar 2024 01:01:08 PM CST
================================================================*/

#include "MiniServer.hh"
#include "json.hpp"
#include <glm/glm.hpp>
#include <mutex>
#include <thread>

class MotionServer : public MiniServer {
  public:
    std::mutex  mutex_v;
    std::thread m_server_thread; // server thread
    glm::vec3   value;           // protect value

  public:
    MotionServer() {
        m_server_thread = std::thread([&]() {
            Listen();
        });
    }
    ~MotionServer() {
        if (m_server_thread.joinable()) {
            m_server_thread.join();
        }
        TerminateServer();
    }

    void ModifiedValue(const glm::vec3& newvalue) {
        std::lock_guard<std::mutex> lock(mutex_v);
        value = newvalue;
    }

    void Process() override {
        while (is_connected) {
            std::string msg;
            if (ReadMsg(msg)) {

                std::cout << "   ";
                PrintMsg("[" + ipname + "]: " + msg); // print message.

                // nlohmann::json     data = nlohmann::json::parse(msg);
                // std::vector<float> pos  = data["pos"].get<std::vector<float>>();
                // ModifiedValue(glm::vec3(pos[0], pos[1], pos[2]));

                // std::string posv = std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z);
                // PrintMsg("[" + ipname + "]: " + posv);
            }
        }
    }
};

class App {
  public:
    std::shared_ptr<MotionServer> m_server;

  public:
    App() {
        m_server = std::make_shared<MotionServer>();
    }

    ~App() {
    }
};

int main(int argc, char* argv[]) {
    MotionServer server;
    signal(SIGINT, server.handleSignal);

    // std::shared_ptr<App> app = std::make_shared<App>();
    // signal(SIGINT, app->m_server->handleSignal);

    return 0;
}
