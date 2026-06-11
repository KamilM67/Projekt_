#include "Enemy.h"
#include <cmath>
#include <cstdlib>

// konstruktor inicjalizuje zmienne i ustawia poczatkowy wyglad oraz pozycje wroga na start sciezki
Enemy::Enemy(const std::vector<sf::Vector2f>& mapPath, float speed, float maxHp)
    : mapPath(mapPath), speed(speed), hp(maxHp), dead(false), currentPathIndex(0), boss(false) {
    shape.setRadius(15.0f); shape.setOrigin(15.0f, 15.0f); shape.setFillColor(sf::Color::Red);
    if (!mapPath.empty()) shape.setPosition(mapPath[0]); // ustawienie na pierwszym punkcie sciezki
}

// aktualizacja pozycji wroga - poruszanie sie wzdluz punktow sciezki
void Enemy::update(float dt) {
    if (dead || mapPath.empty()) return; // jesli wrog nie zyje lub brak sciezki, nic nie rob

    if (currentPathIndex < mapPath.size()) {
        // obliczanie wektora kierunku do kolejnego punktu
        sf::Vector2f dir = mapPath[currentPathIndex] - shape.getPosition();
        // obliczanie odleglosci do tego punktu
        float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        // jesli wrog jest blisko punktu, przelacza sie na nastepny cel
        if (dist < 5.0f) currentPathIndex++;
        // w przeciwnym wypadku przesuwa sie w strone punktu docelowego
        else shape.move((dir / dist) * speed * dt);
    }
}

// rysowanie wroga w oknie gry jesli wciaz zyje
void Enemy::draw(sf::RenderWindow& window) { if (!dead) window.draw(shape); }

// funkcja obslugujaca otrzymywanie obrazen przez wroga
void Enemy::takeDamage(float damage) {
    if (dead) return;
    hp -= damage; // odjecie punktow zycia

    // jesli zycie spadnie do zera lub nizej, wrog umiera
    if (hp <= 0) { hp = 0; dead = true; }
    // jesli przezyje, zmienia kolor na losowy jako efekt trafienia
    else shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

// metoda zmieniajaca statystyki i wyglad wroga na wiekszego i silniejszego (bossa)
void Enemy::setBossAppearance() {
    boss = true;
    shape.setRadius(35.0f);
    shape.setOrigin(35.0f, 35.0f);
    shape.setFillColor(sf::Color(139, 0, 0)); // ciemnoczerwony kolor dla bossa
}
