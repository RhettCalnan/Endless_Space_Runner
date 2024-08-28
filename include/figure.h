#ifndef FIGURE_H
#define FIGURE_H

// Include necessary libraries.
#include <SFML/Graphics.hpp>
#include <iostream>
#include "properties.h"

// Use the standard namespace and SFML graphics namespace.
using namespace std;
using namespace sf;

// Class definition for Figure.
class Figure {

    // Protected members.
    protected:
        // SFML RectangleShape object.
        RectangleShape box;
        // Position of the figure.
        Vector2f pos;
        // Size of the figure.
        Vector2f size;
        // Texture of the figure.
        Texture tex;
        // Color of the figure.
        Color col;

    // Public members.
    public:

        // Default constructor.
        Figure(){
            // Set initial position, size, and color.
            pos = Vector2f(0,0);
            size = Vector2f(100,100);
            col = Color::Magenta;

            // Set the box properties.
            box.setSize(size);
            box.setOrigin(size.x/2,size.y/2);
            box.setPosition(Centered(pos));
            box.setFillColor(col);
        }

        // Constructor for no Texture.
        Figure(Vector2f Pos, Vector2f Size, Color Col){
            // Set position, size, and color.
            pos = Pos;
            size = Size;
            col = Col;

            // Set the box properties.
            box.setSize(size);
            box.setOrigin(size.x/2,size.y/2);
            box.setPosition(Centered(pos));
            box.setFillColor(col);
        }

        // Constructor with Texture.
        Figure(Vector2f Pos, Vector2f Size, string Path){
            // Set position and size.
            pos = Pos;
            size = Size;

            // Set the box properties.
            box.setSize(size);
            box.setOrigin(size.x/2,size.y/2);
            box.setPosition(Centered(pos));

            // Load texture from file and set box texture.
            tex.loadFromFile(Path);
            tex.setSmooth(false);
            box.setTexture(&tex);
        }

        // Method to draw the figure to the screen.
        void draw(RenderWindow *window){
            // Draw the box to the window.
            window->draw(box);
        }

        // Getter for position.
        Vector2f getPos(){
            return pos;
        }

        // Setter for position.
        void setPos(Vector2f Pos){
            pos = Pos;
            box.setPosition(Centered(pos));
        }

        // Getter for size.
        Vector2f getSize(){
            return size;
        }

        // Setter for size.
        void setSize(Vector2f Size){
            box.scale(Vector2f(Size.x/size.x,Size.y/size.y));
            size = Size;
        }

        // Method to scale the figure.
        void scale(float Scale){
            box.scale(Scale,Scale);
            size = Scale * size;
        }

        // Method to set the texture of the figure.
        void setTexture(string Path){
            tex.loadFromFile(Path);
            tex.setSmooth(false);
            box.setTexture(&tex);
        }

        // Method to set the color of the figure.
        void setColor(Color Col){
            col = Col;
            box.setFillColor(col);
        }

        // Getter for the box.
        RectangleShape *getBox(){
            return &box;
        }

        // Method to alter the part of the texture being used
        // (x,y) is the top left corner
        // (w,h) is the dimensions of the area
        void TextureRect(int x, int y, int w, int h){
            box.setTextureRect(IntRect(x,y,w,h));
        }

};

#endif