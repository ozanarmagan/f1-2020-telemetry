#include "udp_server.h"
#include "../parser/parser.h"
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

using namespace std;

#pragma comment(lib,"ws2_32.lib")

void udp_server(unsigned short port)
{
    WSADATA wsa;
    cout << "Initializing WinSock" << endl;

    if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cout << "Fail on initialization" << WSAGetLastError();
        exit(EXIT_FAILURE);
    }

    SOCKET sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock == SOCKET_ERROR)
    {
        cout << "Socket Creation Error" << WSAGetLastError();
        exit(EXIT_FAILURE);
    }

    cout << "Connection established" <<endl;

    SOCKADDR_IN si_other = {};
    int slen = sizeof(si_other);
    si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	si_other.sin_addr.s_addr = INADDR_ANY;

    int result = bind(sock,(SOCKADDR*)&si_other,sizeof(si_other));
    if (result == SOCKET_ERROR) {
        cout << "Socket bind failed. Error: " << WSAGetLastError() << endl;
        exit(1);
    }

    cout << "Socket binded" << endl << "Waiting for data to receive..." << endl;

    char buffer[BUFFER_SIZE*2];
    int read;

    bool flag = false;
    while(1)
    {
        read = recvfrom(sock,buffer,BUFFER_SIZE*2,0,(SOCKADDR *)&si_other, &slen);

        if(read == SOCKET_ERROR)
            cout << "Recieving data has failed " << WSAGetLastError() << endl;
        if(!flag)
        {
            system("cls");
            flag = true;
        }
        else
        {
            parse(buffer);   
        }
    }

}