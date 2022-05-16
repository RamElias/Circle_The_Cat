#include "Screen.h"

//-------------------------------------
Screen::Screen()
{
	setTexts();
}

//-------------------------------------
// set the texts on the screen
void Screen::setTexts()
{
	Vector2f pos = { HEADLINE_START, 20 };

	for (size_t i = 0; i < Texts.size(); i++)
	{
		if (i == 1) 
		{
			pos.x = DETAILS_START;
			pos.y += TEXT_Y_DISTANCE;
		}

		Text text = createText(Texts[i], pos, FONT_SIZE, Color{ 52, 73, 94 });
		m_boardDetails.push_back(text);

		pos.x += TEXT_X_DISTANCE;
	}

	setSteps();
	setLvl();

}
//-------------------------------------
//create the text of details
Text Screen::createText(const std::string &msg, Vector2f pos, int size, const Color& color)
{
	Text text;
	text.setFont(ResourceManager::instance().getFont());
	text.setString(msg);
	text.setPosition(pos);
	text.setCharacterSize(size);
	text.setFillColor(color); 
	
	return text;
}

//-------------------------------------
void Screen::drawScreen(RenderWindow& window)const
{
	for (auto const &i : m_boardDetails)
		window.draw(i);
}
//-------------------------------------
void Screen::setSteps()
{
	m_boardDetails[2].setString(Texts[2] + std::to_string(m_steps)); 
}

//-------------------------------------
void Screen::resetSteps() 
{
	m_steps = 0;
	setSteps();
}

//-------------------------------------
void Screen::decresSteps()
{
	m_steps--;
	setSteps();
}

//-------------------------------------
void Screen::setLvl()
{
	m_boardDetails[1].setString(Texts[1] + std::to_string(m_level + 1));
}

//-------------------------------------
bool Screen::undoClick(const Vector2f& loc)const 
{
	if (m_boardDetails[3].getGlobalBounds().contains(loc))
		return true;

	return false;
}