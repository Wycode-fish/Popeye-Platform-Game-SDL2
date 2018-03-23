#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H


#include <SDL.h>
#include <vector>
#include <iostream>
#include "vector2d.h"
#include <map>
#include <string>
#include <stddef.h>
#include "gamesetting.h"
#include "system.h"

using namespace std;
/**
 * @brief This class defines Control System
 *
 * Applied Singleton Design Pattern
 */
class ControlSystem: public System{
public:
    /**
     * @brief Get the only instance
     */
    static ControlSystem* getInstance();
    /**
     * @brief Destructor
     */
    ~ControlSystem();
    /**
     * @brief Initialization
     */
    bool init();
    /**
     * @brief Get the player inputs
     *
     * @param playerId An integer represents the designated player
     */
    Vector2D* getInputs(int playerId);
    /**
     * @brief Capture the player input at every frame
     *
     * @param e Keyboard event
     */

    bool getIsFireInput(int playerId);
    void setIsFireInput(int playerId);
    void update(SDL_Event e);
    /**
     * @brief Update
     */
    void update();
    /**
     * @brief Quit
     */
    bool quit();

public:
    void setInput(int pid, Vector2D* v);

private:
    /**
     * @brief private constructor
     */
    ControlSystem();
    /**
     * @brief the only instance
     */
    static ControlSystem* g_controlSystem;
    /**
     * @brief playerInputs
     */
    vector<Vector2D*> playerInputs;

    // the bullet status input
    vector<bool> isFireInputs;
};

#endif // CONTROLSYSTEM_H
