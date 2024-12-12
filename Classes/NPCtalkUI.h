//NPCtalkUI.h
#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"

class NPCtalkUI : public cocos2d::Layer {
public:
    virtual bool init ();

    static NPCtalkUI* create ();

    void backgroundcreate ();

    void close ();
private:


};
