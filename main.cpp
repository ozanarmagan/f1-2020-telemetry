#define GLFW_DLL
#include <iostream>
#include "connection/udp_server.h"

int main(int argc, char** argv)
{
    udp_server(20777);
    return 0;
}   