#include "Menu.h"
#include <fstream>
#include <string>

// konstruktor inicjalizujacy wyglad calego menu
Menu::Menu(float width, float height) {
    // wczytanie czcionki z pliku
    if (!font.loadFromFile("arial.ttf")) {}

    // ustawienia wizualne glownego tytulu
    titleText.setFont(font); titleText.setString("Wieze i Balony");
    titleText.setCharacterSize(65); titleText.setFillColor(sf::Color(64, 0, 0));
    sf::FloatRect tBounds = titleText.getLocalBounds();
    // centrowanie tytulu wedlug jego srodka
    titleText.setOrigin(tBounds.left + tBounds.width / 2.0f, tBounds.top + tBounds.height / 2.0f);
    titleText.setPosition(width / 2.0f, 90.0f);

    // ustawienia wizualne podtytulu
    subtitleText.setFont(font); subtitleText.setString("Projekt");
    subtitleText.setCharacterSize(35); subtitleText.setFillColor(sf::Color(64, 0, 0));
    sf::FloatRect sBounds = subtitleText.getLocalBounds();
    // centrowanie podtytulu
    subtitleText.setOrigin(sBounds.left + sBounds.width / 2.0f, sBounds.top + sBounds.height / 2.0f);
    subtitleText.setPosition(width / 2.0f, 165.0f);

    // przygotowanie trzech pudelek (przyciskow) z poziomami trudnosci
    levelBoxes.resize(3);
    std::vector<std::string> labels = { "Level 1", "Level 2", "Level 3" };
    std::vector<std::string> insideTexts = { "easy", "medium", "hard" };
    // kolory tla przyciskow (zielony, zolty, czerwony)
    std::vector<sf::Color> boxColors = { sf::Color(34, 177, 76), sf::Color(255, 242, 0), sf::Color(237, 28, 36) };
    // kolory napisow na przyciskach
    std::vector<sf::Color> textColors = { sf::Color(80, 220, 100), sf::Color(255, 128, 0), sf::Color(150, 0, 0) };

    // wymiary i rozmieszczenie przyciskow w poziomie i pionie
    float boxWidth = 230.0f; float boxHeight = 150.0f;
    float centerY = height / 2.0f + 100.0f;
    float spacing[3] = { -280.0f, 0.0f, 280.0f }; // przesuniecia od srodka ekranu

    // petla generujaca wszystkie trzy przyciski
    for (int i = 0; i < 3; ++i) {
        // konfiguracja ksztaltu i koloru samego pudelka
        levelBoxes[i].box.setSize({ boxWidth, boxHeight });
        levelBoxes[i].box.setFillColor(boxColors[i]);
        levelBoxes[i].box.setOutlineColor(sf::Color::Black);
        levelBoxes[i].box.setOutlineThickness(4.0f);
        levelBoxes[i].box.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        levelBoxes[i].box.setPosition(width / 2.0f + spacing[i], centerY);

        // konfiguracja etykiety (np. "Level 1") nad pudelkiem
        levelBoxes[i].label.setFont(font); levelBoxes[i].label.setString(labels[i]);
        levelBoxes[i].label.setCharacterSize(32); levelBoxes[i].label.setFillColor(boxColors[i]);
        sf::FloatRect lBounds = levelBoxes[i].label.getLocalBounds();
        levelBoxes[i].label.setOrigin(lBounds.left + lBounds.width / 2.0f, lBounds.top + lBounds.height / 2.0f);
        levelBoxes[i].label.setPosition(width / 2.0f + spacing[i], centerY - boxHeight / 2.0f - 40.0f);

        // konfiguracja tekstu poziomu trudnosci (np. "easy") w srodku pudelka
        levelBoxes[i].insideText.setFont(font); levelBoxes[i].insideText.setString(insideTexts[i]);
        levelBoxes[i].insideText.setCharacterSize(36); levelBoxes[i].insideText.setFillColor(textColors[i]);
        sf::FloatRect insideBounds = levelBoxes[i].insideText.getLocalBounds();
        levelBoxes[i].insideText.setOrigin(insideBounds.left + insideBounds.width / 2.0f, insideBounds.top + insideBounds.height / 2.0f);
        levelBoxes[i].insideText.setPosition(width / 2.0f + spacing[i], centerY);
    }
    // automatyczne zaczytanie tablicy wynikow po zaladowaniu menu
    updateLeaderboard(font);
}

Menu::~Menu() {}

// funkcja wylapujaca klikniecie w dany prostokat poziomu
int Menu::getClickedItem(float x, float y) {
    // przelatuje po wszystkich trzech pudelkach i sprawdza czy kursor (x, y) sie w nich znajduje
    for (int i = 0; i < 3; ++i) { if (levelBoxes[i].box.getGlobalBounds().contains(x, y)) return i; }
    // zwraca -1 gdy kliknieto puste pole (poza przyciskami)
    return -1;
}

// rysowanie wszystkich elementow na oknie
void Menu::draw(sf::RenderWindow& window) {
    // rysuje glowne teksty menu
    window.draw(titleText); window.draw(subtitleText); window.draw(menuLeaderboardText);

    // rysuje przyciski wraz z przypisanymi do nich etykietami
    for (int i = 0; i < 3; ++i) {
        // odswiezenie obramowania (na wypadek najechana na przycisk)
        levelBoxes[i].box.setOutlineColor(sf::Color::Black); levelBoxes[i].box.setOutlineThickness(4.0f);
        window.draw(levelBoxes[i].box); window.draw(levelBoxes[i].label); window.draw(levelBoxes[i].insideText);
    }
}

// ladowanie wynikow z pliku tekstowego i przypisywanie ich do odpowiedniego sf::Text
void Menu::updateLeaderboard(sf::Font& mainFont) {
    // formatowanie tekstu dla tablicy wynikow
    menuLeaderboardText.setFont(mainFont); menuLeaderboardText.setCharacterSize(18);
    menuLeaderboardText.setFillColor(sf::Color(220, 220, 220));

    // otwarcie pliku leaderboard.txt do odczytu
    std::ifstream inputFile("leaderboard.txt");
    int score; std::string sep1, outcome, sep2, diff;
    std::string lbString = "--- TOP BEST SCORES ---\n"; int count = 0;

    // czytanie po kolei najlepszych trzech wynikow
    while (inputFile >> score >> sep1 >> outcome >> sep2 >> diff && count < 3) {
        // formatowanie jednej lini w rankingu
        lbString += std::to_string(score) + " | " + outcome + " | " + diff + "\n"; count++;
    }
    // jezeli wynikow jest mniej niz 3 to wypelnia puste miejsca kreskami
    while (count < 3) { lbString += "---\n"; count++; }
    inputFile.close(); // zamkniecie pliku z wynikami

    // ustawienie gotowego tekstu we wlasciwym miejscu w rogu ekranu
    menuLeaderboardText.setString(lbString); menuLeaderboardText.setPosition(40.0f, 40.0f);
}