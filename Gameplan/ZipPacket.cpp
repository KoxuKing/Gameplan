#include "ZipPacket.h"


/*sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
	return packet << character.age << character.name << character.weight;
}

sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
	return packet >> character.age >> character.name >> character.weight;
}*/


/*const void* ZipPacket::onSend(std::size_t& size)
{
	const void* srcData = getData();
	std::size_t srcSize = getDataSize();

	return compressTheData(srcData, srcSize, &size);
}*/

/*void ZipPacket::onReceive(const void* data, std::size_t size)
{
	std::size_t dstSize;
	const void* dstData = uncompressTheData(data, size, &dstSize); // this is a fake function, of course :)
	append(dstData, dstSize);
}*/
