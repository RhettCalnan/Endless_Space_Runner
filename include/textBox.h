#ifndef TEXTBOX_H
#define TEXTBOX_H

// Include the necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "figure.h"
#include "properties.h"
#include "math.h"

// Define the path to the font file
#define FONT_PATH "Fonts/PixelifySans-VariableFont_wght.ttf"

// Use the standard and SFML namespaces
using namespace std;
using namespace sf;

// Define the TextBox class which inherits from the Figure class
class TextBox : public Figure{

    // Protected members of the TextBox class
    protected:
        Font font; // Font object
        Text obj; // Text object
        string text; // String to store the text
        Color colText; // Color of the text

    // Public members of the TextBox class
    public:

        // Constructor for the TextBox class
        TextBox(Vector2f Pos, Vector2f Size, Color Col, string Text, Color ColText) : Figure(Pos,Size,Col){
            // Load the font from the file
            font.loadFromFile(FONT_PATH);

            // Assign the text and color to the class members
            text = Text;
            colText = ColText;

            // Set the text, color and font of the Text object
            obj.setString(text);
            obj.setFillColor(colText);
            obj.setFont(font);

            // Set the character size of the Text object
            obj.setCharacterSize(0.9*min(size.x,size.y));

            // Get the global bounds of the Text object
            FloatRect bounds = obj.getGlobalBounds();

            // Set the origin of the Text object
            obj.setOrigin(Vector2f(bounds.width/2,bounds.height));

            // Set the position of the Text object
            obj.setPosition(Centered(pos));
        }

        // Function to draw the TextBox
        void draw(RenderWindow *window){
            // Draw the Figure
            Figure::draw(window);
            // Draw the Text object
            window->draw(obj);
        }

        // Function to set the text of the TextBox
        void setText(string Text){
            // Assign the new text to the class member and the Text object
            text = Text;
            obj.setString(Text);

            // Get the new global bounds of the Text object
            FloatRect bounds = obj.getGlobalBounds();

            // Set the new origin of the Text object
            obj.setOrigin(Vector2f(bounds.width/2,bounds.height));

            // Set the new position of the Text object
            obj.setPosition(Centered(pos));
        }

};

#endif