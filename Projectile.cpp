#include "Projectile.h"
#include "Enemy.h"
#include <cmath>
#include <cstdlib>

// ustawienie pozycji startowej celu oraz losowanie szansy na trafienie krytyczne
Projectile::Projectile(sf::Vector2f start, Enemy* target, sf::Color color, float damageOrSpeed) {
    this->target = target; this->active = true; this->speed = 550.0f; this->damage = damageOrSpeed;
    if (std::rand() % 100 < 15) { this->isCrit = true; this->damage *= 2.0f; shape.setFillColor(sf::Color::Red); }
    else { this->isCrit = false; shape.setFillColor(color); }
    shape.setRadius(5.0f); shape.setOrigin(5.0f, 5.0f); shape.setPosition(start);
}
// ruch pocisku w strone wroga i sprawdzanie kolizji z celem
void Projectile::update(float dt) {
    if (!active) return;
    if (target == nullptr || target->isDead()) { active = false; return; }
    sf::Vector2f dir = target->getPosition() - shape.getPosition();
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    // zadanie obrazen wrogowi po dotarciu na miejsce
    if (distance < speed * dt) { target->takeDamage(damage); active = false; }
    else shape.move((dir / distance) * speed * dt);
}
// rysowanie pocisku jezeli jest aktywny na mapie
void Projectile::draw(sf::RenderWindow& window) { if (active) window.draw(shape); }
// sprawdzenie czy pocisk nie zostal zniszczony
bool Projectile::isActive() { return active; }
