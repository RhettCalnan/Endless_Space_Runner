#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <math.h>

// Custom files
#include "properties.h"
#include "planet.h"
#include "player.h"
#include "utilities.h"

// Namespace declarations
using namespace sf;
using namespace std;

// Function to process player's input
// Takes a pointer to a Player object, a PlanetStack object, and a Vector2f object as parameters
void processInput(Player *player, PlanetStack planets, Vector2f N){

    // If the player is not airborne
    if (!player->airborne){

        // If the space key is pressed, increase the player's velocity
        if (Keyboard::isKeyPressed(Keyboard::Space)){        
            player->setVel(player->getVel() + jumpPower*N);         
        }
        // Increase the player's fuel
        player->setFuelPlus();

    }else{
        
        // If the player has fuel
        if (player->getFuel()){
            // If the W key is pressed, decrease the player's velocity in the y-direction
            if (Keyboard::isKeyPressed(Keyboard::W)){
                player->setVel(player->getVel() - jetpackPower*Vector2f(0,-1));
                // Decrease the player's fuel
                player->setFuelMinus();
            }

            // If the S key is pressed, increase the player's velocity in the y-direction
            if (Keyboard::isKeyPressed(Keyboard::S)){
                player->setVel(player->getVel() - jetpackPower*Vector2f(0,1));
                // Decrease the player's fuel
                player->setFuelMinus();
            }

            // If the A key is pressed, decrease the player's velocity in the x-direction
            if (Keyboard::isKeyPressed(Keyboard::A)){
                player->setVel(player->getVel() - jetpackPower*Vector2f(1,0));
                // Decrease the player's fuel
                player->setFuelMinus();
            }

            // If the D key is pressed, increase the player's velocity in the x-direction
            if (Keyboard::isKeyPressed(Keyboard::D)){
                player->setVel(player->getVel() - jetpackPower*Vector2f(-1,0));
                // Decrease the player's fuel
                player->setFuelMinus();
            }
            
        }   
    }

}

#endif