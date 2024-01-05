#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <utility>
#include <sys/socket.h>

// Structure to represent the header of a message.
struct MessageHeader {
    size_t messageLength;
};

// Structure to represent a message.
struct Message {
    MessageHeader messageHeader;
    std::string payload;

    // Constructor to initialize a Message object with given data.
    Message(const std::string& data);
};

// Function to send a message.
// Takes a message header, a buffer, and a socket file descriptor as input.
// Returns the result of the send operation.
int sendMessage(const MessageHeader &header, const void *buf, int sockfd);

// Wrapper function for sending messages.
// Takes a socket file descriptor, a buffer, its size, and a flag as input.
// Returns the result of the sendMessage operation.
int sendWrapper(int sockfd, const void *buf, size_t n, int flag);

// Function to receive a message.
// Takes a socket file descriptor as input.
// Returns a pair of MessageHeader and string, containing the received message.
std::pair<MessageHeader, std::string> receiveMessage(int sockfd);

// Function to receive a message using a pointer.
// Takes a socket file descriptor and a string payload as input.
// Returns a pair of MessageHeader and string, containing the received message.
std::pair<MessageHeader, std::string> receiveMessagePointer(int sockfd, std::string payload);

// Wrapper function for receiving messages.
// Takes a socket file descriptor, a buffer, its size, and flags as input.
// Does not return a value.
int receiveWrapper(int sockfd, void *buf, size_t n, int flags);

#endif // NETWORK_H
