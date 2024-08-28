#ifndef METEOR_H
#define METEOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Include custom files
#include "properties.h"
#include "object.h"

// Use the sf and std namespaces
using namespace sf;
using namespace std;

// Definition of the Meteor class
class Meteor : public Object{

    public:

        // Default constructor for the Meteor class
        Meteor() : Object(){
            // Set the texture for the meteor object
            this->getFigure()->setTexture("Textures/Meteor_1.png");
            // Set the texture rectangle for the meteor object
            this->getFigure()->TextureRect(4,4,8,8);
        }

        // Parameterized constructor for the Meteor class
        Meteor(float Radius, Vector2f Pos, Vector2f Vel, Vector2f Acc, string Path) : Object(Radius, 0, Pos, Vel, Acc, Path){
            // Set the texture for the meteor object
            this->getFigure()->setTexture("Textures/Meteor_1.png");
            // Set the texture rectangle for the meteor object
            this->getFigure()->TextureRect(4,4,8,8);
        }

};

#endif