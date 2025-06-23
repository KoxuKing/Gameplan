#include "CheckersBoard.h"

using BoardCoord = sf::Vector2i;
using Pawn = std::shared_ptr<CheckersPawn>;

std::vector<BoardCoord> CheckersBoard::getDiagonalMoves(CheckersPawn* selectedPawn, CheckersPlayer* player, bool can_player_eat)
{
    std::vector<sf::Vector2i> possible_moves;
    possible_moves.clear();

    // Direction vectors based on pawn color and king status
    std::vector<sf::Vector2i> directions;

    // Kings can move in all diagonal directions
    if (selectedPawn->color == player->color && selectedPawn->isKing) {
        // All four diagonal directions for kings
        directions = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
    }
    // Regular pawns can only move forward based on color
    else if (selectedPawn->color == player->color && player->color == sf::Color::Red) {
        directions = { {-1, 1}, {1, 1} }; // down-left, down-right
    }
    else if (selectedPawn->color == player->color && player->color == sf::Color::Yellow) {
        directions = { {-1, -1}, {1, -1} }; // up-left, up-right
    }
    else {
        return possible_moves; // Not player's pawn
    }

    // Check each direction
    for (const auto& dir : directions) {
        sf::Vector2i diagonal_1 = { selectedPawn->board_slot.x + dir.x, selectedPawn->board_slot.y + dir.y };
        sf::Vector2i diagonal_2 = { selectedPawn->board_slot.x + 2 * dir.x, selectedPawn->board_slot.y + 2 * dir.y };

        // Check if position is valid
        if (isPositionInBounds(diagonal_1)) {
            if (slots[diagonal_1.y][diagonal_1.x].pawn) {
                // Check for eat move
                if (slots[diagonal_1.y][diagonal_1.x].pawn->color != selectedPawn->color &&
                    isPositionInBounds(diagonal_2) &&
                    !slots[diagonal_2.y][diagonal_2.x].pawn) {
                    possible_moves.push_back(diagonal_2);
                }
            }
            else if (!can_player_eat) {
                // Regular move
                possible_moves.push_back(diagonal_1);
            }
        }
    }

    return possible_moves;
}

bool CheckersBoard::moveSelectedPawnToSquare(CheckersPawn* selected_pawn, CheckersPlayer* player, BoardCoord new_square)
{
    if (!selected_pawn->HasThisMove(new_square)) {
        return false;
    }

    bool successfulEat = eatPawnsBetweenSlots(selected_pawn->board_slot, new_square);

    // Create new pawn at the target position
    auto movedPawn = std::make_shared<CheckersPawn>(selected_pawn->color, new_square);

    // Preserve king status if the pawn was already a king
    movedPawn->isKing = selected_pawn->isKing;

    // Check if pawn should be promoted to king (reached the last row)
    if (!movedPawn->isKing) {
        // Red pawns move downward, become kings at the bottom row
        if (movedPawn->color == sf::Color::Red && new_square.y == size.x - 1) {
            movedPawn->isKing = true;
        }
        // Yellow pawns move upward, become kings at the top row
        else if (movedPawn->color == sf::Color::Yellow && new_square.y == 0) {
            movedPawn->isKing = true;
        }
    }

    // Store the moves before erasing the old pawn
    auto moves = selected_pawn->possible_moves;

    // Update board state
    slots[new_square.y][new_square.x].pawn = movedPawn;
    slots[selected_pawn->board_slot.y][selected_pawn->board_slot.x].pawn = nullptr;

    // Check for additional eat moves if we just ate a pawn
    if (successfulEat) {
        auto additionalMoves = getDiagonalMoves(movedPawn.get(), player, true);
        if (!additionalMoves.empty()) {
            movedPawn->possible_moves = additionalMoves;
            return false; // Player must continue eating
        }
    }

    return true;
}

bool CheckersBoard::eatPawnsBetweenSlots(BoardCoord start_square, BoardCoord new_square)
{
    int distance_x = new_square.x - start_square.x;
    int distance_y = new_square.y - start_square.y;

    if (std::abs(distance_x) == 2 && std::abs(distance_y) == 2)
    {
        BoardSlot& target_slot = slots[new_square.y][new_square.x];
        BoardSlot& check_slot = slots[start_square.y + (distance_y / 2)][start_square.x + (distance_x / 2)];

        if (check_slot.pawn && !target_slot.pawn)
        {
            check_slot.pawn.reset(); // Remove the pawn that was eaten
            return true;
        }
    }
    return false;
}

std::vector<Pawn> CheckersBoard::getMoveablePawns(CheckersPlayer* player)
{
    bool can_player_eat = false;
	bool take_only = false; // If true, only return pawns that can eat
    std::vector<Pawn> moveable_pawns = {};

    for (int r = 0; r < slots.size(); r++)
    {
        for (int c = 0; c < slots[0].size(); c++)
        {
            if (slots[r][c].pawn && slots[r][c].pawn->color == player->color)
            {
                can_player_eat = canPawnEat(slots[r][c].pawn.get(), player);

                if (can_player_eat && !take_only)
                {
					take_only = true; // If player can eat, only return pawns that can eat
					moveable_pawns.clear();
                }

				if (take_only && !can_player_eat)
					continue; // Skip pawns that cannot eat if player can eat
				
                if (getDiagonalMoves(slots[r][c].pawn.get(), player, can_player_eat).size() > 0)
                    moveable_pawns.push_back(slots[r][c].pawn);

            }
        }
    }
    return moveable_pawns;
}

std::vector<selectedMove> CheckersBoard::getAllPawnMoves(std::vector<Pawn> pawns, CheckersPlayer* player)
{
    std::vector<selectedMove> selectedMoves{ {} };
    bool can_player_eat = canPlayerEat(dynamic_cast<CheckersPlayer*>(player));

    for (auto& pawn : pawns)
    {
        pawn->possible_moves = getDiagonalMoves(pawn.get(), dynamic_cast<CheckersPlayer*>(player), can_player_eat);
        for (auto& move : pawn->possible_moves)
            selectedMoves.push_back(selectedMove(pawn, move));
    }

    return selectedMoves;
}

bool CheckersBoard::canPlayerEat(CheckersPlayer* player)
{
    for (int r = 0; r < size.x; r++)
    {
        for (int c = 0; c < size.y; c++)
        {
            if (slots[r][c].pawn && slots[r][c].pawn->color == player->color)
            {
                if (canPawnEat(slots[r][c].pawn.get(), player))
                    return true;
            }
        }
    }
    return false;
}

int CheckersBoard::getNumberPlayerOfPawns(CheckersPlayer* player) const
{
	int count = 0;

    for (int r = 0; r < size.y; r++)
    {
        for (int c = 0; c < size.x; c++)
        {
            if (slots[r][c].pawn && slots[r][c].pawn->color == player->color)
                count++;
        }
	}

	return count;
}

//void CheckersBoard::cloneBoard(CheckersBoard& clone)
//{
//    clone.size = this->size;
//    clone.slots.clear();
//    clone.slots.resize(size.y, std::vector<BoardSlot>(size.x));
//    for (int r = 0; r < size.y; r++)
//    {
//        for (int c = 0; c < size.x; c++)
//        {
//            clone.slots[r][c].color = slots[r][c].color;
//            if (slots[r][c].pawn)
//            {
//                clone.slots[r][c].pawn = std::make_shared<CheckersPawn>(*slots[r][c].pawn);
//                clone.slots[r][c].pawn->board_slot = sf::Vector2i(c, r);
//            }
//        }
//	}
//}

bool CheckersBoard::canPawnEat(CheckersPawn* selected_pawn, CheckersPlayer* player)
{
    auto possible_moves = getDiagonalMoves(selected_pawn, player, false);
    for (int i = 0; i < possible_moves.size(); i++)
    {
        sf::Vector2i move = possible_moves[i];
        if (std::abs(move.x - selected_pawn->board_slot.x) > 1) // moveHopsOverPawn(move)
            return true;
    }
    return false;
}



bool CheckersBoard::isSlotValid(BoardCoord slot)
{
    return slot.x > -1 && slot.y > -1;
}