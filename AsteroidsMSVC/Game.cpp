#include "Game.h"


// Constructor/Destructor;
Game::Game() {
    this->initVars();
    this->initWindow();
    this->initTextures();
    this->initText();    

    this->player.setPos((float)this->videoMode.width / 2,
                        (float)this->videoMode.height / 2);
}

Game::~Game() {
    delete this->window;

    for (auto& i : this->shapes)
        delete i.second;

    for (auto* i : this->bullets)
        delete i;

    for (auto& i : this->textures)
        delete i.second;

    for (auto& i : this->asteroids)
        for (auto& j : i.second)
            delete j;
}

// Initializing window
void Game::initWindow() {
    // Width equal 2/3 of desktop; Height equals 3/4 of desktop
    this->videoMode.width = sf::VideoMode::getDesktopMode().width / 3 * 2;
    this->videoMode.height = this->videoMode.width * 3 / 4;
    
    // Naming the window
    this->window = new sf::RenderWindow(this->videoMode, "Asteroids",
        sf::Style::Titlebar | sf::Style::Close);

    // Setting the frame limit
    this->window->setFramerateLimit(60);
}

// Check running status
bool Game::running() const {
    return this->window->isOpen();
}

// Initializing some variables
void Game::initVars() {
    this->window = nullptr;

    this->ships = 3;
    this->score = 0;

    this->gamepaused = false;
    this->gameDelayRelax = 0.f;

    this->attackf = true;

    this->AsteroidF = true;
    this->asteroidAngle = 0;

    this->textures_name = { "asteroid1", "asteroid2", "asteroid3", "asteroid4", "asteroid5" };

    for (auto& i : this->asteroids)
        for (auto& j : i.second)
            this->asteroidR[j] = 0;

    this->playerInvis = false;
    this->invisCooldown = 0;
    this->invisCooldownMax = 200;

    this->soundBuffers["shoot"].loadFromFile("Sounds\\Effects\\shot.wav");
    this->sounds["shoot"].setBuffer(this->soundBuffers["shoot"]);

    this->soundBuffers["ship_destroyed"].loadFromFile("Sounds\\Effects\\ship_destroyed.wav");
    this->sounds["ship_destroyed"].setBuffer(this->soundBuffers["ship_destroyed"]);

    this->soundBuffers["asteroid_destroyed"].loadFromFile("Sounds\\Effects\\asteroid_destroyed.wav");
    this->sounds["asteroid_destroyed"].setBuffer(this->soundBuffers["asteroid_destroyed"]);

    for (int i = 1; i < 6; ++i) {
        this->music[i - 1].openFromFile("Sounds\\Music\\" + std::to_string(i) + ".ogg");
        this->music[i - 1].setVolume(10);
    }

    this->gen.seed(rd());
    this->music_num = this->gen() % 5;
    this->music[this->music_num].play();

    this->AsTexDirectories = { 
        "Textures\\Asteroids\\Asteroid1.png", 
        "Textures\\Asteroids\\Asteroid2.png",
        "Textures\\Asteroids\\Asteroid3.png", 
        "Textures\\Asteroids\\Asteroid4.png",
        "Textures\\Asteroids\\Asteroid5.png"};
}

// Initializing textures
void Game::initTextures() {
    this->shapes["bullet"] = new sf::CircleShape();
    this->shapes["bullet"]->setFillColor(sf::Color::White);
    this->shapes["bullet"]->setOutlineColor(sf::Color::Transparent);
    this->shapes["bullet"]->setRadius(5.0f);
    this->shapes["bullet"]->setPointCount(4);
    this->shapes["bullet"]->setOrigin(3 * this->shapes["bullet"]->getRadius() / (2 * sqrtf(3)),
                                      3 * this->shapes["bullet"]->getRadius() / (2 * sqrtf(3)));
    this->shapes["bullet"]->setRotation(45.f);

    for (int i = 0; i < this->textures_name.size(); ++i) {
        this->textures[this->textures_name[i]] = new sf::Texture();
        this->textures[this->textures_name[i]]->loadFromFile(this->AsTexDirectories[i]);
    }
}

// Initializing text
void Game::initText() {
    this->font.loadFromFile("Fonts\\Teko.ttf");

    for (int i = 0; i != 4; ++i) {
        scr_shps[i].setFont(font);
        scr_shps[i].setCharacterSize(60);
        scr_shps[i].setFillColor(sf::Color::White);
    }

    scr_shps[0].setPosition(10.f, 60.f);
    scr_shps[1].setPosition(150.f, 60.f);
    scr_shps[2].setPosition(10.f, 0.f);
    scr_shps[3].setPosition(150.f, 0.f);

    gameover.setFont(font);
    gameover.setCharacterSize(100);
    gameover.setFillColor(sf::Color::White);
    gameover.setPosition((float)this->videoMode.width / 2 - 150, (float)this->videoMode.height / 2 - 100);
}

void Game::render() {

    // Clear old frames;
    this->window->clear(sf::Color::Black);

    // Draw objects;
    this->player.render(this->window);

    for (auto* bullet : this->bullets)
        bullet->render(this->window);

    for (auto& i : this->asteroids)
        for (auto* j : i.second)
            j->render(this->window);

    for (int i = 0; i != 4; ++i)
        this->window->draw(scr_shps[i]);

    if (ships < 0) {
        this->window->draw(gameover);
        this->gamepaused = true;
        this->music[music_num].stop();
    }

    // Render window;
    this->window->display();
}

void Game::PollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (this->event.key.code == sf::Keyboard::P) {
                this->gamepaused = !this->gamepaused;
                if (this->gamepaused)
                    this->music[this->music_num].pause();
                else if (!this->gamepaused)
                    this->music[this->music_num].play();
            }
            break;
        }
    }
}

// Update game events
void Game::update() {
    this->gen.seed(rd());
    this->PollEvents();
    if (!this->gamepaused)
    {
        if (this->music[this->music_num].getStatus() == sf::SoundSource::Status::Stopped) {
            int flag_m = 0;
            do {
                flag_m = this->gen() % 5;
            } while(this->music_num == flag_m);
            this->music_num = flag_m;
            this->music[music_num].play();
        }
        this->updateBullets();
        this->updateAsteroids();
        this->updatePlayer();
    }
    

    this->updateGui();
}

void Game::updateAsteroids() {

    // Creating 4 big asteroids around the player randomly
    if (this->AsteroidF) {
        // Generating random coordinates for big asteroids
        std::vector<sf::Vector2f> rnd_pos(4);
        for (int i = 0; i != 4;) {
            int rnd_x = gen() % (this->videoMode.width - 50);
            int rnd_y = gen() % (this->videoMode.height - 50);
            if ((powf(rnd_x - player.getPos().x, 2) +
                 powf(rnd_y - player.getPos().y, 2)) >= powf(400.f, 2)) {
                rnd_pos[i] = sf::Vector2f(rnd_x, rnd_y);
                ++i;
            }
        }

        // Creating asteroids
        for (int i = 0; i != 4; ++i){
            this->asteroids["asteroidsB"].push_back(
                                        new Asteroid(*this->textures[this->textures_name[this->gen() % 5]], 0.25f,
                                        rnd_pos[i],
                                        normV(sf::Vector2f(this->gen() % 100, this->gen() % 100)),
                                        this->gen() % 6 + 2));
            this->asteroidRS.insert(std::make_pair(asteroids["asteroidsB"][i], ((float)(this->gen() % 5) + 1.f) / 10));
        }
        this->AsteroidF = false;
    }

    // Spawn delay if there are no asteroids
    if (this->asteroids["asteroidsM"].empty() && 
        this->asteroids["asteroidsB"].empty() && 
        this->asteroids["asteroidsS"].empty()) {
        this->gameDelayRelax += 0.1f;
    }
    
    if (gameDelayRelax > 12.f) {
        this->gameDelayRelax = 0.f;
        this->AsteroidF = true;
    }

    // Destroying asteroids and asteroids scrolling through window bounds
    for (auto& k : this->asteroids) {
        int c1 = 0;
        for (auto& i : k.second) {
            i->screenMove(this->videoMode);
            i->update();

            if (this->asteroidR[i] >= 360)
                this->asteroidR[i] = 0;
            i->Rotate(this->asteroidR[i]);

            int c2 = 0;
            for (auto& j : this->bullets) {
                if (j->getBounds().intersects(i->getBounds())) {
                    if (k.second == this->asteroids["asteroidsB"]) {
                        for (int w = 0; w != 2; ++w) {
                            this->asteroids["asteroidsM"].push_back(
                                new Asteroid(*this->textures[this->textures_name[this->gen() % 5]], 0.2f,
                                sf::Vector2f(i->getPos()),
                                normV(sf::Vector2f(this->gen() % 100, this->gen() % 100)),
                                this->gen() % 6 + 2));
                        }
                        for (int v = 0; v != asteroids["asteroidsM"].size(); ++v)
                            this->asteroidRS.insert(std::make_pair(asteroids["asteroidsM"][v], ((float)(this->gen() % 5) + 1.f) / 10));

                        this->sounds["asteroid_destroyed"].play();
                        k.second.erase(k.second.begin() + c1);
                        this->bullets.erase(this->bullets.begin() + c2);
                        this->score += 100;
                    }
                    if (k.second == this->asteroids["asteroidsM"]) {
                        for (int w = 0; w != 2; ++w) {
                            this->asteroids["asteroidsS"].push_back(
                                new Asteroid(*this->textures[this->textures_name[this->gen() % 5]], 0.12f,
                                sf::Vector2f(i->getPos()),
                                normV(sf::Vector2f(this->gen() % 100, this->gen() % 100)),
                                this->gen() % 6 + 2));
                        }
                        for (int v = 0; v != asteroids["asteroidsS"].size(); ++v)
                            this->asteroidRS.insert(std::make_pair(asteroids["asteroidsS"][v], ((float)(this->gen() % 5) + 1.f) / 10))
                            ;
                        this->sounds["asteroid_destroyed"].play();
                        k.second.erase(k.second.begin() + c1);
                        this->bullets.erase(this->bullets.begin() + c2);
                        this->score += 50;
                    }
                    if (k.second == this->asteroids["asteroidsS"]) {
                        this->sounds["asteroid_destroyed"].play();
                        k.second.erase(k.second.begin() + c1);
                        this->bullets.erase(this->bullets.begin() + c2);
                        this->score += 25;
                    }
                }
                ++c2;
            }
            ++c1;
            this->asteroidR[i] += this->asteroidRS[i];
        }
    }
}

void Game::updatePlayer() {
    this->player.update();
    this->player.screenMove(this->videoMode);

    for (auto& i : this->asteroids)
        for (auto& j : i.second)
            if (!this->playerInvis)
                if (
                   (powf(this->player.getPos().x - j->getPos().x, 2) + 
                    powf(this->player.getPos().y - j->getPos().y, 2)) <= powf(j->getBounds().width/2, 2)) {
                    this->sounds["ship_destroyed"].play();
                    this->player.setPos((float)this->videoMode.width / 2,
                                        (float)this->videoMode.height / 2);
                    this->player.direction = sf::Vector2f(0, 0);
                    this->ships--;
                    this->playerInvis = true;
                }

    // Player invisibility on asteroids hit
    if ((this->invisCooldown < this->invisCooldownMax) && (this->playerInvis))
        this->invisCooldown ++;
    else if (this->invisCooldown >= this->invisCooldownMax) {
        this->invisCooldown = 0;
        this->playerInvis = false;
    }
    
    if (this->playerInvis)
        this->player.body.setFillColor(sf::Color(255, 255, 255, 75));
    if ((this->invisCooldown % 10) == 0)
        this->player.body.setFillColor(sf::Color::White);
}

void Game::updateBullets() {

    // Erase bullets;
    int i = 0;
    for (auto* bullet : this->bullets) {
        bullet->screenMove(this->videoMode);
        bullet->setLifeTime(bullet->getLifeTime() - 0.3f);
        if (bullet->getLifeTime() < 0.2f) {
            this->bullets.erase(this->bullets.begin() + i);
        }
        ++i;
    }

    // Recoil
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::X)) &&
        this->attackf) {
        this->sounds["shoot"].play();
        this->bullets.push_back(new Bullet(this->shapes["bullet"],
                                this->player.getPos(),
                                this->player.getDirection(),
                                20.f));
        this->player.direction.x -=  sinf(M_PI * this->player.getAngle() / 180) * 4.f;
        this->player.direction.y -= -cosf(M_PI * this->player.getAngle() / 180) * 4.f;
        this->attackf = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        this->attackf = true;
    }

    // Update bullets
    for (auto* bullet : this->bullets) {
        bullet->update();
    }
}

void Game::updateGui()
{
    this->scr_shps[0].setString("Ships:");
    this->scr_shps[1].setString(std::to_string(ships));

    this->scr_shps[2].setString("Score:");
    this->scr_shps[3].setString(std::to_string(score));

    this->gameover.setString("Game Over");
}
