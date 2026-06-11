#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// dolaczenie biblioteki sfml potrzebnej do operacji graficznych
#include <SFML/Graphics.hpp>

// klasa abstrakcyjna bedaca baza dla wszystkich obiektow w grze (np. wieze, wrogowie)
class GameObject {
public:
    // wirtualny destruktor zapewniaacy poprawne czyszczenie pamieci klas pochodnych
    virtual ~GameObject() = default;

    // czysta funkcja wirtualna do aktualizacji logiki obiektu, dt to czas od ostatniej klatki (delta time)
    virtual void update(float dt) = 0;

    // czysta funkcja wirtualna odpowiedzialna za rysowanie obiektu w oknie gry
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif