#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 1111

int main(int argc, char const *argv[])
{
	// Loading of required
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		exit(1);
	}
	int valread, valread2;
	SOCKADDR_IN address;
	int addrlen = sizeof(address);
	// First field
	char buffer[401] = { 0 };
	// Second field
	char buffer2[401] = { 0 };
	int game = 0;
	// Socket info
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR *)&address, addrlen);
	listen(sListen, SOMAXCONN);
	while (true)
	{
		SOCKET first;
		// First player
		first = accept(sListen, (SOCKADDR *)&address, &addrlen);
		SOCKET second;
		// Second player
		second = accept(sListen, (SOCKADDR *)&address, &addrlen);
		// Start for both players
		send(second, "start\0", 6, 0);
		send(first, "start\0", 6, 0);
		game = 1;
		while (game == 1)
		{
			// Reading of the first field
			valread = recv(first, buffer, 401, 0);
			// Readind of the second field
			valread2 = recv(second, buffer2, 401, 0);
			// Sending of the first field to the second player
			send(second, buffer, 401, 0);
			// Sending of the second field to the first player
			send(first, buffer2, 401, 0);
			// End
			if ((buffer[0] == 'e') || (buffer2[0] == 'e'))
			{
				game = 0;
			}

		}
	}
	return 0;
}