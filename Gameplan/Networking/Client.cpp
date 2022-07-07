#include "Client.h"

void Client::connectToServer(sf::IpAddress& _address, unsigned short _port)
{
	clientStatus = clientSocket.connect(_address, _port, sf::seconds(10.f));		// Connects client to server

	if (clientStatus != sf::Socket::Done)
	{
		std::cout << "Error on connecting server." << std::endl;
	}
	else clientSocket.send("test", 4);
}

void Client::startGame()
{
	cryptedPacket << "start";

	if (clientSocket.send(cryptedPacket) != sf::Socket::Done)
	{
		std::cout << "Error on starting the game." << std::endl;
	}
	cryptedPacket.clear();
}

void Client::endGame()
{
	cryptedPacket << "end";
	if (clientSocket.send(cryptedPacket) != sf::Socket::Done)
	{
		std::cout << "Error on ending the game." << std::endl;
	}
	cryptedPacket.clear();
}

template <typename T>
void Client::sendPacket(T& _message)
{
	cryptedPacket << _message;

	clientSocket.send(cryptedPacket);

	cryptedPacket.clear();
}

sf::Packet Client::receivePacket()
{
	clientSocket.receive(cryptedPacket);
	return cryptedPacket;
}