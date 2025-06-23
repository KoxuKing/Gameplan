#pragma once
#include "../Player.h"
#include <iostream>

struct CheckersPlayer : public Player
{
    sf::Color color;

    explicit CheckersPlayer(int playerNumber)
    {
        data.playerNumber = playerNumber;
        color = (playerNumber == 1) ? sf::Color::Red : sf::Color::Yellow;
    }

    ~CheckersPlayer() override = default;
};
