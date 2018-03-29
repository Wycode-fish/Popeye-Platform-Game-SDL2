#include "../include/controlsystem.h"

ControlSystem* ControlSystem::g_controlSystem = NULL;

ControlSystem* ControlSystem::getInstance() {

    if (!g_controlSystem)
        g_controlSystem = new ControlSystem();

    return g_controlSystem;
}


ControlSystem::ControlSystem(): isFireInputs({false, false}), inputFactors(Vector2D(1.0f, 1.0f))
{
    // initialization.
    cout<<"ControlSystem initializing..."<<endl;
    vector<Vector2D*>* p1 = new vector<Vector2D*>(2);
    (*p1)[0] = new Vector2D(0.0f, 0.0f);
    (*p1)[1] = new Vector2D(0.0f,0.0f);
    // p1->push_back(new Vector2D(0.0f, 0.0f));
    // p1->push_back(new Vector2D(0.0f, 0.0f));
    cout<<"- temp input constructing..."<<endl;
    playerInputs.push_back(p1);
    cout<<"- temp input injecting..."<<endl;
}

ControlSystem::~ControlSystem(){

}

vector<Vector2D*>* ControlSystem::getInputs (int playerId) {

    if (playerId < playerInputs.size()){

        // cout<<"testing:"+to_string(playerInputs[playerId]->size())<<endl;
        //cout<<"testing:"+to_string((*input2)[0])+", "+to_string((*input2)[1])<<endl;
        return playerInputs[playerId];
    }

    else {

        cout<<"testing..." <<endl;
        vector<Vector2D*>* temp = new vector<Vector2D*>(2);
        (*temp)[0] =  new Vector2D(0.0f, 0.0f);
        (*temp)[1] = new Vector2D(0.0f, 0.0f);
        return temp;
    }

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
    //playerInputs[pid] = v;
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


Vector2D* ControlSystem::translateInput(int  pid) {


    vector<Vector2D*>* input = getInputs( pid );


    Vector2D* input1 = (*input)[0];

    // cout<<"input1:"+to_string((*input1)[0])+", "+to_string((*input1)[1])<<endl;

    Vector2D* input2 = (*input)[1];

    //cout<<"input1:"+to_string((*input2)[0])+", "+to_string((*input2)[1])<<endl;

    bool hasUp = (*input1)[1]<0 || (*input2)[1]<0;
    bool hasDown = (*input1)[1]>0 || (*input2)[1]>0;
    bool hasRight = (*input1)[0]>0 || (*input2)[0]>0;
    bool hasLeft = (*input1)[0]<0 || (*input2)[0]<0;

    if (hasUp && hasLeft) {
        return new Vector2D(-1.0f, -1.0f);
    }
    else if (hasDown && hasLeft) {
        return new Vector2D(-1.0f, 1.0f);
    }
    if (hasUp && hasRight) {
        return new Vector2D(1.0f, -1.0f);
    }
    else if (hasDown && hasRight) {
        return new Vector2D(1.0f, 1.0f);
    }
    else if(hasUp) {
        return new Vector2D(0.0f, -1.0f);
    }
    else if(hasDown) {
        return new Vector2D(0.0f, 1.0f);
    }
    else if(hasLeft) {
        return new Vector2D(-1.0f, 0.0f);
    }
    else if(hasRight) {
        return new Vector2D(1.0f, 0.0f);
    }
    else {
        return new Vector2D(0.0f, 0.0f);
    }

}

void ControlSystem::reset() {

    for (int i=0; i<GameSetting::getInstance()->getPlayerNum(); ++i) {

        playerInputs[i]->pop_back();
        playerInputs[i]->pop_back();
        playerInputs[i]->push_back(new Vector2D(0.0f,0.0f));
        playerInputs[i]->push_back(new Vector2D(0.0f,0.0f));
    }
}

void ControlSystem::update (SDL_Event e) {

    for (int i = 0; i < GameSetting::getInstance()->getPlayerNum(); ++i) {

        if (playerInputs.size() < i) {

            vector<Vector2D*> tempPlayerInput(2, new Vector2D(0.0f,0.0f));

            playerInputs.push_back(&tempPlayerInput);
        }

        if (isFireInputs.size() < i)
            isFireInputs.push_back(false);

        switch (GameSetting::CurrentPlayerControlSchemes[i]) {

            case GameSetting::ControlSchemes::WASD:
                if (e.type == SDL_KEYDOWN)    {

                    cout<<"key down. detected."<<endl;
                    if (e.key.keysym.sym == SDLK_w){
//                        SoundSystem::getInstance()->playJumpSound();
                        cout<<"w detected"<<endl;
                    }

                    Vector2D* newInput = new Vector2D((e.key.keysym.sym==SDLK_d?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_a?1.0f:0.0f),
                                                   (e.key.keysym.sym==SDLK_s?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_w?1.0f:0.0f));
                    if (playerInputs[CONTROL_WASD]->size()<2) {
                        // playerInputs[CONTROL_WASD]->pop_back();
                        playerInputs[CONTROL_WASD]->push_back(newInput);
                    }
                    else if (playerInputs[CONTROL_WASD]->size()==2) {

                        if ((*(playerInputs[CONTROL_WASD]->front()))==Vector2D(0.0f,0.0f))
                            (*playerInputs[CONTROL_WASD])[0] = newInput;
                        else if ((*(playerInputs[CONTROL_WASD]->back()))==Vector2D(0.0f,0.0f))
                            (*playerInputs[CONTROL_WASD])[1] = newInput;
                        //playerInputs[CONTROL_WASD]->push_back(newInput);
                    }
                    while (playerInputs[CONTROL_WASD]->size()<2) {

                        playerInputs[CONTROL_WASD]->push_back(new Vector2D(0.0f,0.0f));
                    }
                    // playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_d?1.0f:0.0f)-
                    //                                (e.key.keysym.sym==SDLK_a?1.0f:0.0f),
                    //                                (e.key.keysym.sym==SDLK_s?1.0f:0.0f)-
                    //                                (e.key.keysym.sym==SDLK_w?1.0f:0.0f));

                    isFireInputs[i] = (e.key.keysym.sym == SDLK_f? true:false);
                }
                else if (e.type == SDL_KEYUP) {

                    // if (e.key.keysym.sym==SDLK_d) cout<<"*******: in key up: d"<<endl;
                    // else if (e.key.keysym.sym==SDLK_a) cout<<"*******: in key up: a"<<endl;
                    // else if (e.key.keysym.sym==SDLK_w) cout<<"*******: in key up: w"<<endl;
                    // else if (e.key.keysym.sym==SDLK_s) cout<<"*******: in key up: s"<<endl;
                    // else cout<<"*******: in key up: else"<<endl;

                    Vector2D* newInput = new Vector2D((e.key.keysym.sym==SDLK_d?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_a?1.0f:0.0f),
                                                   (e.key.keysym.sym==SDLK_s?1.0f:0.0f)-
                                                   (e.key.keysym.sym==SDLK_w?1.0f:0.0f));

                    Vector2D* input1 = (*playerInputs[CONTROL_WASD])[0];

                    Vector2D* input2 = (*playerInputs[CONTROL_WASD])[1];

                    if ((*newInput)==(*input1) && (*newInput)==(*input2)) {

                        playerInputs[i]->pop_back();
                        playerInputs[i]->pop_back();
                        playerInputs[i]->push_back(new Vector2D(0.0f,0.0f));
                        playerInputs[i]->push_back(new Vector2D(0.0f,0.0f));
                    }

                    else if ((*newInput)==(*input1)) {


                        playerInputs[CONTROL_WASD]->erase(playerInputs[CONTROL_WASD]->begin());

                        playerInputs[CONTROL_WASD]->push_back(new Vector2D(0.0f,0.0f));
                    }
                    else if ((*newInput)==(*input2)){


                        playerInputs[CONTROL_WASD]->pop_back();

                        playerInputs[CONTROL_WASD]->push_back(new Vector2D(0.0f,0.0f));
                    }
                    else {

                        reset();
                    }

                    isFireInputs[i] = (e.key.keysym.sym == SDLK_f? true:false);

                }
                else{
                    isFireInputs[i] = false;

                    //cout<<"*******: in key up: ??????"+to_string(e.type)<<endl;

                    while (playerInputs[CONTROL_WASD]->size()<2) {


                        playerInputs[CONTROL_WASD]->push_back(new Vector2D(0.0f,0.0f));
                    }
                }

                break;



            case GameSetting::ControlSchemes::IJKL:
                // if (e.type == SDL_KEYDOWN){
                //     playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_l?1.0f:0.0f)-
                //                                    (e.key.keysym.sym==SDLK_j?1.0f:0.0f),
                //                                    (e.key.keysym.sym==SDLK_i?1.0f:0.0f)-
                //                                    (e.key.keysym.sym==SDLK_k?1.0f:0.0f));
                //     isFireInputs[i] = (e.key.keysym.sym == SDLK_h)? true : false;
                // }
                // else{
                //     isFireInputs[i] = false;
                //     playerInputs[i] = new Vector2D(0.0f, 0.0f);
                // }

                break;



            case GameSetting::ControlSchemes::ArrowKeys:
                // if (e.type == SDL_KEYDOWN){
                //     playerInputs[i] = new Vector2D((e.key.keysym.sym==SDLK_RIGHT?1.0f:0.0f)-
                //                                    (e.key.keysym.sym==SDLK_LEFT?1.0f:0.0f),
                //                                    (e.key.keysym.sym==SDLK_UP?1.0f:0.0f)-
                //                                    (e.key.keysym.sym==SDLK_DOWN?1.0f:0.0f));
                //     isFireInputs[i] = (e.key.keysym.sym == SDLK_SPACE)? true : false;
                // }
                // else{
                //     isFireInputs[i] = false;
                //     playerInputs[i] = new Vector2D(0.0f, 0.0f);
                // }
                break;



            default:{
                // isFireInputs[i] = false;
                // playerInputs[i] = new Vector2D(0.0f, 0.0f);
            }
        }
    }
}

void ControlSystem::setInputFactors( Vector2D inputFactors ){
    this->inputFactors = inputFactors;
}

Vector2D ControlSystem::getInputFactors(){
    return inputFactors;
}
