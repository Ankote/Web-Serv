#include "web-server.hpp"
#include <fcntl.h>
int main()
{
    MAP map;
    bind_socket(create_socket(), map);
}

//sko 7nat