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
	template <typename T>
	void sendMessage(T& _message);
	sf::Packet receivePacket();

private:
	sf::TcpSocket clientSocket;
	sf::Socket::Status clientStatus;
};