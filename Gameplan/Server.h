#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "ZipPacket.h"

class Server
{
public:

private:
	sf::TcpListener connectionListener;	// Listens if some client tries to connect to the server
	sf::TcpSocket connectingSocket;	// Client that is trying to connect to server
	sf::SocketSelector selector;	// List of sockets
	ZipPacket packet;				// Coming and going packets
	std::vector<sf::TcpSocket> connectedSocketList;  // List of connected sockets
	bool gameStarted;				// Determines if game is started
	unsigned short serverPort;		// server's open port
	std::string gameStartText;		// If text is start, game starts
	sf::Uint8 playerNumber;

	bool isClientConnecting();		// Checks if there is client that tries to connect to the server
	void acceptConnection();		// Accepts client to connect to the server
	void updateConnections();		// Wraps up connection functions and constantly going through them
	void updatePackets();			// Checks if there is coming packet and send it foward
	void sendPackets(sf::TcpSocket& senderSocket);	// Sends packet to everyone except the one who send it
	void updateServer();			// While loop which go through every function
	void gameOver();
};

