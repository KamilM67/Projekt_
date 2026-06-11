#ifndef CONFIG_H
#define CONFIG_H

// dolaczenie biblioteki sfml odpowiedzialnej za grafike
#include <SFML/Graphics.hpp>

// struktura przechowujaca globalne ustawienia i stale konfiguracji gry
struct Config {
    // wymiary okna gry w pikselach
    static const int WINDOW_WIDTH = 1280;
    static const int WINDOW_HEIGHT = 720;

    // tytul wyswietlany na gornej belce okna gry
    static constexpr const char* WINDOW_TITLE = "Tower Defense Projekt";

    // statystyki startowe dla gracza
    static const int STARTING_MONEY = 200; // poczatkowy stan konta
    static const int STARTING_LIVES = 10;  // poczatkowa liczba zyc

    // ekonomia gry i balanse obrony
    static const int TOWER_COST = 50;      // koszt postawienia jednej wiezy

    // ustawienia wygladu elementow gry za pomoca sfml
    static inline const sf::Color TOWER_COLOR = sf::Color::Blue;        // kolor wiezy
    static inline const sf::Color PROJECTILE_COLOR = sf::Color::Yellow; // kolor pocisku

    // konfiguracja fal przeciwnikow
    static const int BASE_ENEMIES_PER_WAVE = 10;       // liczba przeciwnikow w pierwszej fali
    static const int ENEMIES_INCREMENT_PER_WAVE = 5;   // o ile wiecej wrogow pojawi sie w kazdej kolejnej fali
};

#endif