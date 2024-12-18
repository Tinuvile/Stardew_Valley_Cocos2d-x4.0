#include "Timesystem.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "DailyRecordUI.h"

USING_NS_CC;



bool Timesystem::init( std::string place ) {
    // ���ø����init()
    if (!Node::init()) {  // ����̳���Node������Node��init
        return false;
    }
    Place = place;
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

    //�����ʾ
    moneyDisplay = Sprite::create ( "UIresource/supermarket/moneyFrame_new.png" );
    moneyDisplay->setScale ( 3.5f );
    this->addChild ( moneyDisplay , 1 );
    moneyDisplay->setPosition ( 630 , 330 );
    GoldAmountDisplay = nullptr;
    int goldAmount = GoldAmount;
    if (GoldAmountDisplay == nullptr) {
        GoldAmountDisplay = Label::createWithTTF ( std::to_string ( goldAmount ) , "fonts/Marker Felt.ttf" , 45 );
        GoldAmountDisplay->setTextColor ( Color4B::WHITE );
        GoldAmountDisplay->setPosition ( 630 , 320 );
        this->addChild ( GoldAmountDisplay , 4 );
    }

    //��־��ʾ
    DailyRecord = Sprite::create ( "UIresource/rizhi.png" );
    this->addChild ( DailyRecord , 1 );
    DailyRecord->setScale ( 1.5f );
    DailyRecord->setPosition ( 670 , 250 );

    auto listener = EventListenerMouse::create ();
    listener->onMouseMove = [this]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        if (DailyRecord->getBoundingBox ().containsPoint ( mousePos )) {
            DailyRecord->setScale ( 1.5f * 1.2f );
        }
        else
            DailyRecord->setScale ( 1.5f );
        };
    listener->onMouseDown = [this]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        if (DailyRecord->getBoundingBox ().containsPoint ( mousePos )) {
            DailyRecordUI* Dailyrecord = DailyRecordUI::create ( Place );
            Dailyrecord->setScale ( 0.9f );
            // ��ȡ��ǰ���еĳ���
            Scene* currentScene = Director::getInstance ()->getRunningScene ();
            currentScene->addChild ( Dailyrecord , 20 );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , DailyRecord );

    this->schedule([this](float dt) {
        _timerLabelD->setString("Day: " + std::to_string(day));
        _timerLabelH->setString(std::to_string(remainingTime / 1800) + ":00");
        _timerLabelS->setString(Season);
        GoldAmountDisplay->setString ( std::to_string ( GoldAmount ) );
        }, 0.01f, "updatetime");

    return true;
}

Timesystem* Timesystem::create( std::string place ) {
    Timesystem* ret = new Timesystem();
    if (ret && ret->init(place)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}