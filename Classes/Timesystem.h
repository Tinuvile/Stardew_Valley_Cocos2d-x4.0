#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"
#include <NPC.h>

class Timesystem : public cocos2d::Node {  // �̳���Node
public:
    bool init ( std::string place );

    static Timesystem* create ( std::string place );

    void UpdateEnergy();

    // ������Ա�����ͷ���
    cocos2d::Label* timer_label_day;
    cocos2d::Label* timer_label_hour;
    cocos2d::Label* timer_label_season;
    cocos2d::Label* timer_label_weather;
    cocos2d::Label* timer_label_festival;
    cocos2d::Sprite* time_pic;
    cocos2d::Sprite* energy_frame;
    cocos2d::Sprite* energy_bar;

    cocos2d::Sprite* currency_frame;
    cocos2d::Label* currency_num;

    cocos2d::Sprite* daily_record;

    // �����ĳ���
    std::string Place;
};