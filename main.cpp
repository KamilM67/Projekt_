#include <SFML/Graphics.hpp>
#include "Config.h"

// Startowy main sprawdzajacy dzialanie okna
int main() {
    sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color(45, 45, 45));
        window.display();
    }
    return 0;
}