#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourceManager.h"

class Screen
{
public:
	Screen();
	void drawScreen(RenderWindow& window)const;

	void setSteps();
	void increaseSteps() { m_steps++; }
	void decresSteps();
	void resetSteps();
	
	void setLvl();
	unsigned int getLevelNum() const { return m_level; }
	void increaseLevel() { m_level++; }
	void updateLvl(unsigned int lvl) { m_level = lvl; }

	Text createText(const std::string& msg, Vector2f pos, int size, const Color& color);
	bool undoClick(const Vector2f& loc) const;

private:
	void setTexts();

	unsigned int m_steps = 0;
	unsigned int m_level = 0;
	
	std::vector<Text> m_boardDetails;
	std::vector<std::string> Texts = { "Circle The Cat", "Level: ", "Steps: ", "Undo" };
};