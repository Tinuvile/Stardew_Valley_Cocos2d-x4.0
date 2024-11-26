#include "Player.h"

USING_NS_CC;

Player::Player() : speed(10.0f) {}

Player::~Player() {}

bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 加载角色的图片
    this->initWithFile("character1/player_stop.png");

    // 创建键盘事件监听器
    auto keyboardListener = EventListenerKeyboard::create();

    // 按下键盘时更新方向
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);

    // 按键释放时停止移动
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // 将监听器添加到事件派发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    
    return true;
}

Player* Player::create()
{
    Player* player = new Player();
    if (player && player->init())
    {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}


void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    float X = this->getPositionX();
    float Y = this->getPositionY();

    // 判断按下的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !moveUp)  // 上箭头
    {
        moveUp = true;

        this->setPositionY(this->getPositionY() + speed);  // 只移动一次
        this->setTexture("character1/player_up.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !moveDown)  // 下箭头
    {
        moveDown = true;

        this->setPositionY(this->getPositionY() - speed);
        this->setTexture("character1/player_down.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !moveLeft)  // 左箭头
    {
        moveLeft = true;

        this->setPositionX(this->getPositionX() - speed);  // 只移动一次
        this->setTexture("character1/player_left.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !moveRight)  // 右箭头
    {
        moveRight = true;

        this->setPositionX(this->getPositionX() + speed);  // 只移动一次
        this->setTexture("character1/player_right.png");

    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 判断松开的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // 上箭头
    {
        moveUp = false;
        this->setTexture("character1/player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // 下箭头
    {
        moveDown = false;
        this->setTexture("character1/player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // 左箭头
    {
        moveLeft = false;
        this->setTexture("character1/player_stop.png");  // 切换到“下走”图像
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // 右箭头
    {
        moveRight = false;
        this->setTexture("character1/player_stop.png");  // 切换到“下走”图像
    }
}