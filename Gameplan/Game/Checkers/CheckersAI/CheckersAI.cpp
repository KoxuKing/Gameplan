#include "CheckersAI.h"
#include <random>

using BoardCoord = sf::Vector2i;

bool CheckersAI::makeMove(CheckersBoard& board, CheckersTable* table)
{

	std::vector<std::shared_ptr<CheckersPawn>> moveable_pawns = board.getMoveablePawns(dynamic_cast<CheckersPlayer*>(this));

	if (moveable_pawns.empty()) {
		return {}; // No pawns to move
	}

	
	

	std::vector<selectedMove> pawnMoves = board.getAllPawnMoves(moveable_pawns, dynamic_cast<CheckersPlayer*>(this));

	move_points = -10000;
	CheckersBoard clone_board = board;
	allPawnMoves = {};
	//getMoves(pawnMoves, clone_board, dynamic_cast<CheckersPlayer*>(this), allPawnMoves);
	best_moves = getBestMoves(pawnMoves, clone_board);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, best_moves.size() - 1);
	int randomIndex = dist(gen);

	selectedMove selected_move = best_moves[randomIndex];

	return board.moveSelectedPawnToSquare(selected_move.pawn.get(), dynamic_cast<CheckersPlayer*>(this), selected_move.move);
}

std::vector<selectedMove> CheckersAI::getBestMoves(std::vector<selectedMove>& moves, CheckersBoard& board)
{
	std::vector<selectedMove> minMaxMoves;

	int score = 0;
	iterations++;

	for (auto& move : moves) {

		score = getMinMaxScore(move, board);

		if (score > move_points) {
			move_points = score;
			minMaxMoves.clear();
			minMaxMoves.push_back(move);
		}
		else if (score == move_points) {
			minMaxMoves.push_back(move);
		}
	}
	std::cout << "Score: " << move_points << std::endl;
	return minMaxMoves;
}



int CheckersAI::getMinMaxScore(selectedMove move, CheckersBoard clone_board)
{
	std::unique_ptr<CheckersPlayer> opponent;

	if (color == sf::Color::Yellow)
		opponent = std::make_unique<CheckersPlayer>(1);
	else
		opponent = std::make_unique<CheckersPlayer>(2);

	int points = 0;

	bool succesful_eat = clone_board.moveSelectedPawnToSquare(move.pawn.get(), dynamic_cast<CheckersPlayer*>(this), move.move);

	/*std::vector<selectedMove> nextMoves = clone_board.getAllPawnMoves(clone_board.getMoveablePawns(human_player.get()), human_player.get());

	for (auto& move : nextMoves) {
		clone_board.moveSelectedPawnToSquare(move.pawn.get(), human_player.get(), move.pawn->possible_moves[0]);

		int score = getMinMaxScore(move, clone_board);
		if (score > points) {
			points = score;
		}
	}*/
	if (succesful_eat)
		points += 10;

	if (clone_board.canPlayerEat(opponent.get()))
		points -= 10; // Arbitrary value for eating a pawn
	else
		points += 1; // Arbitrary value for a normal move

	return points;
}

std::vector<std::vector<selectedMove>> CheckersAI::getMoves(std::vector<selectedMove>& moves, CheckersBoard clone_board, CheckersPlayer* player, std::vector<std::vector<selectedMove>>& _allpawnMoves)
{
	iterations++;
	std::vector<selectedMove> pawnMoves{};

	std::unique_ptr<CheckersPlayer> opponent;

	if (color == sf::Color::Yellow)
		opponent = std::make_unique<CheckersPlayer>(1);
	else
		opponent = std::make_unique<CheckersPlayer>(2);

	//if (iterations < max_iterations)
	//{
		for (auto& move : moves) {
			CheckersBoard board = clone_board;
			board.moveSelectedPawnToSquare(move.pawn.get(), player, move.move);

			std::vector<std::shared_ptr<CheckersPawn>> moveable_pawns = board.getMoveablePawns(opponent.get());
			pawnMoves = board.getAllPawnMoves(moveable_pawns, opponent.get());
			_allpawnMoves.push_back(pawnMoves);

			getMoves(pawnMoves, board, opponent.get(), _allpawnMoves);

		}
	//}

	return allPawnMoves;
}


