#include "Player.h"

USING_NS_CC;

extern int remainingTime;

Player::Player() : speed(10.0f) {}

Player::~Player() {}

bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 加载角色的图片
    this->initWithFile("character1/player_down3.png");

    // 创建键盘事件监听器
    auto keyboardListener = EventListenerKeyboard::create();

    // 按下键盘时更新方向
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);

    // 按键释放时停止移动
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // 将监听器添加到事件派发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->schedule([this](float dt) {
        this->player1_move();
        }, 0.05f, "player1_move");

    this->schedule([this](float dt) {
        this->player_change();
        }, 0.3f, "player_change");

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
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !uppressed)  // 上箭头
    {
        uppressed = true;
        
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !downpressed)  // 下箭头
    {
      
        downpressed = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !leftpressed)  // 左箭头
    {
        leftpressed = true;
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !rightpressed)  // 右箭头
    {
        rightpressed = true;
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 判断松开的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // 上箭头
    {
        this->look_state = 0;
        this->setTexture("character1/player_up3.png");
        uppressed = false;
       
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // 下箭头
    {
        this->look_state = 0;
        this->setTexture("character1/player_down3.png");
        downpressed = false;
       
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // 左箭头
    {
        this->look_state = 0;
        this->setTexture("character1/player_down3.png");
        leftpressed = false;
        
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // 右箭头
    {
        this->look_state = 0;
        this->setTexture("character1/player_right3.png");
        rightpressed = false;
        
    }
}

void Player::player1_move() {

    if (this->leftpressed && this->moveLeft) {

        if (this->look_state == 0) {
            this->look_state++;
            return;
        }
        this->setPositionX(this->getPositionX() - speed);

    }
    else if (this->downpressed && this->moveDown) {

        if (this->look_state == 0) {
            this->look_state++;
            return;
        }
        this->setPositionY(this->getPositionY() - speed);

    }
    else if (this->uppressed && this->moveUp) {
        if (this->look_state == 0) {
            this->look_state++;
            return;
        }
        this->setPositionY(this->getPositionY() + speed);

    }
    else if (this->rightpressed && this->moveRight) {
        if (this->look_state == 0) {
            this->look_state++;
            return;
        }
        this->setPositionX(this->getPositionX() + speed);

    }

}

void Player::player_change() {

    if (this->leftpressed && this->moveLeft) {

        if (this->look_state % 2 == 1) {
            this->look_state++;
            this->setTexture("character1/player_left1.png");

        }
        else {
            this->look_state++;
            this->setTexture("character1/player_left2.png");
        }

    }
    else if (this->downpressed && this->moveDown) {

        if (this->look_state % 2 == 1) {
            this->look_state++;
            this->setTexture("character1/player_down1.png");

        }
        else {
            this->look_state++;
            this->setTexture("character1/player_down2.png");
        }

    }
    else if (this->uppressed && this->moveUp) {

        if (this->look_state % 2 == 1) {
            this->look_state++;
            this->setTexture("character1/player_up1.png");

        }
        else {
            this->look_state++;
            this->setTexture("character1/player_up2.png");
        }

    }
    else if (this->rightpressed && this->moveRight) {

        if (this->look_state % 2 == 1) {
            this->look_state++;
            this->setTexture("character1/player_right1.png");

        }
        else {
            this->look_state++;
            this->setTexture("character1/player_right2.png");
        }

    }
}

