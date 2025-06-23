#pragma once
#include "../CheckersPlayer.h"
#include "../CheckersTable.h"

using BoardCoord = sf::Vector2i;

struct CheckersAI : public CheckersPlayer
{
public:
    explicit CheckersAI(int playerNumber) : CheckersPlayer(playerNumber) {}
    ~CheckersAI() override = default;

    bool makeMove(CheckersBoard& board, CheckersTable* table);

private:
    
	int move_points = 0;
	int max_iterations = 5;
    int iterations = 0;

    std::vector<selectedMove> best_moves{ {} };
    std::vector<selectedMove> getBestMoves(std::vector<selectedMove>& moves, CheckersBoard& board);
	int getMinMaxScore(selectedMove move, CheckersBoard clone_board);

    // TEST
    std::vector<std::vector<selectedMove>> getMoves(std::vector<selectedMove>& moves, CheckersBoard board, CheckersPlayer* player, std::vector<std::vector<selectedMove>>&);

    std::vector<std::vector<selectedMove>> allPawnMoves{};

};