// plik naglowkowy dla klasy menu
#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <vector>

// struktura przechowujaca elementy wizualne pojedynczego przycisku poziomu
struct MenuLevelBox { sf::RectangleShape box; sf::Text label; sf::Text insideText; };

// glowna klasa zarzadzajaca menu startowym
class Menu {
private:
    sf::Font font; // czcionka wykorzystywana w menu
    sf::Text titleText; // glowny tytul gry
    sf::Text subtitleText; // podtytul
    std::vector<MenuLevelBox> levelBoxes; // wektor przechowujacy trzy przyciski z poziomami
    sf::Text menuLeaderboardText; // tekst wyswietlajacy tablice najlepszych wynikow
public:
    Menu(float width, float height); // konstruktor
    ~Menu(); // dekonstruktor
    void draw(sf::RenderWindow& window); // funkcja renderujaca menu w oknie
    int getClickedItem(float x, float y); // sprawdza ktory poziom zostal klikniety (zwraca indeks)
    void updateLeaderboard(sf::Font& mainFont); // wczytuje i aktualizuje ranking graczy z pliku
};
#endif