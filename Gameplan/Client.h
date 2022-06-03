#pragma once
#include <SFML/Network.hpp>
#include "ZipPacket.h"
#include <iostream>

class Client
{

public:
	ZipPacket cryptedPacket;		// Crypted packet
	sf::Packet nonCryptedPacket;    // Non-crypted packet
	void connectToServer(sf::IpAddress& _address, unsigned short _port);	// Tries to connect to the server of given ip-address

	void startGame();		// Starts the game
	void endGame();

	template <typename T>
	void sendPacket(T& _message);
	sf::Packet receivePacket();

private:
	sf::TcpSocket clientSocket;
	sf::Socket::Status clientStatus;
};