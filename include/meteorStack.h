#ifndef METEORSTACK_H
#define METEORSTACK_H

// Include necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "time.h"

// Include custom files
#include "properties.h"
#include "object.h"
#include "meteor.h"

// Use the namespaces for convenience
using namespace sf;
using namespace std;

// Define the MeteorStack class
class MeteorStack{

    // Declare private member variables
    Meteor **array;
    int length;
    int maxLength;

    public:

        // Default constructor
        MeteorStack(){
            // Initialize member variables
            maxLength = 20;
            length = 0;
            // Dynamically allocate memory for the array
            array = new Meteor*[maxLength];
        }

        // Method to append a meteor to the stack
        bool Append(Meteor *meteor){
            // If the stack is not full, append the meteor and return true
            if (length < maxLength){
                array[length] = meteor;
                length++;
                return true;
            }
            // If the stack is full, print an error message and return false
            else{
                cout << "Failed to append meteor\n"; 
                return false;
            }
        }

        // Method to append a random meteor
        bool AppendRandom(){
            // Create a new meteor
            Meteor* meteor = new Meteor();

            // Randomly initialize the meteor's properties
            srand(1000*time(NULL));
            int fac = -1;
            if (rand()%10 >= 5){
                fac = 1;
            }

            meteor->setPos(Vector2f(res.x/2 - rand()%(int)(res.x/5), fac*(res.y/2+50)));
            meteor->setRadius(rand()%radiusThresh_Meteor + minRadius_Meteor);
            meteor->setVel(Vector2f(vel_Meteor.x,vel_Meteor.y*fac));

            // Append the meteor to the stack and return the result
            return this->Append(meteor);
        }

        // Method to remove a meteor from the stack
        bool Remove(){
            // If the stack is not empty, remove the meteor and return true
            if (length > 0){
                length--;
                Meteor* temp = array[0];
                temp->~Meteor();
                for (int i = 0; i < length; i++){
                    array[i] = array[i+1];
                }
                return 1;
            }
            // If the stack is empty, return false
            else{
                return 0;
            }
        }

        // Method to remove out-of-bounds meteors
        void RemoveOutOfBounds(){
            for (int i = 0; i < length; i++){
                if (array[i]->getPos().x < leftBoundary){
                    this->Remove();
                    break;
                }
            }
        }

        // Getter methods for the array, length, and maxLength
        Meteor** getArray(){
            return array;
        }
        int getLength(){
            return length;
        }
        int getMaxLength(){
            return maxLength;
        }

        // Method to draw all meteors in the stack
        void draw(RenderWindow *window){
            for (int i = 0; i < length; i++){
                array[i]->draw(window);
            }
        }

        // Method to free memory allocated for the array and its elements
        void freeMemory(){
            for (int i = 0; i < length; i++){
                array[i]->~Meteor(); // Calls the destructor of the Meteor object
            }
            // Delete the dynamically allocated array
            delete[] array; // This line deletes the array and frees the memory it was using
        }
};

#endif