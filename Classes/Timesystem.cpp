#include "Timesystem.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  


USING_NS_CC;



bool Timesystem::init() {
    // ���ø����init()
    if (!Node::init()) {  // ����̳���Node������Node��init
        return false;
    }

    // ���ü�ʱ����ǩ
    _timerLabelD = Label::createWithTTF("Day: 0", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelD, 2);
    _timerLabelD->setScale(1.7f);
    _timerLabelD->setString("Day" + day);

    _timerLabelH = Label::createWithTTF("0:00", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelH, 2);
    _timerLabelH->setScale(1.7f);
    _timerLabelD->setString(remainingTime / 1800 + ":00");

    _timerLabelS = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelS, 2);
    _timerLabelS->setScale(1.5f);
    _timerLabelS->setString(Season);

    _timerLabelW = Label::createWithTTF("Rainy", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelW, 2);
    _timerLabelW->setScale(1.5f);
    _timerLabelW->setString(Weather);

    _timerLabelF = Label::createWithTTF("Fishing Festival", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelF, 2);
    _timerLabelF->setScale(1.5f);
    _timerLabelF->setString(Festival);

    // ����ʱ�䱳��ͼƬ
    TimePic = Sprite::create("UIresource/TimePic.png");
    TimePic->setScale(1.7f);
    this->addChild(TimePic, 1);  // ����ͼƬ�㼶�ڱ�ǩ�·�

    // ���ø�Ԫ�ص�λ��

    _timerLabelD->setPosition(585, 575);
    _timerLabelH->setPosition(690, 575);
    _timerLabelS->setPosition(570, 500);
    _timerLabelW->setPosition(710, 500);
    _timerLabelF->setPosition(630, 415);
    TimePic->setPosition(630, 490);




    this->schedule([this](float dt) {
        _timerLabelD->setString("Day: " + std::to_string(day));
        _timerLabelH->setString(std::to_string(remainingTime / 1800) + ":00");
        _timerLabelS->setString(Season);
        }, 0.01f, "updatetime");

    return true;
}

Timesystem* Timesystem::create() {
    Timesystem* ret = new Timesystem();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}