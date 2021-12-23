#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "Object.h"

class Bullet : public Object {
private:
    sf::CircleShape shape;

    sf::Vector2f direction;

    void initVars();

public:
    float lifeTime;
                            Bullet          ();
                            Bullet          (sf::CircleShape* shape, 
                                             sf::Vector2f pos, 
                                             sf::Vector2f direction, 
                                             float speed);
    virtual                 ~Bullet         ();

    void                    setLifeTime     (float lifeTime);
    float                   getLifeTime     ();

    sf::Vector2f	        getPos          ()                                  override;
    void			        setPos          (float x = 0, float y = 0)          override;


    void			        Rotate          (float angle)                       override;

    // Get direction vector of moving object;
    sf::Vector2f	        getDirection    ()                                  override;

    const sf::FloatRect     getBounds       ()                            const override;



    void                    update          ()                                  override;
    void                    render          (sf::RenderTarget* target)          override;
};


#endif //ASTEROIDS_BULLET_H
