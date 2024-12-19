#pragma once
//quitUI.h
//ÍË³ö½çÃæ
#include "cocos2d.h"  
#include "AppDelegate.h"

class quitUI : public cocos2d::Layer {
public:
    virtual bool init ( std::string sceneName );

    static quitUI* create ( std::string sceneName );

private:
    void close ();

    void backgroundcreate ();

    void Buttons_switching ();

    void updateCoordinate ( float& x , float& y );

    void quitAndsetting ();

    std::string SceneName;
};