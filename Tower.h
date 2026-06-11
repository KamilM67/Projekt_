#ifndef TOWER_H // zabezpieczenie przed wielokrotnym dolaczaniem tego samego naglowka
#define TOWER_H // zdefiniowanie makra dla powyzszego zabezpieczenia guard

#include <SFML/Graphics.hpp> // dolaczenie biblioteki sfml do obslugi rysowania ksztaltow i grafiki 2d
#include <vector>            // dolaczenie dynamicznej tablicy vector z biblioteki standardowej c++
#include "GameObject.h"      // dolaczenie klasy bazowej wszystkich obiektow gry po ktorej dziedziczymy
#include "Enemy.h"           // dolaczenie klasy wroga zeby wieza miala dostep do jego pozycji i zycia
#include "Projectile.h"      // dolaczenie klasy pocisku zeby wieza mogla generowac nowe obiekty strzalu

enum class TowerType { Blue, Green, Pink }; // stworzenie bezpiecznej listy dostepnych typow wiez

class Tower : public GameObject { // deklaracja klasy tower ktora dziedziczy publicznie metody z gameobject
private: // rozpoczecie sekcji prywatnej dostepnej tylko dla kodu wewnatrz tej klasy
    sf::CircleShape shape;            // obiekt sfml reprezentujacy glowny okragly ksztalt wiezy
    sf::CircleShape rangeShape;       // duzy przezroczysty okrag pokazujacy zasieg strzalu wiezy
    sf::CircleShape innerRing;        // wewnetrzny ozdobny pierscien dla lepszego wygladu wiezy
    sf::CircleShape goldDot;          // mala zlota ozdobna kropka w samym srodku struktury
    sf::CircleShape externalGoldRing; // zewnetrzny zloty pierscien ozdobny dla grafiki wiezy
    sf::CircleShape upgradeIcon;      // obiekt graficzny wyswietlajacy ikonke informujaca o opcji ulepszenia

    sf::Vector2f position; // zmienna przechowujaca wspolrzedne x i y polozenia wiezy na mapie
    TowerType type;        // zmienna przechowujaca przypisany typ wiezy z listy enum

    float range;          // wartosc liczbowa okreslajaca maksymalny zasieg strzalu wiezy
    float damage;         // wartosc okreslajaca sile obrazen jakie zada pocisk wystrzelony przez wieze
    int upgradeLevel;     // zmienna przechowujaca aktualny poziom ulepszenia wiezy od zera w gore
    bool showRange;       // flaga typu prawda lub falsz decydujaca czy rysowac na ekranie zasieg wiezy

    float shootTimer;     // zegar odliczajacy czas jaki minal od ostatniego wystrzalu pocisku
    float fireRate;       // szybkostrzelnosc wiezy okreslajaca ile strzalow moze oddac w sekunde
    float fireCooldown;   // czas odnowienia jaki musi minac miedzy kolejnymi strzalami
    float fireTimer;      // pomocniczy licznik czasu uzywany do kontroli efektow ognia lub animacji
