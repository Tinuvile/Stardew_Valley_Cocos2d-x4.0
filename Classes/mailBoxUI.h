#pragma once
//mailBoxUI.h
//������ȡ����
#include "cocos2d.h"  
#include "AppDelegate.h"

class mailBoxUI: public cocos2d::Layer {
public:
    virtual bool init ();

    static mailBoxUI* create ();

private:

    void displayAllTasks ( TaskManagement& taskManager );

    void close ();

    void backgroundcreate ();

    void updateCoordinate ( float& x , float& y );
};
