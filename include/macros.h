#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

const int NUM_OF_LVL = 3;

const int BOARD_SIDE = 11;
const int CIRCLE_SIZE = 25;
const int FONT_SIZE = 50;

//for screen texts
const int HEADLINE_START = 320;
const int DETAILS_START = 140;
const int TEXT_X_DISTANCE = 300;
const int TEXT_Y_DISTANCE = 780;

const int LEFT_CORNER = 190;
const int WIDTH_DISTANCE = 65;
const int HIEGHT_DISTANCE = 60;
const int EVEN_DISTANCE = 35;

const Vector2i CAT_START = { 5,5 };

//for BFS
const int dirctionRow[] = { 1, 0, 1, 0, -1, -1 };
const int dirColOdd[] = { 0, -1, 1, 1, 0, 1 };
const int dirColEvenOdd[] = { -1, -1, 0, 1, -1, 0 };
const int directions = 6;


using BoardVector = std::vector<std::vector<CircleShape>>;
