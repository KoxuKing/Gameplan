#pragma once
#include <SFML/Network.hpp>


class ZipPacket : public sf::Packet
{
public:
	friend sf::Packet operator << (sf::Packet& packet, const class Game& player);
	friend sf::Packet operator >> (sf::Packet& packet, const class Game& player);
private:
	//virtual const void* onSend(std::size_t& size);

	//virtual void onReceive(const void* data, std::size_t size);

};