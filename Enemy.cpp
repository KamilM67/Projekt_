#include "Enemy.h"
#include <cmath>
#include <cstdlib>

// inicjalizacja wroga i ustawienie domyslnego wygladu oraz pozycji startowej
Enemy::Enemy(const std::vector<sf::Vector2f>& mapPath, float speed, float maxHp)
    : mapPath(mapPath), speed(speed), hp(maxHp), dead(false), currentPathIndex(0), boss(false) {
    shape.setRadius(15.0f); shape.setOrigin(15.0f, 15.0f); shape.setFillColor(sf::Color::Red);
    if (!mapPath.empty()) shape.setPosition(mapPath[0]);
}
// poruszanie sie wroga po punktach sciezki
void Enemy::update(float dt) {
    if (dead || mapPath.empty()) return;
    if (currentPathIndex < mapPath.size()) {
        sf::Vector2f dir = mapPath[currentPathIndex] - shape.getPosition();
        float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        // zmiana punktu docelowego jesli wrog jest blisko
        if (dist < 5.0f) currentPathIndex++;
        // ruch w strone punktu docelowego
        else shape.move((dir / dist) * speed * dt);
    }
}
// wyswietlanie wroga jezeli zyje
void Enemy::draw(sf::RenderWindow& window) { if (!dead) window.draw(shape); }
// obsluga obrazen i zmiana koloru po trafieniu
void Enemy::takeDamage(float damage) {
    if (dead) return;
    hp -= damage;
    if (hp <= 0) { hp = 0; dead = true; }
    else shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}
// zmiana statystyk i wygladu na bossa
void Enemy::setBossAppearance() {
    boss = true; shape.setRadius(35.0f); shape.setOrigin(35.0f, 35.0f); shape.setFillColor(sf::Color(139, 0, 0));
}
