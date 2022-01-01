/*
 * Author: 318324563 - Daniel Meir Karl
 */
#include "Server.h"

/**
 * setting of the server - the file descriptor of the server.
 * making the server ready for the start method that handles the client.
 * @param port
 */
Server::Server(int port) throw(const char *) {
    stopping = false;
    fdServer = socket(AF_INET, SOCK_STREAM, 0);
    if (fdServer < 0) {
        throw "socket failure";
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(fdServer, (struct sockaddr *) &server, sizeof(server)) < 0) {
        throw "bind failure";
    }
    if (listen(fdServer, 2) < 0) {
        throw "listen failure";
    }
}

// using strategy pattern
void Server::start(ClientHandler &ch) throw(const char *) {
    t = new thread([this, &ch]() {
        while (!stopping) {
            socklen_t size = sizeof(client);
            int fdClient = accept(fdServer, (struct sockaddr *) &client, &size);
            if (fdClient > 0) {
                ch.handle(fdClient);
                close(fdClient);
            }
        }
        close(fdServer);
    });
}

void Server::stop() {
    stopping = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

string socketIO::read() {
    char letter = 0;
    string str = "";
    while (letter != '\n') {
        recv(clientID, &letter, sizeof(letter), 0);
        str += letter;
    }
    return str;
}

void socketIO::write(string text) {
    const char *ptr = text.c_str();
    send(clientID, ptr, strlen(ptr), 0);
}

void socketIO::write(float f) {
    ostringstream stringStrem;
    stringStrem << f;
    string str(stringStrem.str());
    write(str);
}

void socketIO::read(float *f) {

}

