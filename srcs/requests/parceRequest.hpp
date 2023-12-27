#pragma once
#include "catchRequest.hpp"
#include <map>
#include <sstream>
using namespace std;

void parceRequest(string inputString, MAP &map);
void fillMap(MAP &map, string &line);

typedef struct  s_request
{
    string request;
    string path;
    string version;
}               t_request;
