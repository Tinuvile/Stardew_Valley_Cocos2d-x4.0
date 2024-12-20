#include "Timesystem.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "DailyRecordUI.h"

USING_NS_CC;



bool Timesystem::init( std::string place ) {
    // 调用父类的init()
    if (!Node::init()) {  // 如果继承自Node，调用Node的init
        return false;
    }
    Place = place;
    // 设置计时器标签
    timer_label_day = Label::createWithTTF("Day: 0", "fonts/Marker Felt.ttf", 24);
    this->addChild(timer_label_day, 2);
    timer_label_day->setScale(1.7f);
    timer_label_day->setString("Day" + day);

    timer_label_hour = Label::createWithTTF("0:00", "fonts/Marker Felt.ttf", 24);
    this->addChild(timer_label_hour, 2);
    timer_label_hour->setScale(1.7f);
    timer_label_day->setString(remainingTime / 1800 + ":00");

    timer_label_season = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 24);
    this->addChild(timer_label_season, 2);
    timer_label_season->setScale(1.5f);
    timer_label_season->setString(Season);

    timer_label_weather = Label::createWithTTF("Rainy", "fonts/Marker Felt.ttf", 24);
    this->addChild(timer_label_weather, 2);
    timer_label_weather->setScale(1.5f);
    timer_label_weather->setString(Weather);

    timer_label_festival = Label::createWithTTF("Fishing Festival", "fonts/Marker Felt.ttf", 24);
    this->addChild(timer_label_festival, 2);
    timer_label_festival->setScale(1.5f);
    timer_label_festival->setString(Festival);

    // 创建时间背景图片
    time_pic = Sprite::create("UIresource/TimePic.png");
    time_pic->setScale(1.7f);
    this->addChild(time_pic, 1);  // 设置图片层级在标签下方

    // 创建体力边框
    energy_frame = Sprite::create("UIresource/strength.png");
    energy_frame->setScale(3.7f);
    this->addChild(energy_frame, 1);
    energy_frame->setPosition(435, 500);

    energy_bar = Sprite::create("Beach/green_bar.png");
    energy_bar->setScaleY(strength / 100 * 16.5f);
    energy_bar->setScaleX(3.1f);
    energy_bar->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->addChild(energy_bar, 3);
    energy_bar->setPosition(435, 405);

    // 设置各元素的位置
    timer_label_day->setPosition(585, 575);
    timer_label_hour->setPosition(690, 575);
    timer_label_season->setPosition(570, 500);
    timer_label_weather->setPosition(710, 500);
    timer_label_festival->setPosition(630, 415);
    time_pic->setPosition(630, 490);
   

    //金币显示
    currency_frame = Sprite::create ( "UIresource/supermarket/moneyFrame_new.png" );
    currency_frame->setScale ( 3.5f );
    this->addChild ( currency_frame , 1 );
    currency_frame->setPosition ( 630 , 330 );
    currency_num = nullptr;
    int goldAmount = GoldAmount;
    if (currency_num == nullptr) {
        currency_num = Label::createWithTTF ( std::to_string ( goldAmount ) , "fonts/Marker Felt.ttf" , 45 );
        currency_num->setTextColor ( Color4B::WHITE );
        currency_num->setPosition ( 630 , 320 );
        this->addChild ( currency_num , 4 );
    }

    //日志显示
    daily_record = Sprite::create ( "UIresource/rizhi.png" );
    this->addChild ( daily_record , 1 );
    daily_record->setScale ( 1.5f );
    daily_record->setPosition ( 670 , 250 );

    auto listener = EventListenerMouse::create ();
    listener->onMouseMove = [this]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        if (daily_record->getBoundingBox ().containsPoint ( mousePos )) {
            daily_record->setScale ( 1.5f * 1.2f );
        }
        else
            daily_record->setScale ( 1.5f );
        };
    listener->onMouseDown = [this, place](EventMouse* event) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        if (daily_record->getBoundingBox ().containsPoint ( mousePos )) {
            DailyRecordUI* Dailyrecord = DailyRecordUI::create(place);
            // 获取当前运行的场景
            Scene* currentScene = Director::getInstance ()->getRunningScene ();
            currentScene->addChild ( Dailyrecord , 20 );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , daily_record );

    this->schedule([this](float dt) {
        timer_label_day->setString("Day: " + std::to_string(day));
        timer_label_hour->setString(std::to_string(remainingTime / 1800) + ":00");
        timer_label_season->setString(Season);
        currency_num->setString ( std::to_string ( GoldAmount ) );
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

void Timesystem::UpdateEnergy () {
    TimeUI->energy_bar->setScaleY ( strength / 100.0 * 16.5f );
}