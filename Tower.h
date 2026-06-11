// dyrektywy preprocesora zapobiegajace wielokrotnemu dolaczaniu pliku
#ifndef TOWER_H
#define TOWER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Enemy.h"
#include "Projectile.h"

// wyliczenie dostepnych wariantow wiez
enum class TowerType { Blue, Green, Pink };

// definicja klasy wiezy dziedziczacej po ogolnej klasie gameobject
class Tower : public GameObject {
private:
    // elementy graficzne sfml tworzace wyglad wiezy i wskazniki poziomu ulepszenia
    sf::CircleShape shape; sf::CircleShape innerRing; sf::CircleShape goldDot;
    sf::CircleShape externalGoldRing; sf::CircleShape upgradeIcon;
    // polozenie wiezy na mapie oraz jej wariant
    sf::Vector2f position; TowerType type;
    // parametry bitewne: promien razenia, zadawane obrazenia i obecny stopien ulepszenia
    float range; float damage; int upgradeLevel;
    // zmienne regulujace czas i czestotliwosc strzelania
    float shootTimer; float fireRate;
public:
    // konstruktor przypisujacy pozycje startowa i typ wiezy
    Tower(float x, float y, TowerType type);
    // puste metody wirtualne narzucone przez dziedziczenie z gameobject
    void update(float dt) override {}
    void draw(sf::RenderWindow& window) override {}
    // glowna funkcja odswiezajaca stan wiezy - namierza przeciwnikow i oddaje strzaly
    void update(float dt, const std::vector<Enemy*>& enemies, std::vector<Projectile*>& projectiles);
    // metoda rysujaca wyglad wiezy - sprawdza tez stan gotowki gracza
    void draw(sf::RenderWindow& window, int currentMoney);
    // funkcja weryfikujaca czy wieza moze byc jeszcze ulepszona
    bool canUpgrade() const;
    // zwraca koszt podniesienia wiezy na nastepny poziom
    int getUpgradeCost() const;
    // funkcja podnoszaca statystyki po kupieniu ulepszenia
    void upgrade();
    // pozwala pobrac rozmiar ikony ulepszania aby wykywac na niej klikniecia
    sf::FloatRect getUpgradeBounds() const;
};
#endif