#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"
#include <NPC.h>

class Timesystem : public cocos2d::Node {  // 继承自Node
public:
    static Timesystem* create();

    bool init() override;

    // 其他成员变量和方法
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;
    cocos2d::Label* _timerLabelW;
    cocos2d::Label* _timerLabelF;
    cocos2d::Sprite* TimePic;

    // 所处的场景
    std::string place;

};