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

SERVER_ADDRESS = '127.0.0.1'  # server config
SERVER_PORT = 12345           # server config


def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    client_socket.connect((SERVER_ADDRESS, SERVER_PORT))
    print(f"Connected to server {SERVER_ADDRESS}:{SERVER_PORT}")

    try:
        while True:
            data_to_send = input("Enter message to send: ")
            if data_to_send.lower() == 'exit':
                print("Exiting client.")
                break

            data = {}
            data["type"] = "motion"
            data["name"] = data_to_send
            data["pos"] = [float(data_to_send), 0.23, 0.34]

            data_str = json.dumps(data, indent=4)
            client_socket.sendall(data_str.encode())

    except KeyboardInterrupt:
        print("\nClient interrupted by user.")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        client_socket.close()
        print("Connection closed.")


if __name__ == '__main__':
    main()
