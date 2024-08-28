#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <math.h>

// Include header files for different components
#include "properties.h"
#include "planet.h"
#include "planetStack.h"
#include "meteor.h"
#include "meteorStack.h"
#include "player.h"
#include "utilities.h"
#include "input.h"

// Use the SFML and std namespaces
using namespace sf;
using namespace std;

// Function to calculate gravity between two objects
// The formula used here is F = GMm/r^2, where G is the gravitational constant
// M is the mass of the objects, r is the distance between the centers of the objects
Vector2f gravity(Object A, Object B){
    Vector2f gravity = G * A.getMass() * B.getMass() * direction(A.getPos(),B.getPos()) / magnitude2(A.getPos()-B.getPos());
    return gravity;
}

// Function to update the positions of all planets based on their velocities
void updatePlanets(PlanetStack planets, Time deltaT){
    float dt = deltaT.asSeconds();
    for (int i = 0; i < planets.getLength(); i++){
        planets.getArray()[i]->setPos(planets.getArray()[i]->getPos() + dt*planets.getArray()[i]->getVel());
    }
}

// Function to update the positions of all meteors based on their velocities
void updateMeteors(MeteorStack meteors, Time deltaT){
    float dt = deltaT.asSeconds();
    for (int i = 0; i < meteors.getLength(); i++){
        meteors.getArray()[i]->setPos(meteors.getArray()[i]->getPos() + dt*meteors.getArray()[i]->getVel());
    }
}

// Function to update the player's position and velocity based on the forces acting on it
void updatePlayer(Player *player, PlanetStack planets, MeteorStack meteors, Time deltaT){
    float dt = deltaT.asSeconds();
    Vector2f acceleration = Vector2f(0,0);

    // Calculate the total gravitational force acting on the player
    for (int i = 0; i < planets.getLength(); i++){
        acceleration += gravity(*player,*planets.getArray()[i]) / player->getMass();
    }

    // If the player intersects with a meteor, bounce off it
    int minI = intersects(*player, meteors);
    Meteor* hit = meteors.getArray()[minI];
    player->airborne = true;
    if (minI != -1){
        Vector2f velY = component(player->getVel(),direction(hit->getPos(),player->getPos()));
        Vector2f velX = player->getVel() - velY;
        player->setVel(Vector2f(velX - E*velY));
        player->setPos(hit->getPos() + (hit->getRadius() + player->getRadius())* direction(hit->getPos(),player->getPos()));
    }

    // If the player intersects with a planet, bounce off it
    minI = intersects(*player, planets);
    Planet* bounceOff = planets.getArray()[minI];
    player->airborne = true;
    Vector2f N;
    if (minI != -1){
        player->airborne = false;

        // Calculate the new velocity and position of the player after bouncing off a planet
        Vector2f velY = component(player->getVel(),direction(bounceOff->getPos(),player->getPos()));
        Vector2f velX = player->getVel() - velY;

        // Update the player's velocity and position
        player->setVel(Vector2f(velX));
        player->setPos(bounceOff->getPos() + (bounceOff->getRadius() + player->getRadius())* direction(bounceOff->getPos(),player->getPos()));
        N = direction(bounceOff->getPos(),player->getPos());
    }

    // Process the player's input
    processInput(player, planets,N);

    // Update the player's velocity and position based on the acceleration
    player->setVel(player->getVel() + acceleration*dt);
    player->setPos(player->getPos() + player->getVel()*dt);

}

#endif