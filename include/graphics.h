#pragma once
#include <deque>
#include <string>
#include <SFML/Graphics.hpp>

void create_SFML_plots(std::deque<std::pair<int, int>> points, std::string title, sf::Color pointColor);
