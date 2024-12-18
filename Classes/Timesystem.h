#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"
#include <NPC.h>

class Timesystem : public cocos2d::Node {  // �̳���Node
public:
    static Timesystem* create();

    bool init() override;

    // ������Ա�����ͷ���
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;
    cocos2d::Label* _timerLabelW;
    cocos2d::Label* _timerLabelF;
    cocos2d::Sprite* TimePic;

    // �����ĳ���
    std::string place;

};