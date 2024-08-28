#ifndef BACKGROUND_H
#define BACKGROUND_H

// Include necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>

// Include custom header files
#include "properties.h"
#include "object.h"

// Use the sf and std namespaces
using namespace sf;
using namespace std;

// Define the Background class that inherits from Figure
class Background : public Figure{

    public:

        // Constructor that takes a file path as an argument
        Background(string Path) : Figure(Vector2f(0,0),res,Path){}

        // Constructor that takes a color as an argument
        Background(Color col) : Figure(Vector2f(0,0),res,col){}

        // Method to draw the background on a window
        void draw(RenderWindow *window){
            // Call the draw method of the Figure class
            Figure::draw(window);
        }
};

#endif