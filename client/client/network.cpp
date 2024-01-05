// Server.cpp
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <algorithm>


struct MessageHeader {
    size_t messageLength;
};

struct Message {
    MessageHeader messageHeader;
    std::string payload;

    Message(const std::string& data)
        : messageHeader{static_cast<int>(data.size())}, payload(data) {}
};



int sendMessage(const MessageHeader &header, const void *buf, int sockfd)
{
    printf("now send the message\n");
    auto a = send(sockfd, &header, sizeof(header), 0);
    auto b = send(sockfd, buf, header.messageLength, 0);
    printf("sent the message\n");
    return b;
}

int sendWrapper(int sockfd, const void *buf, size_t n, int flag) {
    MessageHeader header;
    header.messageLength = n;
    return sendMessage(header, buf, sockfd);
}


std::pair<MessageHeader, std::string> receiveMessage(int sockfd)
{
    MessageHeader header;
    ssize_t bytesRead = recv(sockfd, &header, sizeof(header), 0);
    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message header or connection closed" << std::endl;
        return {};
    }

    std::string payload(header.messageLength, '\0');
    bytesRead = recv(sockfd, &payload[0], header.messageLength, 0);
    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message payload or connection closed" << std::endl;
        return {};
    }

    return {header, payload};
}

std::pair<MessageHeader, std::string> receiveMessagePointer(int sockfd, std::string payload)
{
    printf("got a message from server");
    MessageHeader header;
    ssize_t bytesRead = recv(sockfd, &header, sizeof(header), 0);
    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message header or connection closed" << std::endl;
        return {};
    }
    // std::string payload(header.messageLength, '\0');
    bytesRead = recv(sockfd, &payload[0], header.messageLength, 0);
    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message payload or connection closed" << std::endl;
        return {};
    }

    return {header, payload};
}


int receiveWrapper(int sockfd, void *buf, size_t n, int flags) {
    MessageHeader header;
    ssize_t bytesRead = recv(sockfd, &header, sizeof(header), 0);

    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message header or connection closed" << std::endl;
    }
    // std::string payload(header.messageLength, '\0');
    bytesRead = recv(sockfd, buf, header.messageLength, 0);
    if (bytesRead <= 0)
    {
        std::cout << "Failed to read message payload or connection closed" << std::endl;
    }
    return bytesRead;

}
