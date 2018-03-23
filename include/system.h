#ifndef SYSTEM_H
#define SYSTEM_H


/**
 * @brief This class defines the base class for all systems used in the game.
 */
class System{
public:
    /**
     * @brief Initialization
     */
    virtual bool init()=0;
    /**
     * @brief Quit
     */
    virtual bool quit()=0;
    /**
     * @brief Update
     */
    virtual void update()=0;
};


#endif // SYSTEM_H
