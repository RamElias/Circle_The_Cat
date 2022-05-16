#include "Controller.h"

//-------------------------------------
Controller::Controller() :
	m_window(VideoMode(1100, 900), "Circle the Cat"),
	m_cat(m_board), m_Won(false), m_Lost(false)
{}

//-------------------------------------
//main function that run the game

void Controller::run()
{
	srand(int(time(NULL)));
	int level = 0;
	m_board.setBlockCircles(m_screen.getLevelNum());

	while (m_window.isOpen() &&  m_screen.getLevelNum() < NUM_OF_LVL)
	{
		handleEvents();

		m_window.clear(sf::Color::White);
		draw(m_window);
		m_window.display();

		if (m_Lost || m_Won)
		{
			endLvl(m_screen.getLevelNum());
		}
	}

	endLvl(m_screen.getLevelNum());

	m_window.close();
}

//-------------------------------------
//function that handle the events in the game

void Controller::handleEvents()
{
	auto event = sf::Event();
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			mouseEventPressed(event);
			break;
		case sf::Event::MouseMoved:
			mouseEventMoved(event);
			break;
		default:
			exitGame(event);
			break;
		}
	}
}

//-------------------------------------
// function that handle the game and details when the user\cat win

void Controller::endLvl(unsigned int level)
{
	Text text;

	//cat won 
	if (m_Won)
	{
		text = m_screen.createText("Cat Won!", { 120, 300 }, 150, Color{ 231, 76, 60 });

		Clock clock;
		while (clock.getElapsedTime().asSeconds() < 3)
		{
			m_window.clear(sf::Color::White);
			draw(m_window);
			m_window.draw(text);
			m_window.display();
		}

		while (!m_logs.empty())
			doUndoClick();
	}

	//user won
	else if (m_Lost)
	{
		if (level == NUM_OF_LVL - 1)
			text = m_screen.createText("Game finished! :)", { 90, 300 }, 90 , Color{ 39, 174, 96 });
		else
			text = m_screen.createText("You Won!", { 120, 300 }, 150, Color{ 39, 174, 96 });
		
		Clock clock;
		while (clock.getElapsedTime().asSeconds() < 3)
		{
			m_window.clear(sf::Color::White);
			draw(m_window);
			m_window.draw(text);
			m_window.display();
		}

		m_screen.increaseLevel();
		m_screen.updateLvl(m_screen.getLevelNum());
		m_screen.setLvl();
		m_board.resetCircles();
		m_board.setBlockCircles(m_screen.getLevelNum());
	}

	m_cat.setCatLost(false);
	m_cat.setCatBlock(false);
	m_cat.setCatPos(CAT_START);
	m_cat.setCatSprite(CAT_START);
	m_Lost = m_Won = false;
	m_screen.resetSteps();
}

//-------------------------------------
void Controller::exitGame(const Event& event)
{
	if (event.key.code == sf::Keyboard::Escape ||
		event.type == sf::Event::Closed)
		m_window.close();
}

//-------------------------------------
//function for the event of moused pressed
void Controller::mouseEventPressed(const Event& event)
{
	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	if (m_board.findClick(location, m_cat.getCatPos()))
	{
		m_logs.emplace_back(std::pair<Vector2i, Vector2i>(m_cat.getCatPos(), m_board.getClikLogs()));
		m_screen.increaseSteps();
		m_screen.setSteps();
        m_cat.move();
        if(m_cat.checkCatWon())
            m_Won = true;
		if (m_cat.checkCatLost())
			m_Lost = true;
	}
	if (m_screen.undoClick(location))
		doUndoClick();
}
//-------------------------------------
//function for the event of mouse move on board
void Controller::mouseEventMoved(const Event& e)
{
	auto location = Vector2f(float(e.mouseMove.x), float(e.mouseMove.y));
	m_board.findMousePos(location, m_cat.getCatPos());
}

//-------------------------------------
void Controller::draw(RenderWindow& window)
{
	m_board.drawBoard(window);
	m_cat.showCat(window);
	m_screen.drawScreen(window);
}

void Controller::doUndoClick() {
	if (m_logs.empty())
		return;
	m_cat.setCatSprite(m_logs.back().first);
	m_cat.setCatPos(m_logs.back().first);
	m_board.whiteCircle(m_logs.back().second);
	m_screen.decresSteps();
	m_logs.pop_back();
}