#include "Player.h"

USING_NS_CC;  // 使用 Cocos2d-x 命名空间

// Player 类的构造函数
Player::Player() : speed(10.0f), pic_path("character1 / player_down3.png"), 
    moveLeft(true), moveDown(true), moveUp(true), moveRight(true),
    leftpressed(false), downpressed(false), uppressed(false), rightpressed(false) {
    // 构造函数体
}

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

// 设置移动状态（由输入处理器调用）
void Player::setMovementState(MovementDirection direction, bool isPressed) {
    CCLOG("[Player] setMovementState called: direction=%d, isPressed=%s", 
          static_cast<int>(direction), isPressed ? "true" : "false");
    switch (direction) {
        case DIRECTION_UP:
            if (!uppressed && isPressed) {
                uppressed = true;
                moveUp = true;  // 允许向上移动
                this->look_state = 0;  // 重置动画状态
                CCLOG("[Player] UP key pressed - uppressed=true, moveUp=true");
            } else if (uppressed && !isPressed) {
                uppressed = false;
                moveUp = true;  // 保持允许移动
                updateTexture(DIRECTION_UP);
                CCLOG("[Player] UP key released - uppressed=false, moveUp=true");
            }
            break;
        case DIRECTION_DOWN:
            if (!downpressed && isPressed) {
                downpressed = true;
                moveDown = true;  // 允许向下移动
                this->look_state = 0;
                CCLOG("[Player] DOWN key pressed - downpressed=true, moveDown=true");
            } else if (downpressed && !isPressed) {
                downpressed = false;
                moveDown = true;  // 保持允许移动
                updateTexture(DIRECTION_DOWN);
                CCLOG("[Player] DOWN key released - downpressed=false, moveDown=true");
            }
            break;
        case DIRECTION_LEFT:
            if (!leftpressed && isPressed) {
                leftpressed = true;
                moveLeft = true;  // 允许向左移动
                this->look_state = 0;
                CCLOG("[Player] LEFT key pressed - leftpressed=true, moveLeft=true");
            } else if (leftpressed && !isPressed) {
                leftpressed = false;
                moveLeft = true;  // 保持允许移动
                updateTexture(DIRECTION_LEFT);
                CCLOG("[Player] LEFT key released - leftpressed=false, moveLeft=true");
            }
            break;
        case DIRECTION_RIGHT:
            if (!rightpressed && isPressed) {
                rightpressed = true;
                moveRight = true;  // 允许向右移动
                this->look_state = 0;
                CCLOG("[Player] RIGHT key pressed - rightpressed=true, moveRight=true");
            } else if (rightpressed && !isPressed) {
                rightpressed = false;
                moveRight = true;  // 保持允许移动
                updateTexture(DIRECTION_RIGHT);
                CCLOG("[Player] RIGHT key released - rightpressed=false, moveRight=true");
            }
            break;
    }
}

// 获取移动状态
bool Player::getMovementState(int direction) const {
    switch (direction) {
        case DIRECTION_UP:
            return uppressed;
        case DIRECTION_DOWN:
            return downpressed;
        case DIRECTION_LEFT:
            return leftpressed;
        case DIRECTION_RIGHT:
            return rightpressed;
        default:
            return false;
    }
}

// 更新玩家贴图
void Player::updateTexture(int direction) {
    this->look_state = 0;  // 复位 look_state 状态
    
    switch (direction) {
        case DIRECTION_UP:
            this->setTexture("character1/player_up3.png");
            this->pic_path = "character1/player_up3.png";
            break;
        case DIRECTION_DOWN:
            this->setTexture("character1/player_down3.png");
            this->pic_path = "character1/player_down3.png";
            break;
        case DIRECTION_LEFT:
            this->setTexture("character1/player_left3.png");
            this->pic_path = "character1/player_left3.png";
            break;
        case DIRECTION_RIGHT:
            this->setTexture("character1/player_right3.png");
            this->pic_path = "character1/player_right3.png";
            break;
    }
}

// 玩家移动的逻辑
void Player::player1_move() {
    // 调试移动状态
    static int debugCounter = 0;
    if (debugCounter % 60 == 0) { // 每秒输出一次（假设60FPS）
        CCLOG("[Player] Movement flags: leftPressed=%s moveLeft=%s downPressed=%s moveDown=%s upPressed=%s moveUp=%s rightPressed=%s moveRight=%s",
              leftpressed ? "T" : "F", moveLeft ? "T" : "F",
              downpressed ? "T" : "F", moveDown ? "T" : "F", 
              uppressed ? "T" : "F", moveUp ? "T" : "F",
              rightpressed ? "T" : "F", moveRight ? "T" : "F");
    }
    debugCounter++;

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
