#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <fstream>

// Our files
#include "include/properties.h"
#include "include/figure.h"
#include "include/textBox.h"
#include "include/button.h"
#include "include/menu.h"

#include "include/player.h"
#include "include/planet.h"
#include "include/planetStack.h"
#include "include/meteor.h"
#include "include/meteorStack.h"
#include "include/background.h"

#include "include/physics.h"

using namespace sf;
using namespace std;

int main() {

    // Window
    RenderWindow window(VideoMode(res.x, res.y), "2D Super Mario Galaxy");
    window.setPosition(Vector2i(2560/4,1440/4));
    window.setVerticalSyncEnabled(true);

    // Clear console
    system("clear");

    string line;
    ifstream InScoreFile("score.txt");
    getline(InScoreFile, line);
    int HighScore = stof(line);

    // Variable storing gamestate
    enum GameState { Startup, MainMenu, Playing, Dead, Pause, About, Exit };
    GameState CurrentState = Startup;
    
    // Create the main menu
    Menu Main = Menu();
    // Add buttons to the main menu
    Main.Append(new Button(Vector2f(0,120), Vector2f(500,50),Color::White,"START",Color::Black));
    Main.Append(new Button(Vector2f(0,40), Vector2f(500,50),Color::White,"ABOUT",Color::Black));
    Main.Append(new Button(Vector2f(0,-40), Vector2f(500,50),Color::White,"EXIT",Color::Black));

    // Create the play menu
    Menu PlayMenu = Menu();
    // Add buttons to the play menu
    PlayMenu.Append(new Button(Vector2f(0,340), Vector2f(500,30),Color(0,0,0,0),"High Score: " + to_string(HighScore),Color::White));
    PlayMenu.Append(new Button(Vector2f(-400,-280), Vector2f(500,50),Color(0,0,0,0),"Move: [W][A][S][D]",Color::Blue));
    PlayMenu.Append(new Button(Vector2f(-400,-340), Vector2f(500,50),Color(0,0,0,0),"Jump: [SPACEBAR]",Color::Blue));

    // Create the pause menu
    Menu PauseMenu = Menu();
    // Add buttons to the pause menu
    PauseMenu.Append(new Button(Vector2f(0,40), Vector2f(500,50),Color::Black,"RESUME",Color::White));
    PauseMenu.Append(new Button(Vector2f(0,-40), Vector2f(500,50),Color::Black,"RETURN TO MAIN MENU",Color::White));

    // Create the death menu
    Menu DeathMenu = Menu();
    // Add buttons to the death menu
    DeathMenu.Append(new Button(Vector2f(0,40), Vector2f(500,50),Color::Black,"RETRY",Color::White));
    DeathMenu.Append(new Button(Vector2f(0,-40), Vector2f(500,50),Color::Black,"RETURN TO MAIN MENU",Color::White));
    DeathMenu.Append(new Button(Vector2f(0,160), Vector2f(500,80),Color(0,0,0,0),"YOU DIED",Color::Red));
    DeathMenu.Append(new Button(Vector2f(0,-160), Vector2f(500,40),Color(0,0,0,0),"",Color::Yellow));

    // Create clocks for game and delta time
    Clock gameClock;
    Clock deltaClock;
    Time deltaT;
    int loopCount;
    float gameT;

    // Create a player object
    Player player = Player();

    // Create a planet stack
    PlanetStack planets = PlanetStack();

    // Create a mateor stack
    MeteorStack meteors = MeteorStack();
    
    // Create background objects
    Background mainBG = Background("Textures/Menu.png");
    Background playBG = Background("Textures/Menu.png");
    Background pauseBG = Background(Color(0,0,0,150));
    Background deathBG = Background(Color(115,2,23,255));

    // Run while the window is still alive
    while (window.isOpen())
    {

        Event event;

        window.clear();

        switch (CurrentState)
        { 
        case Startup:
            {
                // Loading screen
                Clock Loading;
                TextBox LoadingText = TextBox(Vector2f(0,0),Vector2f(500,50),Color::Black, "LOADING...",Color::White);
                TextBox Warning = TextBox(Vector2f(0,-res.y/2 + 50),Vector2f(1000,30),Color::Black, "WARNING: Please click the screen a few times to avoid an SFML bug",Color::Red);
                while (Loading.getElapsedTime().asSeconds() < 1){
                    LoadingText.draw(&window);
                    Warning.draw(&window);
                    window.display();
                    
                    while (window.pollEvent(event)){
                        if (event.type == Event::Closed){
                            window.close();
                        }
                    }
                }
                CurrentState = MainMenu;
                break;
            }
        case MainMenu:
            {
                // Event handling for the main menu
                while (window.pollEvent(event)){

                    if (event.type == Event::Closed){
                        CurrentState = Exit;
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Escape)){
                        CurrentState = Exit;
                    }

                    // Menu buttons
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        int ButtonIndex = Main.isClicked(Mouse::getPosition(window));

                        switch (ButtonIndex)
                        {
                        case 0:
                            CurrentState = Playing;

                            // Setup level
                            player.setPos(Vector2f(-0.8*res.x/2,0));
                            player.setVel(Vector2f(100,0));
                            player.setFuelMax();

                            planets.AppendRandom();
                            planets.getArray()[0]->setPos(Vector2f(0,0));
                            planets.getArray()[0]->setRadius(150);
                            planets.AppendRandom();

                            loopCount = 0;
                            gameT = 0;

                            deltaClock.restart();
                            gameClock.restart();
                            break;
                        case 1:
                            CurrentState = About;
                            break;
                        case 2:
                            CurrentState = Exit;
                            break;
                        case -1:
                            break;
                        default:
                            break;
                        }
                    }
                }
                mainBG.draw(&window);
                Main.draw(&window);
                window.display();
                break;
            }  
        case Playing:
            {
                // Event handling for the playing state
                while (window.pollEvent(event)){
                    if (event.type == Event::Closed){
                        CurrentState = Exit;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape)){
                        gameT += gameClock.getElapsedTime().asSeconds();
                        CurrentState = Pause;
                        continue;
                    }
                }

                // Update game state
                if ((loopCount % spawnInterval_Planet) >= spawnInterval_Planet-1){
                    planets.AppendRandom();
                    meteors.AppendRandom();
                }

                deltaT = deltaClock.getElapsedTime();
                deltaClock.restart();

                updatePlanets(planets, deltaT);
                updateMeteors(meteors, deltaT);
                updatePlayer(&player, planets, meteors, deltaT);

                planets.RemoveOutOfBounds();
                meteors.RemoveOutOfBounds();

                // Check if the player is out of bounds
                if (abs(player.getPos().x) > res.x/2+player.getRadius() || abs(player.getPos().y) > res.y/2+player.getRadius()){
                    CurrentState = Dead;
                    gameT += gameClock.getElapsedTime().asSeconds();
                    DeathMenu.getArray()[3]->setText("");
                }

                // Draw game elements
                playBG.draw(&window);
                planets.draw(&window);
                meteors.draw(&window);
                player.draw(&window);
                PlayMenu.draw(&window);
                window.display();

                // Increment the loop count
                loopCount++;

                break;
            }
        case Dead:
            {
                // Event handling for the dead state
                while (window.pollEvent(event)){
                    if (event.type == Event::Closed){
                        CurrentState = Exit;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape)){
                        CurrentState = Exit;
                    }

                    // Menu buttons
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        int ButtonIndex = DeathMenu.isClicked(Mouse::getPosition(window));

                        switch (ButtonIndex)
                        {
                        case 0:
                            CurrentState = Playing;

                            // Setup level
                            while (planets.Remove()){ /*Loop till all planets removed*/ }
                            while (meteors.Remove()){}

                            player.setPos(Vector2f(-0.8*res.x/2,0));
                            player.setVel(Vector2f(100,0));
                            player.setFuelMax();

                            planets.AppendRandom();
                            planets.getArray()[0]->setPos(Vector2f(0,0));
                            planets.getArray()[0]->setRadius(150);
                            planets.AppendRandom();

                            loopCount = 0;
                            gameT = 0;

                            deltaClock.restart();
                            gameClock.restart();
                            break;
                        case 1:
                            CurrentState = Startup;
                            break;
                        case -1:
                            break;
                        default:
                            break;
                        }
                    }
                }

                if (HighScore < 1000*gameT){
                    HighScore = (int)(1000*gameT);
                    DeathMenu.getArray()[3]->setText("NEW HIGH SCORE:\n" + to_string(HighScore));
                    PlayMenu.getArray()[0]->setText("High Score: " + to_string(HighScore));
                }

                // Draw the death background and menu
                deathBG.draw(&window);
                DeathMenu.draw(&window);
                window.display();

                break;
            }
        case Pause:
            {
                // Event handling for the pause state
                while (window.pollEvent(event)){
                    if (event.type == Event::Closed){
                        CurrentState = Exit;
                    }
                    // Menu buttons
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        int ButtonIndex = PauseMenu.isClicked(Mouse::getPosition(window));

                        switch (ButtonIndex)
                        {
                        case 0:
                            CurrentState = Playing;

                            gameClock.restart();
                            deltaClock.restart();
                            break;
                        case 1:
                            CurrentState = Startup;
                            break;
                        case -1:
                            break;
                        default:
                            break;
                        }
                    }
                    
                }

                // Draw the pause elements
                playBG.draw(&window);
                planets.draw(&window);
                player.draw(&window);

                pauseBG.draw(&window);
                PauseMenu.draw(&window);

                window.display();
                break;
            }
        case About:
            {
                // Display the about text
                TextBox AboutText = TextBox(Vector2f(0,0),Vector2f(500,50),Color::Black, 
                    "2D Super Mario Galaxy\nBy:\n  -Rajatha\n  -Rhett\n  -Chris\n\nPress [ESC] to return to main menu",
                    Color::White);
                
                AboutText.draw(&window);
                window.display();
                while (window.pollEvent(event)){

                    if (event.type == Event::Closed){
                        CurrentState = Exit;
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Escape)){
                        CurrentState = MainMenu;
                    }

                }
                break;
            }
        case Exit:
            {
                // Exit the game
                cout << "Thank you for playing! :D\n";
                window.close();
                break;
            }
        default:
            // Handle an invalid game state
            cout << "Something went wrong : Invalid game state\n";
            window.close();
            break;
        }
    }

    // Free the memory used by the menus and the planet stack
    Main.freeMemory();
    PauseMenu.freeMemory();
    planets.freeMemory();
    meteors.freeMemory();
    InScoreFile.close();

    ofstream OutScoreFile("score.txt");
    OutScoreFile << HighScore;
    OutScoreFile.close();
    
    cout << "Highscore: " << HighScore << endl;

    return 0;
}
