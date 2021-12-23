#ifndef ASTEROIDSMSVC_PLAYER_H
#define ASTEROIDSMSVC_PLAYER_H

#define _USE_MATH_DEFINES 
#include <cmath>

#include "Object.h"

class Player : public Object {
private:
    float           acceleration;

    sf::Vector2f    redirection;
    

    float           aCooldown;
    float           aCooldownMax;

    void            initVars();
    void            initShape();
public:
                    Player(float x = 0.f, float y = 0.f);
    virtual         ~Player();

    sf::CircleShape body;

    sf::Vector2f    direction;

    
    
    //void setDirection(sf::Vector2f vector);

    void                setPos          (float x, float y)                  override;
    sf::Vector2f        getPos          ()                                  override;
    

    void                Rotate          (float angle)                       override; 


    sf::Vector2f        getDirection    ()                                  override;

    const sf::FloatRect getBounds       ()                            const override;


    void                updateInput     ();
    void                update          ()                                  override;
    void                render          (sf::RenderTarget* target)          override;
};


#endif //ASTEROIDSMSVC_PLAYER_H
