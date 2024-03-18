/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : client.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu 14 Mar 2024 11:33:39 AM CST
================================================================*/

#include "MiniClient.hh"
#include "json.hpp"

class SendClient : public MiniClient {
  public:
    SendClient() {}
    ~SendClient() {}

    virtual void Update() override {
        while (is_connected) {
            std::string words;
            std::cout << "Enter message: ";
            std::getline(std::cin, words);

            nlohmann::json     data;
            std::vector<float> pos = {std::stof(words), 0.23f, 0.34f};
            data["type"]           = "motion";
            data["name"]           = words;
            data["pos"]            = pos;

            std::string message = data.dump();

            if (words == "exit") {
                CloseConnection();
                break;
            } else {
                SendMsg(message);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    SendClient client = SendClient();
    signal(SIGINT, client.handleSignal);

    if (client.Connect("127.0.0.1", 12345)) {
        client.Update();
    } else {
        client.CloseConnection();
    }

    return 0;
}
