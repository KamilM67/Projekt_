#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

// klasa reprezentujaca przeciwnika dziedziczaca po gameobject
class Enemy : public GameObject {
private:
    std::vector<sf::Vector2f> mapPath; // wektor punktow tworzacych sciezke po ktorej idzie wrog
    size_t currentPathIndex;           // indeks punktu sciezki do ktorego aktualnie zmierza wrog
    sf::CircleShape shape;             // graficzny ksztalt przeciwnika (kolo)
    float speed; float hp; float maxHp; // predkosc, aktualne zdrowie oraz maksymalne zdrowie wroga
    bool dead; bool boss;              // flagi okreslajace czy wrog jest martwy oraz czy jest bossem

public:
    // konstruktor przyjmujacy sciezke, predkosc oraz punkty zycia
    Enemy(const std::vector<sf::Vector2f>& mapPath, float speed, float hp);

    // nadpisane funkcje logiczne i graficzne
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    // metody dostepowe (gettery) do sprawdzania stanu i pozycji wroga
    bool isDead() { return dead; }
    bool isBoss() { return boss; }
    sf::Vector2f getPosition() { return shape.getPosition(); }
    sf::FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }

    // metody do modyfikacji stanu wroga
    void setBossAppearance(); // zmienia wyglad wroga na bossa
    void takeDamage(float amount); // zadaje obrazenia wrogowi
};
#endif
