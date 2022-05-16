#pragma once
#include "Screen.h"
#include "Board.h"
#include "Cat.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>


class Controller
{
public:
	Controller();
	void run();

private:
	void draw(RenderWindow&);
	void handleEvents();
	void endLvl(unsigned int level);
	void mouseEventPressed(const Event&);
	void mouseEventMoved(const Event&);
	void exitGame(const Event&);
	void doUndoClick();

	RenderWindow m_window; 
	Screen m_screen;
	Board m_board;
	Cat m_cat;
    bool m_Won;
	bool m_Lost;

	std::vector<std::pair<Vector2i, Vector2i >> m_logs; //cat moves + player clicks

};
