#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Config.h"

// glowny punkt startowy programu
int main() {
    // stworzenie i otworzenie okna gry w oparciu o stala konfiguracje (config.h)
    sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE);

    // deklaracja czcionki
    sf::Font font;
    // zakonczenie dzialania (zwraca -1) w razie braku pliku z czcionka
    if (!font.loadFromFile("arial.ttf")) return -1;

    // utworzenie obiektu glownego menu, przekazanie wymiarow okna
    Menu menu(static_cast<float>(Config::WINDOW_WIDTH), static_cast<float>(Config::WINDOW_HEIGHT));
    // zaladowanie i wyswietlenie tabeli najlepszych wynikow
    menu.updateLeaderboard(font);

    // glowna petla gry zalezna od aktywnosci okna
    while (window.isOpen()) {
        sf::Event event;
        // petla sprawdzajaca wylapane wydarzenia w oknie (np. wcisniecie klawisza)
        while (window.pollEvent(event)) {
            // zamkniecie okna gry gdy uzytkownik kliknie 'X' (zamknij)
            if (event.type == sf::Event::Closed) window.close();
        }

        // wyczyszczenie okna przed renderowaniem nowej klatki i ustawienie tła na ciemnoszare
        window.clear(sf::Color(45, 45, 45));

        // narysowanie zaktualizowanego menu na ekranie
        menu.draw(window);

        // finalne wyswietlenie wszystkiego, co zostalo narysowane do bufora
        window.display();
    }

    // wylaczenie programu jezeli wszystko zadzialalo bez bledow
    return 0;
}