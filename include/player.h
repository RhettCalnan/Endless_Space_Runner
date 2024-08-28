#ifndef PLAYER_H
#define PLAYER_H

// Include necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"

// Include custom header files
#include "properties.h"
#include "object.h"
#include "figure.h"

// Use the namespaces
using namespace sf;
using namespace std;

// Define the Player class
class Player : public Object{

    // Define private variables
    float fuel;
    Figure fuelBar;
    
    public:
        bool airborne;

        // Constructor for the Player class
        Player() : Object(){
            // Set initial properties of the Player object
            this->setRadius(20);
            this->getFigure()->setTexture("Textures/Player.png");
            this->getFigure()->TextureRect(4,4,8,8);
            this->setMass(10);
            this->setPos(Vector2f(0,0));
            this->setVel(Vector2f(0,0));
            this->setAcc(Vector2f(0,0));

            // Initialize fuel and fuelBar
            fuel = 100;
            fuelBar = Figure(Vector2f(30,0),Vector2f(5,40),Color::Green);
            airborne = false;
        }

        // Function to draw the Player and fuelBar on the window
        void draw(RenderWindow *window){
            Object::draw(window);
            fuelBar.draw(window);
        }

        // Function to get the current fuel level
        float getFuel() {return fuel;}

        // Function to increase fuel by 1
        void setFuelPlus() {
            fuel = fuel + 1;
            fuel = min(100.0f,fuel);
            fuelBar.setSize(fuelBar.getSize()+Vector2f(0,40.0f/100.0f));
            if (fuel == 100){
                fuelBar.setSize(Vector2f(5,40));
            }
        }

        // Function to decrease fuel by 1
        void setFuelMinus() {
            fuel = fuel - 1;
            fuel = max(0.0f, fuel);
            fuelBar.setSize(fuelBar.getSize()-Vector2f(0,40.0f/100.0f));
            if (fuel == 100){
                fuelBar.setSize(Vector2f(5,40));
            }
        }

        // Function to set fuel to maximum
        void setFuelMax() {
            fuel = 100;
            fuelBar.setSize(Vector2f(5,40));
        }

        // Function to set the position of the Player object
        void setPos(Vector2f Pos){
            Object::setPos(Pos);
            fuelBar.setPos(Pos + Vector2f(30,0));
        }

};

#endif