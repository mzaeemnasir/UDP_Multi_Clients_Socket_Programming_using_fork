// UDP Socket Programming
// M Zaeem Nasir
// 19F 0355
// 5B

// Server.cpp
// ---------------------
// Creating Socket
// Binding Socket
// Listening for Client
// Accepting Client
// Sending Data
// Closing Socket
// ---------------------

#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <unistd.h>

using namespace std;
int main()
{
    int num1, num2, result;
    int Socket = socket(AF_INET, SOCK_DGRAM, 0);
    char Buffer[1024] = {0};
    if (Socket < 0)
    {
        cout << "Error in creating socket" << endl;
        return -1;
    }
    else
    {
        cout << "Socket Created" << endl;
    }

    struct sockaddr_in ServerAddress, ClientAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(3000);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    int Bind = bind(Socket, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
    if (Bind < 0)
    {
        cout << "Error in binding socket" << endl;
        return -1;
    }
    else
    {
        cout << "Socket Bound" << endl;
    }
    socklen_t ClientAddressLength = sizeof(ClientAddress);

    while (1)
    {
        int data = recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ClientAddress, &ClientAddressLength);
        if (data < 0)
        {
            exit(1);
        }
        cout << "Client Connected" << endl;
        if (fork() == 0)
        {

            ifstream inputfile;
            inputfile.open("textfile.txt");
            string line;
            while (getline(inputfile, line))
            {
                sendto(Socket, line.c_str(), sizeof(line), 0, (sockaddr *)&ClientAddress, ClientAddressLength);
            }
            inputfile.close();
        }
    }
    return 0;
}