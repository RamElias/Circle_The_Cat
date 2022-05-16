#pragma once

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <memory>

#include "macros.h"
#include "ResourceManager.h"

class Board {
public:
    Board();

    void drawBoard(RenderWindow &) const;
    void setBlockCircles(const int level);
    void findMousePos(Vector2f &, const Vector2i&);
    bool findClick(Vector2f &, const Vector2i&);
    const BoardVector getBoard() const { return m_board; }
    const CircleShape &getCircle(size_t row, size_t col) { return m_board[row][col]; }
    bool isBlack(const int x, const int y) const { return m_board[x][y].getFillColor() == Color::Black; }
    void resetCircles();
    Vector2i getClikLogs() const { return m_clickLogs; }
    
    void whiteCircle(Vector2i& pos);

private:
    void setBoard();
    static CircleShape createCircle(Vector2f &);
    Vector2i m_clickLogs;
    BoardVector m_board;
};
