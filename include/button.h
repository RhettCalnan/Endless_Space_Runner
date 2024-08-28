#ifndef BUTTON_H
#define BUTTON_H

// Including necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "figure.h"
#include "textBox.h"
#include "properties.h"

// Using standard and SFML namespaces
using namespace std;
using namespace sf;

// Button class definition, inheriting from TextBox
class Button : public TextBox{

    // Protected members of the Button class
    protected:

    // Public members of the Button class
    public:

        // Button constructor, initializing inherited TextBox with given parameters
        Button(Vector2f Pos, Vector2f Size, Color Col, string Text, Color ColText) : TextBox(Pos,Size,Col,Text,ColText){

        }

        // Function to check whether the button is clicked or not
        bool isClicked(Vector2i MousePos){

            // Getting the global bounds of the button
            FloatRect bounds = this->box.getGlobalBounds();

            // Checking if the mouse position is within the button's bounds
            if (MousePos.x >= bounds.left &&
                MousePos.x <= bounds.left + bounds.width &&
                MousePos.y >= bounds.top &&
                MousePos.y <= bounds.top + bounds.height){
                    return true; // If mouse is within bounds, return true
                }
            // If mouse is not within bounds, return false
            return false;

        }

};

#endif