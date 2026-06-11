// dolaczenie potrzebnych bibliotek standardowych oraz naglowkow projektu
#include <memory>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "GameManager.h"
#include "Config.h"
#include <iostream>
#include <cmath>
#include <algorithm>

// konstruktor managera gry - ladowanie czcionki, ustawianie pozycji tekstow, przyciskow oraz bazowego stanu
GameManager::GameManager() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    if (!font.loadFromFile("arial.ttf")) { std::cerr << "Blad: Nie znaleziono arial.ttf!" << std::endl; }
    backgroundRect.setSize({(float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT}); backgroundRect.setPosition(0, 0);
    maxWaves = 10; bossesToSpawn = 0; bossSpawnCooldown = 3.0f;
    moneyText.setFont(font); moneyText.setCharacterSize(24); moneyText.setFillColor(sf::Color::Yellow); moneyText.setPosition(Config::WINDOW_WIDTH - 215.0f, 15.0f);
    waveAnnouncementText.setFont(font); waveAnnouncementText.setCharacterSize(70); waveAnnouncementText.setFillColor(sf::Color::White); waveAnnouncementText.setOutlineThickness(3.0f);
    gameOverText.setFont(font); gameOverText.setString("GAME OVER"); gameOverText.setCharacterSize(90); gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect goBounds = gameOverText.getLocalBounds(); gameOverText.setOrigin(goBounds.left + goBounds.width / 2.0f, goBounds.top + goBounds.height / 2.0f); gameOverText.setPosition(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f - 140.0f);
    winText.setFont(font); winText.setString("YOU WIN!"); winText.setCharacterSize(90); winText.setFillColor(sf::Color::Green);
    sf::FloatRect wBounds = winText.getLocalBounds(); winText.setOrigin(wBounds.left + wBounds.width / 2.0f, wBounds.top + wBounds.height / 2.0f); winText.setPosition(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f - 140.0f);
    scoreText.setFont(font); scoreText.setCharacterSize(36); scoreText.setFillColor(sf::Color::Yellow);
    leaderboardText.setFont(font); leaderboardText.setCharacterSize(22); leaderboardText.setFillColor(sf::Color::White);
    restartButton.setSize({250.0f, 60.0f}); restartButton.setFillColor(sf::Color(100, 100, 100)); restartButton.setOutlineThickness(3.0f); restartButton.setOutlineColor(sf::Color::White); restartButton.setOrigin(125.0f, 30.0f); restartButton.setPosition(Config::WINDOW_WIDTH / 2.0f - 140.0f, Config::WINDOW_HEIGHT / 2.0f + 190.0f);
    restartText.setFont(font); restartText.setString("PLAY AGAIN"); restartText.setCharacterSize(28); restartText.setFillColor(sf::Color::White);
    sf::FloatRect rtBounds = restartText.getLocalBounds(); restartText.setOrigin(rtBounds.left + rtBounds.width / 2.0f, rtBounds.top + rtBounds.height / 2.0f); restartText.setPosition(restartButton.getPosition());
    menuButton.setSize({250.0f, 60.0f}); menuButton.setFillColor(sf::Color(100, 100, 100)); menuButton.setOutlineThickness(3.0f); menuButton.setOutlineColor(sf::Color::White); menuButton.setOrigin(125.0f, 30.0f); menuButton.setPosition(Config::WINDOW_WIDTH / 2.0f + 140.0f, Config::WINDOW_HEIGHT / 2.0f + 190.0f);
    menuText.setFont(font); menuText.setString("MAIN MENU"); menuText.setCharacterSize(28); menuText.setFillColor(sf::Color::White);
    sf::FloatRect mBounds = menuText.getLocalBounds(); menuText.setOrigin(mBounds.left + mBounds.width / 2.0f, mBounds.top + mBounds.height / 2.0f); menuText.setPosition(menuButton.getPosition());
    baseShape.setSize({60.0f, 60.0f}); baseShape.setFillColor(sf::Color(255, 105, 180)); baseShape.setOrigin(30.0f, 30.0f);
    scoreSaved = false; currentDifficulty = Difficulty::EASY; setupDifficulty(Difficulty::EASY);
}

// wirtualny destruktor managera gry
GameManager::~GameManager() {}

// ustawianie parametrw dla wybranego poziomu trudnosci, w tym ukladu sciezki i palety kolorow mapy
void GameManager::setupDifficulty(Difficulty diff) {
    currentDifficulty = diff;
    if (diff == Difficulty::HARD) {
        maxWaves = 40; mapPath = { {0, 300}, {350, 300}, {350, 100}, {750, 100}, {750, 450}, {200, 450}, {200, 550}, {1300, 550} };
        color_Ground = sf::Color(20, 15, 15); color_Path = sf::Color(85, 25, 20); color_SlotFill = sf::Color(45, 20, 15, 180); color_SlotOutline = sf::Color(255, 69, 0); color_HudBg = sf::Color(25, 15, 15, 240); color_StatsBgFill = sf::Color(45, 15, 15, 220); color_StatsBgOutline = sf::Color(220, 20, 60);
    } else if (diff == Difficulty::MEDIUM) {
        maxWaves = 20; mapPath = { {0, 400}, {200, 400}, {200, 150}, {600, 150}, {600, 350}, {400, 350}, {400, 550}, {900, 550}, {900, 250}, {1100, 250}, {1100, 450}, {1300, 450} };
        color_Ground = sf::Color(15, 12, 30); color_Path = sf::Color(45, 20, 70); color_SlotFill = sf::Color(10, 50, 60, 180); color_SlotOutline = sf::Color(0, 240, 255); color_HudBg = sf::Color(20, 20, 25, 240); color_StatsBgFill = sf::Color(30, 15, 45, 220); color_StatsBgOutline = sf::Color(255, 0, 128);
    } else {
        maxWaves = 10; mapPath = { {0, 100}, {300, 100}, {300, 300}, {100, 300}, {100, 500}, {500, 500}, {500, 200}, {800, 200}, {800, 540}, {1100, 540}, {1100, 300}, {1300, 300} };
        color_Ground = sf::Color(35, 35, 35); color_Path = sf::Color(45, 45, 45); color_SlotFill = sf::Color(80, 80, 80, 180); color_SlotOutline = sf::Color::White; color_HudBg = sf::Color(65, 65, 65, 220); color_StatsBgFill = sf::Color(55, 55, 55, 200); color_StatsBgOutline = sf::Color::White;
    }
    backgroundRect.setFillColor(color_Ground); statsBackground.setSize({210.0f, 105.0f}); statsBackground.setFillColor(color_StatsBgFill); statsBackground.setOutlineColor(color_StatsBgOutline); statsBackground.setOutlineThickness(1.5f); statsBackground.setPosition(Config::WINDOW_WIDTH - 230.0f, 10.0f);
    if (!mapPath.empty()) baseShape.setPosition(mapPath.back().x - 30.0f, mapPath.back().y);
    initPathGraphics(); initPlacementSlots(); initHUD(); restartGame();
}

// przywracanie poczatkowych wartosci zasobow, czyszczenie wektorow obiektow oraz resetowanie licznikow fal
void GameManager::restartGame() {
    gameObjects.clear(); scoreSaved = false;
    for (auto& slot : placementSlots) { slot.isOccupied = false; slot.shape.setFillColor(color_SlotFill); }
    if (currentDifficulty == Difficulty::EASY) { money = 300; lives = 100; } else if (currentDifficulty == Difficulty::MEDIUM) { money = 400; lives = 80; } else if (currentDifficulty == Difficulty::HARD) { money = 500; lives = 50; }
    currentWave = 1; enemiesSpawnedInWave = 0; bossesToSpawn = 0; spawnTimer = 1.0f; wavePauseTimer = 5.0f; isWavePause = true; isGameOver = false; isWin = false; selectedType = TowerType::Blue;
}

// obsluga klikniecia mysza - ulepszanie istniejących wiez, klikanie przyciskow interfejsu lub budowanie nowej wiezy w wolnym slocie
bool GameManager::placeTower(float x, float y) {
    if (isGameOver || isWin) { if (restartButton.getGlobalBounds().contains(x, y)) restartGame(); if (menuButton.getGlobalBounds().contains(x, y)) return true; return false; }
    if (hudMenuButton.getGlobalBounds().contains(x, y)) return true;
    for (auto& obj : gameObjects) {
        if (Tower* t = dynamic_cast<Tower*>(obj.get())) {
            if (t->canUpgrade() && t->getUpgradeBounds().contains(x, y)) {
                int cost = t->getUpgradeCost(); if (money >= cost) { money -= cost; t->upgrade(); return false; }
            }
        }
    }
    for (auto& btn : hudButtons) { if (btn.icon.getGlobalBounds().contains(x, y)) { selectedType = btn.type; return false; } }
    int price = (selectedType == TowerType::Blue) ? 50 : (selectedType == TowerType::Green) ? 150 : 250;
    for (auto& slot : placementSlots) {
        if (!slot.isOccupied && slot.shape.getGlobalBounds().contains(x, y)) {
            if (money >= price) { gameObjects.push_back(std::unique_ptr<GameObject>(new Tower(slot.shape.getPosition().x, slot.shape.getPosition().y, selectedType))); slot.isOccupied = true; slot.shape.setFillColor(sf::Color(color_Path.r / 2, color_Path.g / 2, color_Path.b / 2, 200)); money -= price; return false; }
        }
    }
    return false;
}

// tworzenie elementow dolnego panelu hud - przyciskow sklepu wiez, opisow statystyk oraz przycisku powrotu do menu
void GameManager::initHUD() {
    float hudHeight = 105.0f; hudBackground.setSize({(float)Config::WINDOW_WIDTH, hudHeight}); hudBackground.setFillColor(color_HudBg); hudBackground.setPosition(0, (float)Config::WINDOW_HEIGHT - hudHeight);
    struct TowerDef { TowerType t; sf::Color c; int p; std::string s; };
    std::vector<TowerDef> defs = { {TowerType::Blue, sf::Color::Blue, 50, "Niebieska (Cena: 50)\nDMG: 1 | RNG: 200 | SPD: 0.8s\nUpg 1: 40z (RNG -> 260)\nUpg 2: 60z (RNG -> 320)\nUpg 3 [MAX]: 300z (RNG -> 380)"}, {TowerType::Green, sf::Color::Green, 150, "Zielona (Cena: 150)\nDMG: 0.5 | RNG: 200 | SPD: 0.3s\nUpg 1: 100z (DMG -> 1.0)\nUpg 2: 150z (DMG -> 1.5)\nUpg 3 [MAX]: 600z (DMG -> 2.0)"}, {TowerType::Pink, sf::Color(255, 105, 180), 250, "Rozowa (Cena: 250)\nDMG: 4 | RNG: 200 | SPD: 1.5s\nUpg 1: 150z (SPD -> 1.1s)\nUpg 2: 220z (SPD -> 0.7s)\nUpg 3 [MAX]: 1000z (SPD -> 0.3s)"} };
    hudButtons.clear();
    for (int i = 0; i < 3; ++i) {
        HudButton btn; btn.type = defs[i].t; btn.price = defs[i].p; btn.icon.setRadius(20.0f); btn.icon.setFillColor(defs[i].c); btn.icon.setOutlineThickness(3.0f); btn.icon.setOutlineColor(sf::Color::White); btn.icon.setPosition(150.0f + i * 280.0f, (float)Config::WINDOW_HEIGHT - 75.0f);
        btn.stats.setFont(font); btn.stats.setCharacterSize(12); btn.stats.setFillColor(sf::Color::White); btn.stats.setString(defs[i].s); btn.stats.setPosition(200.0f + i * 280.0f, (float)Config::WINDOW_HEIGHT - 100.0f); hudButtons.push_back(btn);
    }
    hudMenuButton.setSize({130.0f, 40.0f}); hudMenuButton.setFillColor(sf::Color(color_Path.r + 20, color_Path.g + 20, color_Path.b + 20)); hudMenuButton.setOutlineThickness(2.0f); hudMenuButton.setOutlineColor(color_SlotOutline); hudMenuButton.setOrigin(65.0f, 20.0f); hudMenuButton.setPosition((float)Config::WINDOW_WIDTH - 100.0f, (float)Config::WINDOW_HEIGHT - 52.5f);
    hudMenuText.setFont(font); hudMenuText.setString("MENU"); hudMenuText.setCharacterSize(18); hudMenuText.setFillColor(sf::Color::White); hudMenuText.setStyle(sf::Text::Bold); sf::FloatRect hmbBounds = hudMenuText.getLocalBounds(); hudMenuText.setOrigin(hmbBounds.left + hmbBounds.width / 2.0f, hmbBounds.top + hmbBounds.height / 2.0f); hudMenuText.setPosition(hudMenuButton.getPosition());
}

// generowanie prostokatnych grafik drogi na podstawie wektora punktow sciezki mapPath
void GameManager::initPathGraphics() {
    const float thickness = 60.0f; pathSegments.clear();
    for (size_t i = 0; i < mapPath.size() - 1; ++i) {
        sf::Vector2f start = mapPath[i]; sf::Vector2f end = mapPath[i + 1]; sf::RectangleShape segment; float length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2)); segment.setSize({ length, thickness }); segment.setFillColor(color_Path); segment.setOrigin(0, thickness / 2.0f); float angle = std::atan2(end.y - start.y, end.x - start.x) * 180.0f / 3.14159f; segment.setRotation(angle); segment.setPosition(start); pathSegments.push_back(segment);
    }
}

// algorytm rozstawiania kwadratowych slotow pod budowe wiez w bezpiecznej odleglosci od sciezki i innych slotow
void GameManager::initPlacementSlots() {
    placementSlots.clear(); const float slotSize = 40.0f; const float offset = 70.0f; const float step = 140.0f;
    for (size_t i = 0; i < mapPath.size() - 1; ++i) {
        sf::Vector2f start = mapPath[i], end = mapPath[i + 1]; sf::Vector2f dir = end - start; float len = std::sqrt(dir.x * dir.x + dir.y * dir.y); if (len == 0) continue; sf::Vector2f unitDir = dir / len; sf::Vector2f normal(-unitDir.y, unitDir.x);
        for (float d = step / 2.0f; d < len; d += step) {
            if (placementSlots.size() >= 55) break; sf::Vector2f pCenter = start + unitDir * d;
            for (int side : {-1, 1}) {
                sf::Vector2f potPos = pCenter + normal * (offset * (float)side); sf::FloatRect sRect(potPos.x - slotSize/2, potPos.y - slotSize/2, slotSize, slotSize); bool fail = false;
                for (auto& seg : pathSegments) if (seg.getGlobalBounds().intersects(sRect)) fail = true;
                for (auto& s : placementSlots) { float dx = s.shape.getPosition().x - potPos.x, dy = s.shape.getPosition().y - potPos.y; if (std::sqrt(dx*dx+dy*dy) < 70.0f) fail = true; }
                if (potPos.x < 40 || potPos.x > (float)Config::WINDOW_WIDTH - 40 || potPos.y < 40 || potPos.y > (float)Config::WINDOW_HEIGHT - 130) fail = true;
                if (!fail) { PlacementSlot slot; slot.shape.setSize({slotSize, slotSize}); slot.shape.setOrigin(slotSize/2, slotSize/2); slot.shape.setPosition(potPos); slot.shape.setFillColor(color_SlotFill); slot.shape.setOutlineColor(color_SlotOutline); slot.shape.setOutlineThickness(1.5f); placementSlots.push_back(slot); }
            }
        }
    }
}

// odswiezanie napisow informacyjnych o stanie gracza oraz przygotowywanie komunikatow o falach lub podsumowaniu punktacji
void GameManager::updateUI() {
    moneyText.setString("Zloto: " + std::to_string(money) + "\nZycia: " + std::to_string(lives) + "\nFala: " + std::to_string(currentWave) + " / " + std::to_string(maxWaves));
    int bossesThisWave = 0; if (currentWave == 10) bossesThisWave = 1; else if (currentWave == 20 && (currentDifficulty == Difficulty::MEDIUM || currentDifficulty == Difficulty::HARD)) bossesThisWave = 2; else if (currentWave == 30 && currentDifficulty == Difficulty::HARD) bossesThisWave = 3; else if (currentWave == 40 && currentDifficulty == Difficulty::HARD) bossesThisWave = 4;
    if (isWavePause) {
        if (bossesThisWave > 0) waveAnnouncementText.setString("FALA " + std::to_string(currentWave) + ": " + std::to_string(bossesThisWave) + "x BOSS!"); else waveAnnouncementText.setString("FALA " + std::to_string(currentWave));
        sf::FloatRect tb = waveAnnouncementText.getLocalBounds(); waveAnnouncementText.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f); waveAnnouncementText.setPosition((float)Config::WINDOW_WIDTH/2.0f, (float)Config::WINDOW_HEIGHT/2.0f - 140.0f);
    }
    if (isGameOver || isWin) {
        int finalScore = money + (lives * 100); if (!scoreSaved) { loadAndSaveLeaderboard(finalScore); scoreSaved = true; }
        scoreText.setString("SCORE: " + std::to_string(finalScore)); sf::FloatRect scBounds = scoreText.getLocalBounds(); scoreText.setOrigin(scBounds.left + scBounds.width / 2.0f, scBounds.top + scBounds.height / 2.0f); scoreText.setPosition(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f - 40.0f);
    }
}

// glowna logika gry wykonywana co klatke - odliczanie czasu, aktualizacja jednostek, kolizje z baza i warunki wygranej/przegranej
void GameManager::update(float dt) {
    if (isGameOver || isWin) return;
    int bossesThisWave = 0; if (currentWave == 10) bossesThisWave = 1; else if (currentWave == 20 && (currentDifficulty == Difficulty::MEDIUM || currentDifficulty == Difficulty::HARD)) bossesThisWave = 2; else if (currentWave == 30 && currentDifficulty == Difficulty::HARD) bossesThisWave = 3; else if (currentWave == 40 && currentDifficulty == Difficulty::HARD) bossesThisWave = 4;
    int maxEnemiesThisWave = (bossesThisWave > 0) ? bossesThisWave : (Config::BASE_ENEMIES_PER_WAVE + (currentWave - 1) * Config::ENEMIES_INCREMENT_PER_WAVE);
    std::vector<Enemy*> tempEnemies; std::vector<Projectile*> tempProjectiles;
    for (auto& obj : gameObjects) { if (Enemy* e = dynamic_cast<Enemy*>(obj.get())) tempEnemies.push_back(e); if (Projectile* p = dynamic_cast<Projectile*>(obj.get())) tempProjectiles.push_back(p); }
    if (isWavePause) { wavePauseTimer -= dt; if (wavePauseTimer <= 0) { isWavePause = false; enemiesSpawnedInWave = 0; spawnTimer = 0.5f; } } else {
        if (enemiesSpawnedInWave < maxEnemiesThisWave) {
            spawnTimer -= dt; if (spawnTimer <= 0) { spawnEnemy(); enemiesSpawnedInWave++; if (bossesThisWave > 0) spawnTimer = bossSpawnCooldown; else spawnTimer = std::max(0.2f, 1.2f - (currentWave * 0.1f)); }
        }
    }
    size_t oldProjCount = tempProjectiles.size();
    for (auto& obj : gameObjects) { if (Tower* t = dynamic_cast<Tower*>(obj.get())) t->update(dt, tempEnemies, tempProjectiles); }
    for (size_t i = oldProjCount; i < tempProjectiles.size(); ++i) gameObjects.push_back(std::unique_ptr<GameObject>(tempProjectiles[i]));
    for (auto it = gameObjects.begin(); it != gameObjects.end();) {
        if (Enemy* e = dynamic_cast<Enemy*>(it->get())) {
            e->update(dt);
            if (baseShape.getGlobalBounds().contains(e->getPosition())) { lives -= e->isBoss() ? 40 : 1; it = gameObjects.erase(it); if (lives <= 0) { lives = 0; isGameOver = true; } }
            else if (e->isDead()) { money += e->isBoss() ? 100 : 20; it = gameObjects.erase(it); } else ++it;
        } else if (Projectile* p = dynamic_cast<Projectile*>(it->get())) { p->update(dt); if (!p->isActive()) it = gameObjects.erase(it); else ++it; } else ++it;
    }
    if (!isWavePause && !isGameOver && !isWin) {
        int activeEnemies = 0; for (auto& obj : gameObjects) { if (dynamic_cast<Enemy*>(obj.get())) activeEnemies++; }
        if (enemiesSpawnedInWave >= maxEnemiesThisWave && activeEnemies == 0) { if (currentWave >= maxWaves) isWin = true; else { isWavePause = true; wavePauseTimer = 5.0f; currentWave++; } }
    }
    baseShape.rotate(45.0f * dt); static float animationTimer = 0.0f; animationTimer += dt; float currentScale = 1.0f + 0.07f * std::sin(animationTimer * 5.0f); baseShape.setScale(currentScale, currentScale);
    updateUI();
}

// renderowanie tła, segmentow drogi, baz, slotow, obiektow gry (wieze, pociski) oraz interfejsu panelu hud i ekranow konca gry
void GameManager::draw(sf::RenderWindow& window) {
    window.draw(backgroundRect); for (auto& seg : pathSegments) window.draw(seg); window.draw(baseShape); for (auto& slot : placementSlots) window.draw(slot.shape);
    for (auto& obj : gameObjects) { if (Tower* t = dynamic_cast<Tower*>(obj.get())) t->draw(window, money); else obj->draw(window); }
    window.draw(hudBackground); for (auto& btn : hudButtons) { btn.icon.setOutlineColor(btn.type == selectedType ? sf::Color::Yellow : sf::Color::White); window.draw(btn.icon); window.draw(btn.stats); }
    window.draw(statsBackground); window.draw(moneyText); window.draw(hudMenuButton); window.draw(hudMenuText);
    if (isWavePause && !isGameOver && !isWin) window.draw(waveAnnouncementText);
    if (isGameOver || isWin) {
        sf::RectangleShape overlay({(float)Config::WINDOW_WIDTH, (float)Config::WINDOW_HEIGHT}); overlay.setFillColor(sf::Color(0, 0, 0, 200)); window.draw(overlay);
        if (isGameOver) window.draw(gameOverText); else window.draw(winText); window.draw(scoreText); window.draw(leaderboardText); window.draw(restartButton); window.draw(restartText); window.draw(menuButton); window.draw(menuText);
    }
}

// mechanizm tworzenia obiektow wrogow (zwyklych lub bossow) ze skalowaniem zdrowia i predkosci zależnie od poziomu trudnosci i numeru fali
void GameManager::spawnEnemy() {
    float speedMultiplier = 1.0f; if (currentDifficulty == Difficulty::MEDIUM) speedMultiplier = 1.15f; if (currentDifficulty == Difficulty::HARD) speedMultiplier = 1.45f;
    bool isBossWave = false; if (currentWave == 10) isBossWave = true; if (currentWave == 20 && (currentDifficulty == Difficulty::MEDIUM || currentDifficulty == Difficulty::HARD)) isBossWave = true; if (currentWave == 30 && currentDifficulty == Difficulty::HARD) isBossWave = true; if (currentWave == 40 && currentDifficulty == Difficulty::HARD) isBossWave = true;
    if (isBossWave) { std::unique_ptr<Enemy> boss(new Enemy(mapPath, 50.0f * speedMultiplier, 400.0f)); boss->setBossAppearance(); gameObjects.push_back(std::move(boss)); }
    else { float enemyHP = 8.0f; float enemySpeed = (120.0f + (currentWave * 5.0f)) * speedMultiplier; gameObjects.push_back(std::unique_ptr<GameObject>(new Enemy(mapPath, enemySpeed, enemyHP))); }
}

// obsluga pliku tekstowego z wynikami - wczytanie tablicy, dodanie aktualnego wyniku, sortowanie od najwyzszego i zapis top 3
void GameManager::loadAndSaveLeaderboard(int finalScore) {
    highScores.clear(); std::ifstream inputFile("leaderboard.txt"); int tempScore; std::string sep1, tempOutcome, sep2, tempDiff;
    while (inputFile >> tempScore >> sep1 >> tempOutcome >> sep2 >> tempDiff) highScores.push_back({tempScore, tempOutcome, tempDiff}); inputFile.close();
    std::string currentOutcome = isWin ? "Win" : "Lost"; std::string currentDiffStr = "EASY"; if (currentDifficulty == Difficulty::MEDIUM) currentDiffStr = "MEDIUM"; if (currentDifficulty == Difficulty::HARD) currentDiffStr = "HARD";
    highScores.push_back({finalScore, currentOutcome, currentDiffStr});
    std::sort(highScores.begin(), highScores.end(), [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    if (highScores.size() > 3) highScores.resize(3);
    std::ofstream outputFile("leaderboard.txt"); for (const auto& entry : highScores) outputFile << entry.score << " | " << entry.outcome << " | " << entry.difficulty << "\n"; outputFile.close();
    std::string lbString = "--- TOP BEST SCORES ---\n"; for (int i = 0; i < 3; ++i) { if (i < (int)highScores.size()) lbString += std::to_string(highScores[i].score) + " | " + highScores[i].outcome + " | " + highScores[i].difficulty + "\n"; else lbString += "---\n"; }
    leaderboardText.setString(lbString); sf::FloatRect lbBounds = leaderboardText.getLocalBounds(); leaderboardText.setOrigin(lbBounds.left + lbBounds.width / 2.0f, 0.0f); leaderboardText.setPosition(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f + 15.0f);
}
