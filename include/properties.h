#ifndef PROPERTIES_H
#define PROPERTIES_H

// Include the SFML library for 2D vector operations
#include <SFML/System/Vector2.hpp>

// Use the sf namespace for simplicity
using namespace sf;

// Define the resolution of the window
const Vector2f res = Vector2f(1280,720);

// Define the resolution of the textures to be 128x128
Vector2f texRes = Vector2f(128,128); 

// Function to center a position on the screen
Vector2f Centered(Vector2f pos){
    // Flip the y-coordinate
    pos.y *= -1;

    // Shift the x and y coordinates to the center of the screen
    pos.x += res.x/2;
    pos.y += res.y/2;

    // Return the centered position
    return pos;
}

// Define physical constants
const float G = 10000; // Gravitational constant
const float E = 2; // Some other constant
const float collisionThresh = 1; // Threshold for collision detection
float Density = 0.05; // Density of the particles

// Define level parameters
const int yPosThresh_Planet = res.y; // Threshold for the y-position of the planet
const int minRadius_Planet = 50; // Minimum radius of the planet
const int radiusThresh_Planet = 100; // Threshold for the radius of the planet
const int minRadius_Meteor = 20; // Minimum radius of the meteor
const int radiusThresh_Meteor = 40; // Threshold for the radius of the meteor
const int vel_Planet = -100; // Velocity of the planet
const Vector2f vel_Meteor = Vector2f(-300,-300); // Velocity of the meteor
const int leftBoundary = -res.x/2 - 2*(radiusThresh_Planet + minRadius_Planet); // Left boundary for the objects
const int spawnInterval_Planet = 300; // Interval for spawning the planet

// Define player parameters
const float jumpPower = 200; // Power of the jump
const float jetpackPower = 10; // Power of the jetpack

// Define render parameters
const int pointCount = 64; // Number of points in the render

#endif