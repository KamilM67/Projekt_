#include "Projectile.h"
#include "Enemy.h"
#include <cmath>
#include <cstdlib>

// konstruktor pocisku - ustala pozycje startowa, cel oraz losuje szanse na uderzenie krytyczne
Projectile::Projectile(sf::Vector2f start, Enemy* target, sf::Color color, float damageOrSpeed) {
    this->target = target; this->active = true; this->speed = 550.0f; this->damage = damageOrSpeed;

    // 15 procent szansy na trafienie krytyczne (podwojne obrazenia i czerwony kolor pocisku)
    if (std::rand() % 100 < 15) { this->isCrit = true; this->damage *= 2.0f; shape.setFillColor(sf::Color::Red); }
    else { this->isCrit = false; shape.setFillColor(color); }

    // ustawienie rozmiaru i punktu srodka pocisku
    shape.setRadius(5.0f); shape.setOrigin(5.0f, 5.0f); shape.setPosition(start);
}

// aktualizacja logiki pocisku - podazanie za wybranym wrogiem
void Projectile {
    if (!active) return; // jesli nieaktywny, nic nie rob

    // jesli cel zniknal lub umarl zanim dolecial pocisk, dezaktywuj pocisk
    if (target == nullptr || target->isDead()) { active = false; return; }

    // obliczanie wektora kierunku do celu i odleglosci
    sf::Vector2f dir = target->getPosition() - shape.getPosition();
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    // jesli odleglosc jest mniejsza niz dystans jaki pocisk przebywa w tej klatce, nastepuje trafienie
    if (distance < speed * dt) {
        target->takeDamage(damage); // zadanie obrazen wrogowi
        active = false;             // usuniecie pocisku z gry
    }
    // w przeciwnym wypadku kontynuuj lot w strone wroga
    else shape.move((dir / distance) * speed * dt);
}

// rysowanie pocisku na ekranie tylko wtedy gdy jest aktywny
void Projectile::draw(sf::RenderWindow& window) { if (active) window.draw(shape); }

// zwraca informacje czy pocisk caly czas leci
bool Projectile::isActive() { return active; }
