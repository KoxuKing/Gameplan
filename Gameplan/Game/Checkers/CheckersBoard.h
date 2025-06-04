#pragma once
#include "CheckersBoardSlot.h"
#include "CheckersPlayer.h"
#include <memory>

class CheckersBoard {
public:
    CheckersBoard(sf::Vector2i _size);

    // Board state methods
    std::vector<sf::Vector2i> getDiagonalMoves(CheckersPawn* selectedPawn, CheckersPlayer* player, bool can_player_eat);
    bool moveSelectedPawnToSquare(CheckersPawn* selected_pawn, CheckersPlayer* player, sf::Vector2i new_square);
    bool canPawnEat(CheckersPawn* _selected_pawn, CheckersPlayer* player);
    bool eatPawnsBetweenSlots(sf::Vector2i start_square, sf::Vector2i new_square);

    // Input handling methods
    int getColumn(int _mousePosX) const;
    int getRow(int _mousePosY) const;
    bool isSlotValid(sf::Vector2i slot);

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
    bool isPositionInBounds(const sf::Vector2i& pos) const;
    sf::CircleShape createPawnShape() const;
};