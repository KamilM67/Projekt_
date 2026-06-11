#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

// klasa reprezentujaca przeciwnika dziedziczaca po gameobject
class Enemy : public GameObject {
private:
    std::vector<sf::Vector2f> mapPath; // punkty sciezki na mapie
    size_t currentPathIndex;           // aktualny indeks punktu do ktorego idzie wrog
    sf::CircleShape shape;             // ksztalt graficzny wroga
    float speed; float hp; float maxHp; // statystyki predkosci i zdrowia
    bool dead; bool boss;              // flagi stanu zycia i typu jednostki
public:
    // konstruktor wroga
    Enemy(const std::vector<sf::Vector2f>& mapPath, float speed, float hp);
    // aktualizacja logiki i rysowanie okna
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    // gettery stanu i pozycji
    bool isDead() { return dead; }
    bool isBoss() { return boss; }
    sf::Vector2f getPosition() { return shape.getPosition(); }
    sf::FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
    // metody do zmiany wygladu i przyjmowania obrazen
    void setBossAppearance();
    void takeDamage(float amount);
};
#endif
