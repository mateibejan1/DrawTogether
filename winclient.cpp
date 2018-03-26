#include <QDebug>
#include "winclient.h"
#include "request.h"

WinSocket::WinSocket() : result(NULL), ptr(NULL), socket_connect(INVALID_SOCKET) {
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    startup = WSAStartup(wVersionRequested, &wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

WinSocket::~WinSocket(){
    if(disconnect())
        qDebug()<<"Disconnected from server.\n";
}

bool WinSocket::getAdrressAndPort(char *address_info, char *port = DEFAULT_PORT){
    if(startup == 0){
        int get_connect = getaddrinfo(address_info, DEFAULT_PORT, &hints, &result);
        if(get_connect != 0){
            qDebug()<<"Could not get address and port "<<get_connect<<".\n";
            WSACleanup();
            return false;
        }
        return true;
    }
    else{
        qDebug()<<"WSAStartup error.\n";
        return false;
    }
}

bool WinSocket::createWinsock(){
    ptr = result;
    socket_connect = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(socket_connect == INVALID_SOCKET){
        qDebug()<<"Could not connect to socket.\n";
        WSACleanup();
        return false;
    }
    return true;
}

bool WinSocket::connectToSocket(){
    if(startup == 0){
        int _conn_result_ = connect(socket_connect, ptr->ai_addr, (int) ptr->ai_addrlen);
        if(_conn_result_ == SOCKET_ERROR){
            closesocket(socket_connect);
            socket_connect = INVALID_SOCKET;
        }
        freeaddrinfo(result);
        if(socket_connect == INVALID_SOCKET){
            qDebug()<<"Could not connect to server: "<<WSAGetLastError()<<".\n";
            WSACleanup();
            return false;
        }

        SREQUEST rekt = SREQUEST::E_ON_CONNECT;
        const char *send_this = reinterpret_cast <const char *> (&rekt);
        sendData(send_this, 4);

        return true;
    }
    else{
        qDebug()<<"WSAStartup error.\n";
        return false;
    }
}

bool WinSocket::disconnect(){
    int _shut_result_ = shutdown(socket_connect, SD_SEND);
    if(_shut_result_ == SOCKET_ERROR){
        qDebug()<<"Failed to disconnect from server: "<<WSAGetLastError()<<".\n";
        closesocket(socket_connect);
        WSACleanup();
        return false;
    }
    closesocket(socket_connect);
    WSACleanup();
    return true;
}

void WinSocket::sendData(const char *string_to_send, size_t size_of_string) {
    //char *string_to_send1 = "g";
    //qDebug()<<strlen(string_to_send1)<<" ";
    //while(1){
        int socket_fd = socket_connect;
        timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        fd_set write_set;
        FD_ZERO(&write_set);
        FD_SET(socket_fd, &write_set);

        //while(!select(socket_fd + 1, NULL, &write_set, NULL, &tv) > 0);

        //see if descriptors is available for reading

        if(select(socket_fd + 1, NULL, &write_set, NULL, &tv) > 0){
            int _sent_ = send(socket_connect, string_to_send, size_of_string, 0);
            qDebug()<<"Sent data: "<<_sent_<<"\n";
            if(_sent_ == SOCKET_ERROR){
                qDebug()<<"Sent failed: "<<WSAGetLastError()<<".\n";
                closesocket(socket_connect);
                WSACleanup();
            }
        }
}

int WinSocket::receiveData(char *string_to_receive) {
    int _received_;
    do{
        _received_ = recv(socket_connect, string_to_receive, DEFAULT_BUFFER, 0);
        string_to_receive[_received_ - 1] = '\0';
        if(_received_ > 0){
            qDebug()<<"Bytes received: "<<_received_<<"\n";
            return _received_;
        }
        else
            if(_received_ == 0){
                qDebug()<<"Connection closed.\n";
                break;
            }
            else{
                qDebug()<<"Data receiving failed: "<<WSAGetLastError()<<".\n";
                break;
            }
    }while(_received_ > 0);
}

bool WinSocket::poll(){
    int socket_fd = socket_connect, result;
    fd_set readset;
    char strbuff[DEFAULT_BUFFER];
    char receive[DEFAULT_BUFFER];
    timeval tv;

    tv.tv_sec = ZERO_TIMEOUT;
    tv.tv_usec = ZERO_TIMEOUT;
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(socket_fd, &read_set);
    if(select(socket_fd + 1, &read_set, nullptr, nullptr, &tv) > 0)
        return true;
    else
        return false;

}
