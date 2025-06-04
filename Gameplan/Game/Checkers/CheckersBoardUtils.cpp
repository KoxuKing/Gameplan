#include "CheckersBoard.h"

int CheckersBoard::getColumn(int _mousePosX) const
{
    // Goes through every column
    for (int c = 0; c < size.y; c++)
    {
        if (_mousePosX > slots[0][c].position.x && _mousePosX < (slots[0][c].position.x + slot_width))
            return c;
    }

    return -1;
}

int CheckersBoard::getRow(int _mousePosY) const
{
    // Goes through every column
    for (int r = 0; r < size.x; r++)
    {
        if (_mousePosY < slots[r][0].position.y + slot_height && _mousePosY >(slots[0][r].position.y))
            return r;
    }

    return -1;
}