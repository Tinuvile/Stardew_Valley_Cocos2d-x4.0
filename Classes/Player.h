#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Inventory.h"
#include "Crop.h"
#include "AppDelegate.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // ���� Player ����ķ���
    static Player* create();

    // ��ʼ����ɫ
    bool init();

    // ��������ʱ�����Ļص�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ�ʱ�����Ļص�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void player1_move();

    void player_change();


    bool moveLeft, moveDown, moveUp, moveRight;

    bool leftpressed = false, downpressed = false, uppressed = false, rightpressed = false;

    // ��ɫ���ƶ��ٶ�
    float speed;

    int look_state = 0;

    std::string pic_path;



};

#endif // __PLAYER_H__
