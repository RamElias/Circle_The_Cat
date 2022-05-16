#include "Cat.h"

//-------------------------------------
Cat::Cat(const Board& board) : MoveObject(board), m_block(false) 
{
    m_catSprite.setTexture(ResourceManager::instance().getTexture());
    setCatPos(sf::Vector2i(5, 5));
    m_catSprite.setPosition(getBoard().getCircle(5, 5).getPosition());
    m_catSprite.setScale(float(1.5), float(1.5));
}


//-------------------------------------
//drawing the cat after calculating the animation steps if nedded

void Cat::showCat(RenderWindow& window)
{
    if (m_animation && m_delta.empty())
    {
        sf::Vector2f NewPos = m_catSprite.getPosition();

        float deltaX = (NewPos.x - m_oldSprite.x);
        float deltaY = (NewPos.y - m_oldSprite.y);

        deltaX = deltaX / 5;
        deltaY = deltaY / 5;

        //creating the next 5 steps for the animation
        for (int num = 1; num <= 5; num++)
        {
            sf::Vector2f calc(m_oldSprite.x + (deltaX * num), m_oldSprite.y + (deltaY * num));
            m_delta.push_back(calc);
        }
        m_animation = false;
    }

    //seting the animation steps
    if (!m_delta.empty() )
    {
        window.setFramerateLimit(30);
        m_catSprite.setPosition(m_delta[m_num]);
        m_num++;
        if (m_num == 5)
        {
            m_num = 0;
            m_delta.clear();
            window.setFramerateLimit(60);
        }
    }

    window.draw(m_catSprite);
}

//-------------------------------------
void Cat::setCatSprite(const sf::Vector2i &nextMove) {
    m_catSprite.setPosition(getBoard().getCircle(nextMove.x, nextMove.y).getPosition());
}

//-------------------------------------
//seting the cat next move via the bfs or rand algo
void Cat::move() {
    Vector2i newMove;

    //trying bfs algo
    if (!m_block)
    {
        sf::Vector2i place = getCatPos();
        newMove = getNextMove(getBoard().getBoard(), place);
      
        if (newMove == getCatPos())
            m_block = true;
    }
    
    //the cat is blocked so rand algo 
    if(m_block)
    {
       newMove = randomMove(m_catLost);
    }
    
    //for the animation
    m_animation = true;
    m_oldSprite = m_catSprite.getPosition();

    setCatSprite(newMove);
    setCatPos(newMove);
}

//-------------------------------------
bool Cat::checkCatWon()  
{
    sf::Vector2i place = getCatPos();
    if (place.x == BOARD_SIDE-1  || place.x == 0
        || place.y == BOARD_SIDE-1  || place.y == 0)
    return true;

    return false;
}
