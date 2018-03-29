#ifndef MENU_H
#define MENU_H

#include <SDL.h>

enum MENU_MESSAGE{
    MENU_NONE = 1,
    MENU_QUIT = 2,
    MENU_RETURN = 3
};

// This class is a basic class for all the menus
class Menu{
public:

    virtual bool loadMedia()=0;

    virtual MENU_MESSAGE accept()=0;

    virtual void show()=0;

    virtual void destroy()=0;

    virtual void render()=0;

};

#endif // MENU_H
