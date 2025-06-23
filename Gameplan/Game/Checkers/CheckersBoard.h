#pragma once
#include "CheckersBoardSlot.h"
#include "CheckersPlayer.h"
#include <memory>

using BoardCoord = sf::Vector2i;
using Pawn = std::shared_ptr<CheckersPawn>;

struct MoveResult {
    bool isValid = false;
    bool didEat = false;
    sf::Vector2i eatenPawnCoord = { -1, -1 }; // Position of eaten pawn (if any)
};

struct selectedMove
{
    selectedMove(std::shared_ptr<CheckersPawn> _pawn, BoardCoord _move)
    {
        pawn = _pawn;
        move = _move;
    };

    std::shared_ptr<CheckersPawn> pawn{ nullptr };
    BoardCoord move{};
};

class CheckersBoard {
public:
    CheckersBoard(sf::Vector2i _size);

    // Board state methods
    std::vector<BoardCoord> getDiagonalMoves(CheckersPawn* selectedPawn, CheckersPlayer* player, bool can_player_eat);
    bool moveSelectedPawnToSquare(CheckersPawn* selected_pawn, CheckersPlayer* player, BoardCoord new_square);
    bool canPawnEat(CheckersPawn* _selected_pawn, CheckersPlayer* player);
    bool eatPawnsBetweenSlots(BoardCoord start_square, BoardCoord new_square);
    std::vector<Pawn> getMoveablePawns(CheckersPlayer* player);
    std::vector<selectedMove> getAllPawnMoves(std::vector<Pawn> pawns, CheckersPlayer* player);
    bool canPlayerEat(CheckersPlayer* player);

	int getNumberPlayerOfPawns(CheckersPlayer* player) const;

    // Input handling methods
    int getColumn(int _mousePosX) const;
    int getRow(int _mousePosY) const;
    bool isSlotValid(BoardCoord slot);

    // Rendering methods
    void drawBoard(Application* _application);
    void drawPawns(Application* _application);
    void drawPossibleMoves(Application* _application, BoardSlot& selected_slot);

    // Constants
    static constexpr float X_OFFSET = 20.0f;
    static constexpr float Y_OFFSET = 20.0f;
    static constexpr float BORDER_THICKNESS = 2.0f;
    static constexpr float PAWN_OUTLINE_THICKNESS = 2.0f;
    static constexpr float PAWN_TRANSPARENCY_FOR_MOVES = 100.0f;

    // Board data
    std::vector<std::vector<BoardSlot>> slots;
    sf::Vector2i size;
    float slot_width = 0;
    float slot_height = 0;

	

private:
    // Helper methods
    bool isPositionInBounds(const BoardCoord& pos) const;
    sf::CircleShape createPawnShape() const;
};