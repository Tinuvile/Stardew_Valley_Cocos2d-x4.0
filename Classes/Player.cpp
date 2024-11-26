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

    // ���ؽ�ɫ��ͼƬ
    this->initWithFile("character1/player_stop.png");

    // ���������¼�������
    auto keyboardListener = EventListenerKeyboard::create();

    // ���¼���ʱ���·���
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);

    // �����ͷ�ʱֹͣ�ƶ�
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

    // ����������ӵ��¼��ɷ�����
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

    // �жϰ��µķ�����������½�ɫ���ƶ�״̬
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !moveUp)  // �ϼ�ͷ
    {
        moveUp = true;

        this->setPositionY(this->getPositionY() + speed);  // ֻ�ƶ�һ��
        this->setTexture("character1/player_up.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !moveDown)  // �¼�ͷ
    {
        moveDown = true;

        this->setPositionY(this->getPositionY() - speed);
        this->setTexture("character1/player_down.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !moveLeft)  // ���ͷ
    {
        moveLeft = true;

        this->setPositionX(this->getPositionX() - speed);  // ֻ�ƶ�һ��
        this->setTexture("character1/player_left.png");

    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !moveRight)  // �Ҽ�ͷ
    {
        moveRight = true;

        this->setPositionX(this->getPositionX() + speed);  // ֻ�ƶ�һ��
        this->setTexture("character1/player_right.png");

    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    // �ж��ɿ��ķ�����������½�ɫ���ƶ�״̬
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  // �ϼ�ͷ
    {
        moveUp = false;
        this->setTexture("character1/player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  // �¼�ͷ
    {
        moveDown = false;
        this->setTexture("character1/player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  // ���ͷ
    {
        moveLeft = false;
        this->setTexture("character1/player_stop.png");  // �л��������ߡ�ͼ��
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  // �Ҽ�ͷ
    {
        moveRight = false;
        this->setTexture("character1/player_stop.png");  // �л��������ߡ�ͼ��
    }
}