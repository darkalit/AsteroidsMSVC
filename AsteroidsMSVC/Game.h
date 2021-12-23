#ifndef ASTEROIDSMSVC_GAME_H
#define ASTEROIDSMSVC_GAME_H

#define _USE_MATH_DEFINES 
#include <iostream>
#include <map>
#include <random>

#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"


class Game {
private:
    sf::RenderWindow*   window;
    sf::VideoMode       videoMode;
    sf::Event           event{};

    sf::Font font;
    sf::Text scr_shps[4];
    sf::Text gameover;

    int     ships;
    int     score;

    bool    attackf;
    bool    AsteroidF;
    float   asteroidAngle;
    float   gameDelayRelax;

    bool    gamepaused;

    bool    playerInvis;
    int     invisCooldown;
    int     invisCooldownMax;

    int     music_num;

    std::random_device                              rd;
    std::mt19937                                    gen;

    std::map<std::string, sf::SoundBuffer>          soundBuffers;
    std::map<std::string, sf::Sound>                sounds;
    std::map<int, sf::Music>                        music;

    std::vector<std::string>                        AsTexDirectories;

    std::map<std::string, sf::CircleShape*>         shapes;
    std::vector<Bullet*>                            bullets;

    std::map<std::string, sf::Texture*>             textures;
    std::vector<std::string>                        textures_name;
    std::map<std::string, std::vector<Asteroid*>>   asteroids;
    std::map<Asteroid*, float>                      asteroidRS;
    std::map<Asteroid*, float>                      asteroidR;

    void initVars();
    void initTextures();
    void initText();
    void initWindow();
public:
    // Constructor/Destructor
    Game();
    virtual ~Game();

    Player player;

    // Accessors
    bool running() const;

    // Functions
    void PollEvents();
    void updatePlayer();
    void updateAsteroids();
    void updateBullets();
    void updateGui();
    void update();
    void render();
};


#endif
