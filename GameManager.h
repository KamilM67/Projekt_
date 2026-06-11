// zabezpieczenie przed wielokrotnym wczytaniem pliku naglowkowego
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// zabezpieczenie definicji typu wyliczeniowego
#ifndef DIFFICULTY_ENUM_GUARD
#define DIFFICULTY_ENUM_GUARD
// dostepne poziomy trudnosci: latwy, sredni, trudny
enum class Difficulty { EASY, MEDIUM, HARD };
#endif

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "GameObject.h"
#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Menu.h"
#include "Config.h"

// struktura przechowujaca wynik do rankingu (liczba punktow, status gry, poziom trudnosci)
struct ScoreEntry { int score; std::string outcome; std::string difficulty; };
// struktura reprezentujaca miejsce na mapie z mozliwoscia budowy wiezy (jej ksztalt i czy juz jest zajete)
struct PlacementSlot { sf::RectangleShape shape; bool isOccupied; };
// struktura dla przyciskow w dolnym panelu pozwalajacych na zakup danej wiezy
struct HudButton { TowerType type; int price; sf::CircleShape icon; sf::Text stats; };

// glowna klasa odpowiedzialna za przebieg rozgrywki
class GameManager {
private:
    // czcionka i aktualnie wybrany poziom trudnosci gry
    sf::Font font; Difficulty currentDifficulty;
    // wektor przechowujacy wszystkie aktywne obiekty na mapie (wrogowie, pociski)
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    // miejsca, w ktorych gracz moze wybudowac swoja obrone
    std::vector<PlacementSlot> placementSlots;
    // lista punktow wyznaczajacych droge dla przeciwnikow oraz ich graficzna reprezentacja
    std::vector<sf::Vector2f> mapPath; std::vector<sf::RectangleShape> pathSegments;
    // graficzne tla dla calej mapy i glownej bazy gracza na koncu sciezki
    sf::RectangleShape backgroundRect; sf::RectangleShape baseShape;
    // tlo interfejsu (hud) oraz lista przyciskow do wybierania i kupowania wiez
    sf::RectangleShape hudBackground; std::vector<HudButton> hudButtons;
    // obiekty tekstowe i prostokaty wyswietlajace statystyki (np. monety, zapowiedzi fal)
    sf::Text moneyText; sf::RectangleShape statsBackground; sf::Text waveAnnouncementText;
    // przycisk powrotu do menu oraz teksty informujace o przegranej lub wygranej
    sf::RectangleShape hudMenuButton; sf::Text hudMenuText; sf::Text gameOverText; sf::Text winText;
    // elementy wyswietlane po zakonczeniu gry (wynik, przycisk restartu i powrotu do menu)
    sf::Text scoreText; sf::RectangleShape restartButton; sf::Text restartText; sf::RectangleShape menuButton; sf::Text menuText;
    // statystyki obecnej partii: pieniadze, ilosc zyc, numery fal, limity wrogow i bossow
    int money; int lives; int currentWave; int maxWaves; int enemiesSpawnedInWave; int bossesToSpawn;
    // timery sterujace czestotliwoscia pojawiania sie wrogow i dlugoscia przerw
    float spawnTimer; float wavePauseTimer; float bossSpawnCooldown;
    // flagi sprawdzajace obecny stan meczu (pauza, koniec gry, zwyciestwo, czy zapisano wynik)
    bool isWavePause; bool isGameOver; bool isWin; bool scoreSaved;
    // lista uzywana do trzymania najlepszych wynikow z pliku oraz wybrany aktualnie w hud typ wiezy
    std::vector<ScoreEntry> highScores; sf::Text leaderboardText; TowerType selectedType;
    // paleta kolorow wykorzystywanych do rysowania sciezki, trawy i interfejsu uzytkownika
    sf::Color color_Ground, color_Path, color_SlotFill, color_SlotOutline, color_HudBg, color_StatsBgFill, color_StatsBgOutline;

    // prywatne metody przygotowujace poszczegolne wizualne elementy mapy, intefejs i ranking
    void initHUD(); void initPathGraphics(); void initPlacementSlots(); void updateUI(); void spawnEnemy(); void loadAndSaveLeaderboard(int finalScore);
public:
    // konstruktor i destruktor klasy zarzadcy
    GameManager(); ~GameManager();
    // metody dostepne na zewnatrz do resetowania stanu, wyboru poziomu, aktualizacji logiki i renderowania obrazu
    void restartGame(); void setupDifficulty(Difficulty diff); void update(float dt); void draw(sf::RenderWindow& window); bool placeTower(float x, float y);
};
#endif