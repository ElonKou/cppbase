#!/bin/env python3
# -*- coding: utf-8 -*-
# ================================================================*/
#  Copyright (C)2024 All rights reserved.
#  FileName : mini_client.py
#  Author   : dlkou
#  Email    : elonkou@ktime.cc
#  Date     : Mon 18 Mar 2024 03:35:31 PM CST
# ================================================================*/


import socket
import json


class MiniServer:
    def __init__(self) -> None:
        self.isconnected = False
        self.SERVER_ADDRESS = '127.0.0.1'  # server config
        self.SERVER_PORT = 12345           # server config
        self.ConnectServer()

    def ConnectServer(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.SERVER_ADDRESS, self.SERVER_PORT))
        print(f"Connected to server {self.SERVER_ADDRESS}:{self.SERVER_PORT}")
        self.isconnected = True

    def SendMsg(self, data):
        if self.isconnected:
            data_str = json.dumps(data, indent=4)
            self.client_socket.sendall(data_str.encode())
        else:
            print("Send failed, server is closed.")

    def TerminateServer(self):
        self.client_socket.close()
        print("Connection closed.")


def main():
    server = MiniServer()

    try:
        while True:
            data_to_send = input("Enter message to send: ")
            # print(data_to_send, float(data_to_send), type(data_to_send), type(float(data_to_send)))
            if data_to_send.lower() == 'exit':
                print("Exiting client.")
                break

            data = {}
            data["name"] = "motion"
            data["rots"] = [0.0 for i in range(16*3-1)]
            data["rots"] = [float(data_to_send)] + data["rots"]

            server.SendMsg(data=data)

    except KeyboardInterrupt:
        print("\nClient interrupted by user.")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        server.TerminateServer()


if __name__ == '__main__':
    main()
