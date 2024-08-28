#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "figure.h"
#include "textBox.h"
#include "button.h"

// Using SFML for graphics and std for standard library
using namespace sf;
using namespace std;

class Menu{

    protected:

        // Array of buttons
        Button **array;
        // Current length of the array
        int length;
        // Maximum length of the array
        int maxLength;

    public:

        Menu(){
            maxLength = 10;
            length = 0;
            // Allocating memory for the array
            array = new Button*[maxLength];
        }

        // Function to append a button to the array
        bool Append(Button *button){

            if (length < maxLength){
                array[length] = button;
                length++;
                return true;
            }else{
                cout << "Failed to append button\n"; 
                return false;
            }
        }

        // Function to check if a button in the menu is clicked
        int isClicked(Vector2i MousePos){

            for (int i = 0; i < length; i++){
                if (array[i]->isClicked(MousePos)){
                    return i;
                }
            }
            return -1;
        }

        // Function to draw all the buttons in the menu
        void draw(RenderWindow *window){

            for (int i = 0; i < length; i++){
                array[i]->draw(window);
            }
        }

        // Function to get the array of buttons
        Button **getArray(){
            return array;
        }

        // Function to free the memory allocated to the array
        void freeMemory(){
            
            for (int i = 0; i < length; i++){
                array[i]->~Button();
            }
            delete[] array;
        }

};

#endif