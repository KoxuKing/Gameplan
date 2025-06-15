#include "CheckersBoard.h"

std::vector<sf::Vector2i> CheckersBoard::getDiagonalMoves(CheckersPawn* selectedPawn, CheckersPlayer* player, bool can_player_eat)
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

bool CheckersBoard::moveSelectedPawnToSquare(CheckersPawn* selected_pawn, CheckersPlayer* player, sf::Vector2i new_square)
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

bool CheckersBoard::eatPawnsBetweenSlots(sf::Vector2i start_square, sf::Vector2i new_square)
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

bool CheckersBoard::isSlotValid(sf::Vector2i slot)
{
    return slot.x > -1 && slot.y > -1;
}