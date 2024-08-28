#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

// Include custom properties header file
#include "properties.h"
#include "figure.h"

// Use SFML and standard library namespaces
using namespace sf;
using namespace std;

// Define Object class
class Object{

    private:
        // Data members
        float mass;       // Mass of the object
        float radius;     // Radius of the object
        Vector2f pos;     // Position of the object
        Vector2f vel;     // Velocity of the object
        Vector2f acc;     // Acceleration of the object
        Figure appearance; // Appearance of the object

    protected:
        // Default constructor
        Object() {

            // Initialize data members
            mass = 0;
            radius = 100;
            pos = Vector2f(0,0);
            vel = Vector2f(0,0);
            acc = Vector2f(0,0);

            // Create a new Figure object and assign it to appearance
            appearance =  *(new Figure(pos,2.0f*Vector2f(radius,radius),"Textures/UVgrid.png"));
        }

        // Parameterized constructor
        Object(float Radius, float Mass, Vector2f Pos, Vector2f Vel, Vector2f Acc, string Path){
            // Initialize data members with the given parameters
            mass = Mass;
            radius = Radius;
            pos = Pos;
            vel = Vel;
            acc = Acc;

            // Create a new Figure object with the given parameters and assign it to appearance
            appearance = *(new Figure(pos,2.0f*Vector2f(radius,radius),Path));
        }
    
    public:    
        // Getter and setter methods for data members
        float getMass(){ return mass; }
        void setMass(float Mass){ mass = Mass; }

        float getRadius(){ return radius; }
        void setRadius(float Radius){
            // Scale the appearance based on the new radius
            appearance.scale(Radius/radius);
            // Set the new radius
            radius = Radius;         
        }

        Vector2f getPos(){ return pos; }
        void setPos(Vector2f Pos){
            // Set the new position
            pos = Pos;
            // Update the position of the appearance
            appearance.setPos(pos);
        }

        Vector2f getVel(){ return vel; }
        void setVel(Vector2f Vel){ vel = Vel; }

        Vector2f getAcc(){ return acc; }
        void setAcc(Vector2f Acc){ acc = Acc; }

        Figure *getFigure(){
            // Return a pointer to the appearance object
            return &appearance;
        }

        // Method to draw the object on a given window
        void draw(RenderWindow *window){
            // Draw the appearance object on the window
            this->appearance.draw(window);
        }
};

#endif