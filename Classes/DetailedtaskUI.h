#pragma once
//DetailedtaskUI.h
//任务具体界面
#include "cocos2d.h"  
#include "AppDelegate.h"

class DetailedtaskUI : public cocos2d::Layer {
public:
    virtual bool init ( TaskManagement::Task task );

    static DetailedtaskUI* create ( TaskManagement::Task task );

private:

    void displayTask ( TaskManagement::Task task );

    void close ();

    void backgroundcreate ();

    void updateCoordinate ( float& x , float& y );

};
