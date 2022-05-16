#include "Board.h"

//-------------------------------------
Board::Board()
{
    setBoard();
}

//-------------------------------------
//cretaing the circle on the board
void Board::setBoard() 
{
    Vector2f pos = {LEFT_CORNER, 120};
    for (size_t i = 0; i < BOARD_SIDE; i++)
    {
        std::vector<CircleShape> circleVec;
        for (size_t j = 0; j < BOARD_SIDE; j++) 
        {
            CircleShape circle = createCircle(pos);
            circleVec.push_back(circle);
            pos.x += WIDTH_DISTANCE;
        }
        m_board.push_back(circleVec);
        pos.y += HIEGHT_DISTANCE;
        
        if (i % 2 == 0)
            pos.x = LEFT_CORNER + EVEN_DISTANCE;
        else
            pos.x = LEFT_CORNER; 
    }
}

//-------------------------------------
CircleShape Board::createCircle(Vector2f &pos)
{
    CircleShape circle(CIRCLE_SIZE);
    circle.setPosition(pos);
    circle.setFillColor(Color{ 249, 231, 159 });
    circle.setOutlineColor(Color::Black);
    circle.setOutlineThickness(5);
    return circle;
}

//-------------------------------------

void Board::drawBoard(RenderWindow &window) const {
    for (auto const &i: m_board)
        for (auto const &j: i)
            window.draw(j);
}

//-------------------------------------

void Board::findMousePos(Vector2f &loc,
                         const Vector2i &catLoc)
{
    for (int i = 0; i < BOARD_SIDE; i++)
        for (int j = 0; j < BOARD_SIDE; j++)
            if (m_board[i][j].getGlobalBounds().contains(loc))
            {
                m_board[i][j].getFillColor() == Color::Black ||
                (i == catLoc.x && j == catLoc.y) ?
                m_board[i][j].setOutlineColor(Color{ 229, 57, 53 }) :
                    m_board[i][j].setOutlineColor(Color{ 133, 193, 233 });
                m_board[i][j].setOutlineThickness(4);
                return;
            } 
            else 
            {
                m_board[i][j].setOutlineColor(Color::Black);
                m_board[i][j].setOutlineThickness(3);
            }
}

//-------------------------------------

bool Board::findClick(Vector2f &loc,
                      const Vector2i &catLoc) {
    for (int i = 0; i < BOARD_SIDE; i++)
        for (int j = 0; j < BOARD_SIDE; j++)
            if (m_board[i][j].getGlobalBounds().contains(loc)) {
                if (m_board[i][j].getFillColor() == Color::Black
                    || (i == catLoc.x && j == catLoc.y))
                    return false;
                else
                    m_clickLogs = { int(i), int(j) };
                    m_board[i][j].setFillColor(Color::Black);
                return true;
            }
    return false;
}

//-------------------------------------

void Board::setBlockCircles(const int level) {
    int size = 14 - (level*4), x, y;
    srand((unsigned int)time(NULL));
    for (int i = 0; i <= size; ++i)
    {
        x = rand() % BOARD_SIDE;
        y = rand() % BOARD_SIDE;
        if (x == 5 && y == 5) //the cat start place
        {
            i--;
            continue;
        }
        m_board[x][y].setFillColor(Color::Black);
    }
}

//-------------------------------------

void Board::resetCircles() 
{
    for (auto &i : m_board )
    {
       for(auto& j: i)
        j.setFillColor(Color{ 249, 231, 159 });
    }
}
//-------------------------------------

void Board::whiteCircle(Vector2i& pos) 
{
    m_board[size_t(pos.x)][size_t(pos.y)].setFillColor(Color{ 249, 231, 159 });
}