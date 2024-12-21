#pragma once
//Marry.h
//ªÈ“ˆœ‘ æΩÁ√Ê
#include "cocos2d.h"  
#include "AppDelegate.h"

class Marry : public cocos2d::Layer {
public:
    virtual bool init ( std::string sceneName ,std::string npcName);

    static Marry* create ( std::string sceneName , std::string npcName );

private:
    std::string SceneName;

    std::string NpcName;

    void backgroundcreate ();

    void updateCoordinate ( float& x , float& y );

    void ifmarry ();

    void SelectedAnswer ();
};