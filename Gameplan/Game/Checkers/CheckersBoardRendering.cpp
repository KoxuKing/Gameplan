#include "CheckersBoard.h"

void CheckersBoard::drawBoard(Application* _application)
{
    sf::RectangleShape slot;

    slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
    slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

    slot.setSize(sf::Vector2f(slot_width, slot_height));
    slot.setOutlineColor(sf::Color::Black);
    slot.setOutlineThickness(BORDER_THICKNESS);

    for (int r = 0; r < size.x; r++) {
        for (int c = 0; c < size.y; c++) {

            sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * c), Y_OFFSET + static_cast<float>(slot_height * r) };

            // Draw slots
            slot.setPosition(slot_position);
            slots[r][c].position = slot_position;
            sf::Color slot_color = slots[r][c].color;
            slot.setFillColor(slot_color);
            _application->window.draw(slot);
        }
    }
}

void CheckersBoard::drawPawns(Application* _application)
{
    slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
    slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

    sf::CircleShape pawn = createPawnShape();

    for (int r = 0; r < size.x; r++) {
        for (int c = 0; c < size.y; c++) {
            if (slots[r][c].pawn)
            {
                sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * c), Y_OFFSET + static_cast<float>(slot_height * r) };
                pawn.setPosition(slot_position);
                sf::Color pawn_color = slots[r][c].pawn->color;
                pawn.setFillColor(pawn_color);
                _application->window.draw(pawn);

                // Draw a crown or indicator for kings
                if (slots[r][c].pawn->isKing) {
                    // Create a smaller circle inside to indicate a king
                    sf::CircleShape crown = createPawnShape();
                    float crownRadius = pawn.getRadius() * 0.5f;  // Smaller than the pawn
                    crown.setRadius(crownRadius);
                    crown.setPosition({ slot_position.x + pawn.getRadius()/2 , slot_position.y + pawn.getRadius() / 2 });
                    crown.setFillColor(sf::Color::White);  // White crown indicator
                    _application->window.draw(crown);
                }
            }
        }
    }
}

void CheckersBoard::drawPossibleMoves(Application* _application, BoardSlot& selected_slot)
{
    slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
    slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

    sf::CircleShape pawn = createPawnShape();

    if (selected_slot.pawn)
    {
        if (selected_slot.pawn->possible_moves.size() > 0)
        {
            for (int i = 0; i < selected_slot.pawn->possible_moves.size(); i++)
            {
                sf::Vector2i move = selected_slot.pawn->possible_moves[i];
                sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * move.x), Y_OFFSET + static_cast<float>(slot_height * move.y) };

                pawn.setPosition(slot_position);
                sf::Color pawn_color = selected_slot.pawn->color;
                pawn_color.a = PAWN_TRANSPARENCY_FOR_MOVES;
                pawn.setFillColor(pawn_color);
                _application->window.draw(pawn);
            }
        }
    }
}