#include<iostream>
#include "macros.h"
#include <queue>
#include "Board.h"

class MoveObject 
{
public:
    MoveObject(const Board& board) : m_board(&board) {}

    Vector2i getNextMove(const BoardVector &,sf::Vector2i &);
    Vector2i getCatPos() { return m_place; }
    void setCatPos(const Vector2i& place) { m_place = place; }
    
    Vector2i randomMove(bool&);

    bool isBlack(const int x, const int y) const { return m_board->isBlack(x, y); }

    Board getBoard() { return *m_board; }
    
private:
    bool findShortPath(const BoardVector& board, bool vis[][BOARD_SIDE], sf::Vector2i& i, Vector2i prev[BOARD_SIDE][BOARD_SIDE]);

    sf::Vector2i reversePrev(Vector2i prev[BOARD_SIDE][BOARD_SIDE], const sf::Vector2i& e);

    void setArray(bool[][BOARD_SIDE]);
    bool isValid(const BoardVector&, bool[][BOARD_SIDE], const sf::Vector2i &);

    sf::Vector2i m_place;
    const Board* m_board;

};