CC=g++
FLAGS= -Wall -std=c++11 -I./ 

all:
	$(CC) $(FLAGS) ./TCPServer.cpp ./server_demo.cpp -o server_demo -lpthread
	$(CC) $(FLAGS) ./TCPClient.cpp ./client_demo.cpp -o client_demo -lpthread
