#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath>

// implementacja konstruktora ustalajaca poczatkowe zmienne i wartosci odliczania
Tower::Tower(float x, float y, TowerType type) : position(x, y), type(type), shootTimer(0.0f), upgradeLevel(0) {
    // bazowy okrag tworzacy podstawe wiezy i poczatkowy zasieg
    shape.setRadius(15.0f); shape.setOrigin(15.0f, 15.0f); shape.setPosition(position); range = 200.0f;
    // statystyki i modyfikacje wizualne dla niebieskiej wiezy (sredni atak)
    if (type == TowerType::Blue) { shape.setFillColor(sf::Color::Blue); damage = 1.0f; fireRate = 0.8f; innerRing.setFillColor(sf::Color(0, 0, 110)); }
    // statystyki i modyfikacje wizualne dla zielonej wiezy (slaby ale szybki atak)
    else if (type == TowerType::Green) { shape.setFillColor(sf::Color::Green); damage = 0.5f; fireRate = 0.3f; innerRing.setFillColor(sf::Color(0, 90, 0)); }
    // statystyki i modyfikacje wizualne dla rozowej wiezy (mocny ale rzadszy atak)
    else if (type == TowerType::Pink) { shape.setFillColor(sf::Color(255, 105, 180)); damage = 4.0f; fireRate = 1.5f; innerRing.setFillColor(sf::Color(160, 40, 100)); }
    // przygotowanie elementu wizualnego odblokowywanego po pierwszym ulepszeniu
    innerRing.setRadius(9.0f); innerRing.setOrigin(9.0f, 9.0f); innerRing.setPosition(position);
    // przygotowanie zlotego punktu w srodku pojawiajacego sie po drugim ulepszeniu
    goldDot.setRadius(3.5f); goldDot.setOrigin(3.5f, 3.5f); goldDot.setPosition(position); goldDot.setFillColor(sf::Color(255, 215, 0));
    // zewnetrzny obrys sygnalizujacy maksymalny - trzeci poziom ulepszenia wiezy
    externalGoldRing.setRadius(17.0f); externalGoldRing.setOrigin(17.0f, 17.0f); externalGoldRing.setPosition(position);
    externalGoldRing.setFillColor(sf::Color::Transparent); externalGoldRing.setOutlineColor(sf::Color(255, 215, 0)); externalGoldRing.setOutlineThickness(2.0f);
    // inicjalizacja zielonej kropki ktora dziala jako przycisk informujacy o mozliwosci upgrade'u
    upgradeIcon.setRadius(6.0f); upgradeIcon.setOrigin(6.0f, 6.0f); upgradeIcon.setPosition(position.x + 13.0f, position.y - 13.0f);
    upgradeIcon.setFillColor(sf::Color(50, 205, 50)); upgradeIcon.setOutlineColor(sf::Color::White); upgradeIcon.setOutlineThickness(1.0f);
}
// sprawdza logike gry: wieze mozna ulepszyc dopoki ma poziom mniejszy od trzech
bool Tower::canUpgrade() const { return upgradeLevel < 3; }
// funkcja decyzyjna przypisujaca odpowiednia cene za wskazane ulepszenie dla danego koloru wiezy
int Tower::getUpgradeCost() const {
    if (type == TowerType::Blue) { if (upgradeLevel == 0) return 40; if (upgradeLevel == 1) return 60; if (upgradeLevel == 2) return 300; }
    if (type == TowerType::Green) { if (upgradeLevel == 0) return 100; if (upgradeLevel == 1) return 150; if (upgradeLevel == 2) return 600; }
    if (type == TowerType::Pink) { if (upgradeLevel == 0) return 150; if (upgradeLevel == 1) return 220; if (upgradeLevel == 2) return 1000; }
    return 0;
}
// metoda odpowiedzialna za fizyczne polepszenie parametrow naszej konstrukcji
void Tower::upgrade() {
    // przerywa wykonywanie jezeli osiagnieto limit poziomu i zwieksza go o jeden
    if (!canUpgrade()) return; upgradeLevel++;
    // niebieska otrzymuje lepszy zasieg, zielona mocniejszy strzal, a rozowa strzela z wieksza czestotliwoscia
    if (type == TowerType::Blue) range += 60.0f; else if (type == TowerType::Green) damage += 0.5f; else if (type == TowerType::Pink) fireRate -= 0.4f;
}
// zwraca granice przycisku upgrade'u by sprawdzic czy gracz w niego kliknal
sf::FloatRect Tower::getUpgradeBounds() const { return upgradeIcon.getGlobalBounds(); }
// glowna logika wylapywania ofiar i aktywowania ataku
void Tower::update(float dt, const std::vector<Enemy*>& enemies, std::vector<Projectile*>& projectiles) {
    // odmierzanie pozostalego czasu do oddania strzalu w oparciu o czas trwania klatki
    shootTimer -= dt;
    // weryfikacja czy nadszedl moment zeby wystrzelic pocisk
    if (shootTimer <= 0) {
        // sprawdza pokolei kazdego wroga zarejestrowanego na mapie
        for (auto e : enemies) {
            // eliminuje z obliczen tych ktorzy wlasnie zostali zgladzni
            if (e->isDead()) continue;
            // tworzy wektor wyznaczajacy pozycje pomiedzy strzelajacym a wrogiem
            sf::Vector2f diff = e->getPosition() - position;
            // twierdzenie pitagorasa stosowane zeby ocenic czy dystans do ofiary jest mniejszy niz dopuszczalny zasieg broni
            if (std::sqrt(diff.x * diff.x + diff.y * diff.y) <= range) {
                // ustawienie odcienia uzytej amunicji zeby zgadzal sie z kolorem obronnej bazy
                sf::Color bulletColor = (type == TowerType::Blue) ? sf::Color::Blue : ((type == TowerType::Green) ? sf::Color::Green : sf::Color(255, 20, 147));
                // wygenerowanie fizycznego obiektu nowej kulki lecacej do wroga z wybranymi atrybutami
                projectiles.push_back(new Projectile(position, e, bulletColor, damage));
                // po zakonczeniu ataku timer odpala sie na nowo a reszta wrogow jest w tej klatce pomijana
                shootTimer = fireRate; break;
            }
        }
    }
}
// procedura tlumaczaca komputerowi jak dokladnie renderowac dany budynek
void Tower::draw(sf::RenderWindow& window, int currentMoney) {
    // wymaksowana budowla zyskuje ozdobne zlote kolko jako symbol sily
    if (upgradeLevel == 3) window.draw(externalGoldRing);
    // renderowanie absolutnej podstawy figury
    window.draw(shape);
    // dorysowuje wewnetrzna ozdobe informujaca ze gracz podniosl level
    if (upgradeLevel >= 1) window.draw(innerRing);
    // dorysowuje srodek informujacy o posiadaniu ulepszenia poziomu numer dwa
    if (upgradeLevel >= 2) window.draw(goldDot);
    // sprawdza czy mozna ulepszyc i jednoczesnie wystarczy pieniedzy, jesli tak pojawia sie wskaÅºnik klikniecia
    if (canUpgrade() && currentMoney >= getUpgradeCost()) window.draw(upgradeIcon);
}