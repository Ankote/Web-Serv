#pragma once
#include <iostream>
#include <sys/socket.h>
#include <cerrno>
#include <stdlib.h>
#include <sys/types.h>   
#include <arpa/inet.h>
#include <unistd.h>
#include <map>

#include "parceRequest.hpp"
#define BUFFER_SIZE 1024
using namespace std;
#define PORT 8080
#define MAP std::map<string, string>
size_t create_socket();
size_t bind_socket(size_t, MAP &);
size_t listen_and_accept(size_t , struct sockaddr *, socklen_t *, MAP &);
ssize_t listen_to_cnx(size_t , struct sockaddr *, socklen_t *);
string read_request(size_t);