#include "Player.h"

USING_NS_CC;  // 使用 Cocos2d-x 命名空间

// Player 类的构造函数
Player::Player() : speed(10.0f),pic_path("character1 / player_down3.png") {}

// Player 类的析构函数
Player::~Player() {}

// Player 类的初始化函数
bool Player::init()
{
    if (!Sprite::init())  // 初始化父类 Sprite，检查是否成功
    {
        return false;  // 如果初始化失败，返回 false
    }

    // 加载角色的图片（玩家朝下的站立图片）
    this->initWithFile("character1/player_down3.png");

    // 创建键盘事件监听器
    auto keyboardListener = EventListenerKeyboard::create();

    // 按下键盘时更新方向
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);

    // 按键释放时停止移动
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // 将监听器添加到事件派发器中，监听事件
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每 0.05 秒调用一次 player1_move() 函数，控制玩家移动
    this->schedule([this](float dt) {
        this->player1_move();
        }, 0.05f, "player1_move");

    // 每 0.3 秒调用一次 player_change() 函数，控制玩家动画切换
    this->schedule([this](float dt) {
        this->player_change();
        }, 0.3f, "player_change");

    return true;  // 初始化成功，返回 true
}

// Player 类的静态创建方法
Player* Player::create()
{
    Player* player = new Player();  // 创建 Player 对象
    if (player && player->init())  // 如果创建并初始化成功
    {
        player->autorelease();  // 自动释放内存
        return player;  // 返回新创建的 Player 对象
    }
    CC_SAFE_DELETE(player);  // 如果创建失败，删除 player 对象
    return nullptr;  // 返回空指针
}

// 按键按下时的回调函数
void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    float X = this->getPositionX();  // 获取当前玩家的 X 坐标
    float Y = this->getPositionY();  // 获取当前玩家的 Y 坐标

    // 判断按下的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !uppressed)  // 上箭头
    {
        uppressed = true;  // 标记上键已按下
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !downpressed)  // 下箭头
    {
        downpressed = true;  // 标记下键已按下
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !leftpressed)  // 左箭头
    {
        leftpressed = true;  // 标记左键已按下
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !rightpressed)  // 右箭头
    {
        rightpressed = true;  // 标记右键已按下
    }
}

// 按键释放时的回调函数
void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 判断松开的方向键，并更新角色的移动状态
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // 上箭头
    {
        this->look_state = 0;  // 复位 look_state 状态
        this->setTexture("character1/player_up3.png");  // 设置玩家朝上的图片
        this->pic_path = "character1/player_up3.png";
        uppressed = false;  // 标记上键已松开
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // 下箭头
    {
        this->look_state = 0;  // 复位 look_state 状态
        this->setTexture("character1/player_down3.png");  // 设置玩家朝下的图片
        this->pic_path = "character1/player_down3.png";
        downpressed = false;  // 标记下键已松开
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // 左箭头
    {
        this->look_state = 0;  // 复位 look_state 状态
        this->setTexture("character1/player_left3.png");  // 设置玩家朝左的图片
        this->pic_path = "character1/player_left3.png";
        leftpressed = false;  // 标记左键已松开
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // 右箭头
    {
        this->look_state = 0;  // 复位 look_state 状态
        this->setTexture("character1/player_right3.png");  // 设置玩家朝右的图片
        this->pic_path = "character1/player_right3.png";
        rightpressed = false;  // 标记右键已松开
    }
}

// 玩家移动的逻辑
void Player::player1_move() {

    // 如果按下左箭头并且允许向左移动
    if (this->leftpressed && this->moveLeft) {
        if (this->look_state == 0) {
            this->look_state++;  // 如果玩家静止状态，更新状态
            return;
        }
        this->setPositionX(this->getPositionX() - speed);  // 向左移动
    }
    // 如果按下下箭头并且允许向下移动
    else if (this->downpressed && this->moveDown) {
        if (this->look_state == 0) {
            this->look_state++;  // 如果玩家静止状态，更新状态
            return;
        }
        this->setPositionY(this->getPositionY() - speed);  // 向下移动
    }
    // 如果按下上箭头并且允许向上移动
    else if (this->uppressed && this->moveUp) {
        if (this->look_state == 0) {
            this->look_state++;  // 如果玩家静止状态，更新状态
            return;
        }
        this->setPositionY(this->getPositionY() + speed);  // 向上移动
    }
    // 如果按下右箭头并且允许向右移动
    else if (this->rightpressed && this->moveRight) {
        if (this->look_state == 0) {
            this->look_state++;  // 如果玩家静止状态，更新状态
            return;
        }
        this->setPositionX(this->getPositionX() + speed);  // 向右移动
    }
}

// 玩家状态变化的逻辑（切换动画）
void Player::player_change() {

    // 如果按下左箭头并且允许向左移动
    if (this->leftpressed && this->moveLeft) {
        if (this->look_state % 2 == 1) {  // 如果是奇数帧，切换为第一个动画
            this->look_state++;
            this->setTexture("character1/player_left1.png");
        }
        else {  // 如果是偶数帧，切换为第二个动画
            this->look_state++;
            this->setTexture("character1/player_left2.png");
        }
    }
    // 如果按下下箭头并且允许向下移动
    else if (this->downpressed && this->moveDown) {
        if (this->look_state % 2 == 1) {  // 如果是奇数帧，切换为第一个动画
            this->look_state++;
            this->setTexture("character1/player_down1.png");
        }
        else {  // 如果是偶数帧，切换为第二个动画
            this->look_state++;
            this->setTexture("character1/player_down2.png");
        }
    }
    // 如果按下上箭头并且允许向上移动
    else if (this->uppressed && this->moveUp) {
        if (this->look_state % 2 == 1) {  // 如果是奇数帧，切换为第一个动画
            this->look_state++;
            this->setTexture("character1/player_up1.png");
        }
        else {  // 如果是偶数帧，切换为第二个动画
            this->look_state++;
            this->setTexture("character1/player_up2.png");
        }
    }
    // 如果按下右箭头并且允许向右移动
    else if (this->rightpressed && this->moveRight) {
        if (this->look_state % 2 == 1) {  // 如果是奇数帧，切换为第一个动画
            this->look_state++;
            this->setTexture("character1/player_right1.png");
        }
        else {  // 如果是偶数帧，切换为第二个动画
            this->look_state++;
            this->setTexture("character1/player_right2.png");
        }
    }
}
