#pragma once
//DailyRecordUI.h
//任务显示界面
#include "cocos2d.h"  
#include "AppDelegate.h"

class DailyRecordUI : public cocos2d::Layer {
public:
    virtual bool init ( std::string sceneName );

    static DailyRecordUI* create ( std::string sceneName );

private:
    std::string SceneName;

    void close ();

    void backgroundcreate ();

    void updateCoordinate ( float& x , float& y );

    void taskDisplay ( TaskManagement& taskManager );
};