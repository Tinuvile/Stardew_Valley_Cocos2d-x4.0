#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "AppDelegate.h"


class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // ���� Player ����Ĺ�������
    static Player* create();

    // ��������ʱ�����Ļص�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ�ʱ�����Ļص�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    bool moveLeft, moveDown, moveUp, moveRight;

    Player* player;

    // ��ɫ���ƶ��ٶ�
    float speed;


private:
    // ��ʼ����ɫ
    bool init();

};

#endif // __PLAYER_H__
