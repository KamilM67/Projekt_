#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.h"

// deklaracja wyprzedzajaca klasy enemy zeby uniknac zapetlenia naglowkow
class Enemy;

// klasa reprezentujaca pocisk wystrzelony przez wieze
class Projectile : public GameObject {
private:
    sf::CircleShape shape; // ksztalt graficzny pocisku (male kolo)
    sf::Vector2f velocity; // wektor predkosci ruchu pocisku
    Enemy* target;         // wskaznik na wroga ktory jest celem pocisku
    float speed; float damage; // predkosc lotu oraz obrazenia pocisku
    bool active; bool isCrit;  // flagi czy pocisk istnieje na mapie oraz czy jest strzalem krytycznym

public:
    // konstruktor tworzacy pocisk w miejscu startu, celowany w konkretnego wroga
    Projectile(sf::Vector2f start, Enemy* target, sf::Color color, float damageOrSpeed);

    // nadpisane funkcje logiczne i graficzne
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    // getter sprawdzajacy czy pocisk jest aktywny (czy nie trafil jeszcze w cel)
    bool isActive();
};
#endif
