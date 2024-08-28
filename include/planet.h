#ifndef PLANET_H
#define PLANET_H

// Include necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>

// Include custom header files
#include "properties.h"
#include "object.h"

// Use namespaces for convenience
using namespace sf;
using namespace std;

// Define the Planet class that inherits from the Object class
class Planet : public Object{

    public:

        // Default constructor for the Planet class
        Planet() : Object(){
            // Set the mass based on the radius
            this->setMass(Density*this->getRadius()*this->getRadius());
            // Set the texture of the planet
            this->getFigure()->setTexture("Textures/Planet_1.png");
            // Set the texture rectangle of the planet
            this->getFigure()->TextureRect(8,8,16,16);
        }

        // Constructor for the Planet class with additional parameters
        Planet(float Radius, Vector2f Pos, Vector2f Vel, Vector2f Acc, string Path) : Object(Radius, 0, Pos, Vel, Acc, Path){
            // Set the mass based on the radius
            this->setMass(Density*Radius*Radius);
            // Set the texture of the planet
            this->getFigure()->setTexture("Textures/Planet_1.png");
            // Set the texture rectangle of the planet
            this->getFigure()->TextureRect(8,8,16,16);
        }

        // Function to set the radius and mass of the planet
        // The radius automatically determines the mass
        void setRadius(float Radius){
            // Call the base class function to set the radius
            Object::setRadius(Radius);
            // Set the mass based on the radius
            this->setMass(Density*Radius*Radius);
            // If the radius is less than half of the threshold and minimum radius, set a different texture
            if (Radius < 0.5*(radiusThresh_Planet+minRadius_Planet)){
                this->getFigure()->setTexture("Textures/Planet_2.png");
                this->getFigure()->TextureRect(4,4,8,8);
            }else{
                // Otherwise, set the texture as Planet_1
                this->getFigure()->setTexture("Textures/Planet_1.png");
                this->getFigure()->TextureRect(8,8,16,16);
            }
        }

};

#endif