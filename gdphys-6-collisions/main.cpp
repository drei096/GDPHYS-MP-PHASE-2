#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "P6 components/PhysVector.h"
#include "P6 components/PhysParticle.h"
#include "Utils.h"
#include "P6 components/PhysicsWorld.h"
#include "P6 Components/DragForceGenerator.h"
#include "P6 Components/ForceGenerator.h"
#include "P6 Components/ForceRegistry.h"
#include "P6 Components/GravityForceGenerator.h"
#include "P6 Components/Springs/AnchoredSpring.h"
#include "P6 Components/Springs/BungeeSpring.h"
#include "P6 Components/Collision/ParticleContact.h"
#include "P6 Components/Links/Rod.h"
#include "P6 Components/Links/ParticleLink.h"
#include "P6 Components/Links/Cable.h"

/*NOTES 5/8/2021 11:28 AM
* Added working collision
* Manually added 5 particles
* Collision works when user presses SPACE to start sim
* USER CAN MODIFY GRAVITY AT GRAVITYFORCEGENERATOR.H
* 
* WHAT NEEDS TO BE ADDED:
* - cable class implementation (i already added a Cable class)
* - implement gravity na hindi sumasagad pababa yung particles and cable
*/


#define PI 3.14159

using namespace std;


int main()
{
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    Utils utils;
    PhysicsWorld pWorld = PhysicsWorld();


    sf::RenderWindow window(sf::VideoMode(720, 500), "P6 Test");


    sf::Event event;
    Utils::offset = PhysVector(0, 250);


    //Bullet 1 particle
    PhysParticle bullet;
    bullet.name = "Bullet 1";
    bullet.mass = 5.0f;
    //PhysVector dir = PhysVector(-1, 0);
    //bullet.addForce(dir * 50);
    

    bullet.particleShape.setRadius(15.0f);
    bullet.radius = bullet.particleShape.getRadius();
    bullet.particleShape.setFillColor(sf::Color::White);
    bullet.particleShape.setOrigin(bullet.particleShape.getRadius(), bullet.particleShape.getRadius());

    PhysVector renderPoint1 = bullet.toRenderPoint();
    bullet.position = PhysVector(245,0);

    bullet.initialPos = bullet.position;
    bullet.particleShape.setPosition(renderPoint1.x, renderPoint1.y);


    //BULLET 2
    PhysParticle bullet2;
    bullet2.name = "Bullet 2";
    bullet2.mass = 1.5;
    //PhysVector dir2 = PhysVector(1, 0);
    //bullet2.addForce(dir2 * 50);
    

    bullet2.particleShape.setRadius(15.0f);
    bullet2.radius = bullet2.particleShape.getRadius();
    bullet2.particleShape.setFillColor(sf::Color::Blue);
    bullet2.particleShape.setOrigin(bullet2.particleShape.getRadius(), bullet2.particleShape.getRadius());

    PhysVector renderPoint2 = bullet2.toRenderPoint();
    bullet2.position = PhysVector(280, 0);

    bullet2.initialPos = bullet2.position;
    bullet2.particleShape.setPosition(renderPoint2.x, renderPoint2.y);

    
    //BULLET 3
    PhysParticle bullet3;
    bullet3.name = "Bullet 3";
    bullet3.mass = 1.5;
    //PhysVector dir3 = PhysVector(1, 0);
    //bullet3.addForce(dir3 * 50);
    bullet3.velocity = PhysVector(0, 0);

    bullet3.particleShape.setRadius(15.0f);
    bullet3.radius = bullet3.particleShape.getRadius();
    bullet3.particleShape.setFillColor(sf::Color::Green);
    bullet3.particleShape.setOrigin(bullet3.particleShape.getRadius(), bullet3.particleShape.getRadius());

    PhysVector renderPoint3 = bullet3.toRenderPoint();
    bullet3.position = PhysVector(315, 0);

    bullet3.initialPos = bullet3.position;
    bullet3.particleShape.setPosition(renderPoint3.x, renderPoint3.y);

    
    //BULLET 4
    PhysParticle bullet4;
    bullet4.name = "Bullet 4";
    bullet4.mass = 1.5;
    //PhysVector dir3 = PhysVector(1, 0);
    //bullet3.addForce(dir3 * 50);
    bullet4.velocity = PhysVector(0, 0);

    bullet4.particleShape.setRadius(15.0f);
    bullet4.radius = bullet4.particleShape.getRadius();
    bullet4.particleShape.setFillColor(sf::Color::Red);
    bullet4.particleShape.setOrigin(bullet4.particleShape.getRadius(), bullet4.particleShape.getRadius());

    PhysVector renderPoint4 = bullet4.toRenderPoint();
    bullet4.position = PhysVector(350, 0);

    bullet4.initialPos = bullet4.position;
    bullet4.particleShape.setPosition(renderPoint4.x, renderPoint4.y);


    //BULLET 5
    PhysParticle bullet5;
    bullet5.name = "Bullet 5";
    bullet5.mass = 1.5;
    //PhysVector dir3 = PhysVector(1, 0);
    //bullet3.addForce(dir3 * 50);
    bullet5.velocity = PhysVector(0, 0);

    bullet5.particleShape.setRadius(15.0f);
    bullet5.radius = bullet5.particleShape.getRadius();
    bullet5.particleShape.setFillColor(sf::Color::Yellow);
    bullet5.particleShape.setOrigin(bullet5.particleShape.getRadius(), bullet5.particleShape.getRadius());

    PhysVector renderPoint5 = bullet5.toRenderPoint();
    bullet5.position = PhysVector(385, 0);

    bullet5.initialPos = bullet5.position;
    bullet5.particleShape.setPosition(renderPoint5.x, renderPoint5.y);

    //ADD CABLE
    Cable* c = new Cable();
    c->particles[0] = &bullet;
    c->length = 80;
    c->anchorPoint = PhysVector(245, 80);

    //ADDING PARTICLES TO PHYSICS WORLD
    pWorld.addParticle(&bullet);
    pWorld.addParticle(&bullet2);
    pWorld.addParticle(&bullet3);
    pWorld.addParticle(&bullet4);
    pWorld.addParticle(&bullet5);


    //ADDING CABLE TO PHYSICS WORLD
    pWorld.links.push_back(c);


    sf::Clock clock;
    sf::Time timeSinceLast = sf::Time::Zero;

    while (1) {

        timeSinceLast += clock.restart();

        if (timeSinceLast > TimePerFrame) {

            timeSinceLast -= TimePerFrame;


            pWorld.update(TimePerFrame.asMilliseconds() / 1000.0f);

            PhysVector renderPoint1 = bullet.toRenderPoint();
            bullet.particleShape.setPosition(renderPoint1.x, renderPoint1.y);

            PhysVector renderPoint2 = bullet2.toRenderPoint();
            bullet2.particleShape.setPosition(renderPoint2.x, renderPoint2.y);

            PhysVector renderPoint3 = bullet3.toRenderPoint();
            bullet3.particleShape.setPosition(renderPoint3.x, renderPoint3.y);

            PhysVector renderPoint4 = bullet4.toRenderPoint();
            bullet4.particleShape.setPosition(renderPoint4.x, renderPoint4.y);

            PhysVector renderPoint5 = bullet5.toRenderPoint();
            bullet5.particleShape.setPosition(renderPoint5.x, renderPoint5.y);

            //bullet.particleShape.setPosition(bullet.position.x, bullet.position.y);
            //bullet2.particleShape.setPosition(bullet2.position.x, bullet2.position.y);

            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    bullet.velocity = PhysVector(-30, 10);
                    bullet2.velocity = PhysVector(0, 0);
                    bullet3.velocity = PhysVector(0, 0);
                    bullet4.velocity = PhysVector(0, 0);
                    bullet5.velocity = PhysVector(0, 0);
                }
            }

            window.clear();

            if (bullet.getIsDestroyed() != true)
            {
                window.draw(bullet.particleShape);
                window.draw(bullet2.particleShape);
                window.draw(bullet3.particleShape);
                window.draw(bullet4.particleShape);
                window.draw(bullet5.particleShape);
            }

            PhysVector bullet1toSFML = Utils::p6ToSFMLPoint(bullet.position);

            sf::Vertex line1[] = {
                sf::Vertex(sf::Vector2f(c->anchorPoint.x,c->anchorPoint.y)),
                sf::Vertex(sf::Vector2f(bullet1toSFML.x,bullet1toSFML.y))
            };

            if(c->length <= 80)
                window.draw(line1, 2, sf::Lines);
                

            window.display();

            /*
            if (bullet.position.x > bullet.initialPos.x && bullet.position.y >= bullet.initialPos.y)
            {
                break;
            }
            */
           
        }
    }

    utils.displayDistanceTravelled(bullet);


    return 0;
}