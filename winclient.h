#ifndef WINCLIENT_H

#define WINCLIENT_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <Qstring>
#include <QList>
#include <cstring>
#include <sstream>
#include <vector>

#define DEFAULT_BUFFER 512

#define DEFAULT_ADRESS "86.123.39.137"

#define DEFAULT_PORT "4000"

#define ZERO_TIMEOUT 0

class WinSocket {
    addrinfo *result, *ptr, hints;
    //SOCKET socket_connect;
    int startup;

public:
    SOCKET socket_connect;

    WinSocket();
    ~WinSocket();
    bool getAdrressAndPort(char *, char *);
    bool createWinsock();
    bool connectToSocket();
    void sendData(const char *, size_t);
    int receiveData(char *);
    bool disconnect();
    bool poll();
};

#endif
