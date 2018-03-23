#include "../include/controlsystem.h"

ControlSystem* ControlSystem::g_controlSystem = NULL;

ControlSystem* ControlSystem::getInstance() {

    if (!g_controlSystem)
        g_controlSystem = new ControlSystem();

    return g_controlSystem;
}

ControlSystem::ControlSystem():playerInputs({new Vector2D(0.0f, 0.0f),
                                            new Vector2D(0.0f, 0.0f)}),
    isFireInputs({false, false})
{
    // initialization.
}

ControlSystem::~ControlSystem(){

}

Vector2D* ControlSystem::getInputs (int playerId) {
    if (playerId < playerInputs.size())
        return playerInputs[playerId];
    else
        return new Vector2D(0.0f, 0.0f);
}

bool ControlSystem::getIsFireInput(int playerId){
    if (playerId < isFireInputs.size())
        return isFireInputs[playerId];
    else
        return false;
}

void ControlSystem::setIsFireInput(int playerId){
    if (playerId < isFireInputs.size())
        isFireInputs[playerId] = false;
    else
        return;
}

void ControlSystem::setInput(int pid, Vector2D* v) {
    playerInputs[pid] = v;
}
bool ControlSystem::init(){
    // Now do nothing
    bool success = true;
    return success;
}

bool ControlSystem::quit(){
    // Now do nothing
    bool success = true;
    return success;
}

void ControlSystem::update(){
    // Do Nothing
}

void ControlSystem::update (SDL_Event e) {

    for (int i = 0; i < GameSetting::getInstance()->getPlayerNum(); ++i) {

        if (playerInputs.size() < i)
            playerInputs.push_back(new Vector2D(0.0f, 0.0f));

        if (isFireInputs.size() < i)
            isFireInputs.push_back(false);

        switch (GameSetting::CurrentPlayerControlSchemes[i]) {
            case GameSetting::ControlSchemes::WASD:
                if (e.type == SDL_KEYDOWN)    {
                    playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_d?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_a?1.0f:0.0f),
                                                   (e.key.keysym.sym==SDLK_s?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_w?1.0f:0.0f));
                    Vector2D* v = getInputs(0);
                    //if (e.key.keysym.sym==SDLK_w) cout<<"^^^^^^^^^^ !input w: "+to_string((*v)[0])+", "+to_string((*v)[1])<<endl;

                    isFireInputs[i] = (e.key.keysym.sym == SDLK_f? true:false);
                }
                else{
                    isFireInputs[i] = false;
                    playerInputs[i] = new Vector2D(0.0f, 0.0f);
                }

                break;
            case GameSetting::ControlSchemes::IJKL:
                if (e.type == SDL_KEYDOWN){
                    playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_l?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_j?1.0f:0.0f),
                                                   (e.key.keysym.sym==SDLK_i?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_k?1.0f:0.0f));
                    isFireInputs[i] = (e.key.keysym.sym == SDLK_h)? true : false;
                }
                else{
                    isFireInputs[i] = false;
                    playerInputs[i] = new Vector2D(0.0f, 0.0f);
                }

                break;
            case GameSetting::ControlSchemes::ArrowKeys:
                if (e.type == SDL_KEYDOWN){
                    playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_RIGHT?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_LEFT?1.0f:0.0f),
                                                   (e.key.keysym.sym==SDLK_UP?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_DOWN?1.0f:0.0f));
                    isFireInputs[i] = (e.key.keysym.sym == SDLK_SPACE)? true : false;
                }
                else{
                    isFireInputs[i] = false;
                    playerInputs[i] = new Vector2D(0.0f, 0.0f);
                }
                break;
            default:{
                isFireInputs[i] = false;
                playerInputs[i] = new Vector2D(0.0f, 0.0f);
            }
        }
    }
}
