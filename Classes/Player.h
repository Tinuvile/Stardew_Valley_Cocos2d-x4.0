#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // ���� Player ����ķ���
    static Player* create();

    // ��������ʱ�����Ļص�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ�ʱ�����Ļص�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    bool moveLeft, moveDown, moveUp, moveRight;

    bool leftpressed = false, downpressed = false, uppressed = false, rightpressed = false;

    // ��ɫ���ƶ��ٶ�
    float speed;

    int look_state = 0;

    void player1_move();

    void player_change();


private:
    // ��ʼ����ɫ
    bool init();

};

#endif // __PLAYER_H__
