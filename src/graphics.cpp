#include "include/config.h"
#include "include/graphics.h"
#include <SFML/Graphics.hpp>

void create_SFML_plots(std::deque <std::pair <int, int>> points, std::string title, sf::Color pointColor) //Given a deque of coordinate pairs, a title, and a pen color, create a labeled coordinate plane plot using SFML in a new window
{
    const int width = 600, height = 600;
    const int padding = 50;
    const int scale = 50;
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    int maxX = 0, maxY = 0;
    for (auto &pt : points) {
        maxX = std::max(maxX, pt.first);
        maxY = std::max(maxY, pt.second == INT_MAX ? 0 : pt.second);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        for (int x = 0; x <= maxX + 2; ++x) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(padding + x * scale, height - padding), sf::Color(200,200,200)),
                sf::Vertex(sf::Vector2f(padding + x * scale, padding), sf::Color(200,200,200))
            };
            window.draw(line, 2, sf::Lines);
        }
        for (int y = 0; y <= maxY + 2; ++y) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(padding, height - padding - y * scale), sf::Color(200,200,200)),
                sf::Vertex(sf::Vector2f(width - padding, height - padding - y * scale), sf::Color(200,200,200))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw axes
        sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(width - padding, height - padding), sf::Color::Black)
        };
        sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::Black),
            sf::Vertex(sf::Vector2f(padding, padding), sf::Color::Black)
        };
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        // Draw points and connect them
        if (!points.empty()) {
            sf::VertexArray lines(sf::LineStrip, points.size());
            int idx = 0;
            for (auto &pt : points) {
                float px = padding + pt.first * scale;
                float py = height - padding - (pt.second == INT_MAX ? 0 : pt.second) * scale;
                lines[idx].position = sf::Vector2f(px, py);
                lines[idx].color = pointColor;

                sf::CircleShape circle(5);
                circle.setFillColor(pointColor);
                circle.setOrigin(5, 5);
                circle.setPosition(px, py);
                window.draw(circle);
                idx++;
            }
            window.draw(lines);
        }
        window.display();
    }
}

