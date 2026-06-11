#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class Enemy;

// klasa reprezentujaca pocisk wystrzeliwany przez wieze
class Projectile : public GameObject {
private:
    sf::CircleShape shape; // ksztalt graficzny pocisku
    sf::Vector2f velocity; // wektor predkosci ruchowej
    Enemy* target;         // wskaznik na celowany obiekt wroga
    float speed; float damage; // predkosc oraz sila ciosu pocisku
    bool active; bool isCrit;  // status aktywnosci oraz flaga uderzenia krytycznego
public:
    // konstruktor tworzacy pocisk lecacy do celu
    Projectile(sf::Vector2f start, Enemy* target, sf::Color color, float damageOrSpeed);
    // metody aktualizacji logiki, rysowania oraz statusu aktywnosci
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool isActive();
};
#endif
