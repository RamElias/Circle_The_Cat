#pragma once

#include "MoveObject.h"
#include "macros.h"
#include <SFML/Graphics.hpp>

class Cat  : public MoveObject 
{
public:
    Cat(const Board &);
    void showCat(RenderWindow& window); 
    void move();
    bool checkCatWon();
    bool checkCatLost() { return m_catLost; }
    void setCatLost(bool bol) { m_catLost = bol; }
    void setCatBlock(bool bol) { m_block = bol; }
    void setCatSprite(const sf::Vector2i&);


private:

    Sprite m_catSprite;

    std::vector<sf::Vector2f> m_delta;

    sf::Vector2f m_oldSprite{ 550,420 };

    bool m_block = false;
    bool m_catLost = false;
    bool m_animation = false;

    int m_num = 0;
};
