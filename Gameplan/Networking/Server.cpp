#include "Server.h"

bool Server::isClientConnecting()
{
	if (connectionListener.listen(serverPort) != sf::Socket::Done)
	{
		return false;
	}
	else
		return true;
}

void Server::acceptConnection()
{
	sf::TcpSocket* connectingSocket = new sf::TcpSocket;	// Client that is trying to connect to server
	if (connectionListener.accept(*connectingSocket) == sf::Socket::Done)
	{
		// Adds new client to lists
		connectedSocketList.push_back(connectingSocket);
		selector.add(*connectingSocket);
		playerNumber += 1;

		// Gives player number
		packet << playerNumber;
		connectingSocket->send(packet);
		packet.clear();
	}
	else
		std::cout << "Error on accepting new connection." << std::endl;

}

void Server::updateConnections()
{
	if (isClientConnecting())
	{
		acceptConnection();
	}
}

void Server::updatePackets()
{
	// Checks if there is packet waiting for receiving
	if (selector.wait(sf::seconds(10.f)))
	{
		for (auto socket : connectedSocketList)
		{
			if (selector.isReady(*socket))
			{
				socket->receive(packet);

				// If game isnt started yet, server checks what packet includes so it knows when game need to starts
				if (!gameStarted)
				{
					packet >> gameStartText;
					if (gameStartText == "start")
						gameStarted = true;
				}

				sendPackets(*socket);
			}
		}
	}
}

void Server::sendPackets(sf::TcpSocket& senderSocket)
{
	// Sends packet to every socket, except the one who send the packet
	for (auto& socket : connectedSocketList)
	{
		if (socket->getRemoteAddress() == senderSocket.getRemoteAddress())
			continue;
		else
		{
			//Sends packet
			if (socket->send(packet) == sf::Socket::Partial)
			{
				std::cout << "Error on sending packet, trying again." << std::endl;
				if (socket->send(packet) == sf::Socket::Partial)
					std::cout << "Can't send the packet to " << socket->getRemoteAddress() << std::endl;
			}
		}
	}
	// Clears packet
	packet.clear();
}

void Server::updateServer()
{
	while (true)
	{
		if (!gameStarted)
			updateConnections();

		updatePackets();
	}
}

void Server::gameOver()
{
	for (auto socket : connectedSocketList)
	{
		socket->disconnect();
		delete socket;
	}
	connectedSocketList.empty();
	selector.clear();
	playerNumber = 0;
	gameStarted = false;
	packet.clear();
}