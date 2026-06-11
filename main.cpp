// dolaczenie bibliotek graficznych sfml oraz logicznych modulow strukturalnych projektu
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Menu.h"
#include "Config.h"

// typ wyliczeniowy zarzadzajacy biezacym stanem wyswietlanego ekranu gry
enum class GameState { MENU, GAME };

// glowna funkcja startowa programu
int main() {
    sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Tower Defense");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    // inicjalizacja obiektow interfejsu menu poczatkowego oraz glownego managera rozgrywki
    Menu menu(static_cast<float>(Config::WINDOW_WIDTH), static_cast<float>(Config::WINDOW_HEIGHT));
    GameManager gameManager;
    menu.updateLeaderboard(font);

    GameState state = GameState::MENU;
    sf::Clock clock;

    // glowna petla dzialania aplikacji okienkowej podtrzymujaca dzialanie gry
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;

        // petla wychwytywania zdarzen systemowych wysylanych do okna gry
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // przetwarzanie klikniec myszy w obrebie ekranu menu startowego
            if (state == GameState::MENU && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int clickedItem = menu.getClickedItem(event.mouseButton.x, event.mouseButton.y);
                    if (clickedItem == 0) { gameManager.setupDifficulty(Difficulty::EASY); state = GameState::GAME; }
                    else if (clickedItem == 1) { gameManager.setupDifficulty(Difficulty::MEDIUM); state = GameState::GAME; }
                    else if (clickedItem == 2) { gameManager.setupDifficulty(Difficulty::HARD); state = GameState::GAME; }
                }
            }
            // przetwarzanie klikniec myszy podokres rozgrywki do obslugi interfejsu badz budowania
            else if (state == GameState::GAME && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameManager.placeTower(event.mouseButton.x, event.mouseButton.y)) {
                        state = GameState::MENU;
                        menu.updateLeaderboard(font);
                    }
                }
            }
        }

        // aktualizacja logiki obiektow gry tylko wtedy gdy aktywny jest ekran rozgrywki
        if (state == GameState::GAME) gameManager.update(dt);

        // czyszczenie okna i renderowanie odpowiedniej grafiki zaleznie od aktualnego stanu maszyny stanow
        window.clear(sf::Color(45, 45, 45));
        if (state == GameState::MENU) menu.draw(window);
        else if (state == GameState::GAME) gameManager.draw(window);
        window.display();
    }
    return 0;
}
