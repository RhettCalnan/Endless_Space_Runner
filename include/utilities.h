#ifndef UTILITIES_H
#define UTILITIES_H

// Include necessary SFML libraries for graphics and system modules
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

// Include necessary standard libraries
#include <iostream>
#include <math.h>

// Include custom header files
#include "properties.h"
#include "planet.h"
#include "planetStack.h"
#include "meteor.h"
#include "meteorStack.h"
#include "player.h"

// Function to calculate the square of the length of a Vector2f
float magnitude2(Vector2f u){
    return u.x*u.x + u.y*u.y;
}

// Function to calculate the length of a Vector2f
float magnitude(Vector2f u){
    return sqrt(magnitude2(u));
}

// Function to calculate the unit direction vector pointing from u to v
Vector2f direction(Vector2f u, Vector2f v){
    return (v-u)/magnitude(v-u);
}

// Function to check if a player intersects with a planet. Returns the index of the closest planet if it intersects, else returns -1
int intersects(Object player, PlanetStack planets){

    if (planets.getLength() != 0){
        int minI = 0;
        float minD = magnitude(planets.getArray()[0]->getPos() - player.getPos()) - player.getRadius() - planets.getArray()[0]->getRadius();
        for (int i = 1; i < planets.getLength(); i++){

            if (magnitude(planets.getArray()[i]->getPos() - player.getPos()) - player.getRadius() - planets.getArray()[i]->getRadius() < minD){
                minI = i;
                minD = magnitude(planets.getArray()[i]->getPos() - player.getPos()) - player.getRadius() - planets.getArray()[i]->getRadius();
            }
        }

        if (minD < collisionThresh){
            return minI;
        }
    }
    return -1;

}

// Function to check if a player intersects with a meteor. Returns the index of the closest meteor if it intersects, else returns -1
int intersects(Object player, MeteorStack meteors){

    if (meteors.getLength() != 0){
        int minI = 0;
        float minD = magnitude(meteors.getArray()[0]->getPos() - player.getPos()) - player.getRadius() - meteors.getArray()[0]->getRadius();
        for (int i = 1; i < meteors.getLength(); i++){

            if (magnitude(meteors.getArray()[i]->getPos() - player.getPos()) - player.getRadius() - meteors.getArray()[i]->getRadius() < minD){
                minI = i;
                minD = magnitude(meteors.getArray()[i]->getPos() - player.getPos()) - player.getRadius() - meteors.getArray()[i]->getRadius();
            }
        }

        if (minD < collisionThresh){
            return minI;
        }
    }
    return -1;

}

// Function to calculate the 90 degree counter clockwise rotation of a Vector2f
Vector2f perpendicular(Vector2f u){
    return Vector2f(-u.y,u.x);
}

// Function to calculate the dot product of two Vector2f
float dot(Vector2f u, Vector2f v){
    return u.x*v.x + u.y*v.y;
}

// Function to calculate the component of U in the direction of unit V
Vector2f component(Vector2f u, Vector2f v){
    return dot(u,v)*v/magnitude(v);
}

#endif