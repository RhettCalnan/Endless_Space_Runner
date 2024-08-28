#ifndef PLANETSTACK_H
#define PLANETSTACK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "time.h"

// Include the necessary files
#include "properties.h"
#include "object.h"
#include "planet.h"

// Use the sf and std namespaces
using namespace sf;
using namespace std;

// Class for managing a stack of planets
class PlanetStack{

    // Pointer to an array of Planet pointers
    Planet **array;
    // Length of the stack
    int length;
    // Maximum length of the stack
    int maxLength;

    public:

        // Constructor for the PlanetStack class
        PlanetStack(){
            // Set the maximum length of the stack to 20
            maxLength = 20;
            // Initialize the length of the stack to 0
            length = 0;
            // Allocate memory for the array
            array = new Planet*[maxLength];

        }

        // Append a planet to the stack
        bool Append(Planet *planet){

            // If the stack is not full
            if (length < maxLength){
                // Add the planet to the stack
                array[length] = planet;
                // Increment the length of the stack
                length++;
                // Return true to indicate success
                return true;
            }else{
                // If the stack is full, print an error message and return false
                cout << "Failed to append planet\n"; 
                return false;
            }
        }

        // Append a random planet to the stack
        bool AppendRandom(){

            // Create a new planet
            Planet* planet = new Planet();

            // Seed the random number generator
            srand(1000*time(NULL));

            // Set the position, radius, and velocity of the planet
            planet->setPos((Vector2f(res.x/2 + radiusThresh_Planet + minRadius_Planet, rand()%(int)(res.y)-res.y/2)));
            planet->setRadius(rand()%radiusThresh_Planet + minRadius_Planet);
            planet->setVel(Vector2f(vel_Planet,0));

            // Add the planet to the stack
            return this->Append(planet);
        }

        // Remove a planet from the stack
        bool Remove(){

            // If the stack is not empty
            if (length > 0){
                // Decrement the length of the stack
                length--;
                // Get the first planet in the stack
                Planet* temp = array[0];
                // Destroy the planet object
                temp->~Planet();
                // Shift the remaining planets in the stack
                for (int i = 0; i < length; i++){
                    array[i] = array[i+1];
                }
                // Return true to indicate success
                return 1;
            }else{
                // If the stack is empty, return false
                return 0;
            }
        }

        // Remove planets that are out of bounds
        void RemoveOutOfBounds(){

            // Loop over the planets in the stack
            for (int i = 0; i < length; i++){
                // If a planet is out of bounds, remove it
                if (array[i]->getPos().x < leftBoundary){
                    this->Remove();
                    break;
                }
            }
        }

        // Get the array of planets
        Planet** getArray(){
            return array;
        }
        // Get the length of the stack
        int getLength(){
            return length;
        }
        // Get the maximum length of the stack
        int getMaxLength(){
            return maxLength;
        }

        // Draw the planets in the stack
        void draw(RenderWindow *window){

            // Loop over the planets in the stack
            for (int i = 0; i < length; i++){
                // Draw each planet
                array[i]->draw(window);
            }
        }

        // Free the memory used by the stack
        void freeMemory(){
            // Loop over the planets in the stack
            for (int i = 0; i < length; i++){
                // Call the destructor of each planet
                array[i]->~Planet();
            }
            // Delete the array
            delete[] array; 
            // The line "delete[] array;" deallocates the memory that was previously allocated to the array using the "new" operator. 
            // It's important to note that this doesn't delete the objects that the array was pointing to. 
            // It only deallocates the memory that was used to store the pointers in the array. 
            // Therefore, we need to call the destructor of each planet object before deleting the array.
        }
};

#endif