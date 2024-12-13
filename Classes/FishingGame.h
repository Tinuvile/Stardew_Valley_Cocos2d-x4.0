#pragma once
#include"cocos2d.h"
#include"AppDelegate.h"
#include"Fish.h"

const float kBackgroundWidth = 39.0f;
const float kBackgroundHeight = 149.0f;
const float kBackgroundScale = 3.0f;

const float kIconBeginX = 17.0f;
const float kIconBeginY = 5.0f;
const float kIconHeight = kBackgroundHeight - kIconBeginY;

const float kFishBasicScale = 0.5f;

const float kGreeenBarBasicScaleY = 5.0f;

const float kProgressBarBeginX = 33.0f;
const float kProgressBarBeginY = 3.0f;

const float kProgressBarBasicScaleX = 3.0f;
const float kProgressBarBasicScaleY = 143.0f / 5.0f;


// ������Ϸ�࣬�̳���cocos2d::Layer��
// ����������Ϸ��������ҪԪ�غ��߼���������ͼ�ꡢ��ɫ���ꡢ�������ͱ�����
class FishingGame : public cocos2d::Layer {
private:
    //��ͼ��
    cocos2d::Sprite* fish;
    //��ɫ����
    cocos2d::Sprite* green_bar;
    //������
    cocos2d::ProgressTimer* progress_bar;
    
    //����
    cocos2d::Sprite* background;

    // ��Ĵ�ֱλ��
    float fishlike_icon_height = 0;
    // ��ɫ����Ĵ�ֱλ��
    float green_bar_height = 0;
    // ����Ƿ�ס���
    bool is_pressing = false; 

    //���ε����Ʒ��
    int fish_type;

    //������Ϸ��λ��
    cocos2d::Vec2 position; 

public:
    // Ĭ�Ϲ��캯����
    FishingGame () {};

    // �����λ�ò����Ĺ��캯����
    // player_pos ���λ�á�
    FishingGame ( const cocos2d::Vec2& player_pos )
        :position ( player_pos ) {};

    // ����������Ϸʵ���ľ�̬������
    // param player_position ���λ�á�
    // ���ش�����FishingGameʵ��ָ�롣
    static FishingGame* create ( const cocos2d::Vec2& player_position );

    // ��ʼ��������Ϸ��
    // ���س�ʼ���Ƿ�ɹ���
    virtual bool init ();

    // ����������Ϸʵ���ĺ궨�塣
    CREATE_FUNC ( FishingGame );

    // �������������
    void AddMouseListener ();

    // ������Ϸ״̬��
    // deltaTime �����ϴθ��µ�ʱ�䡣
    void UpdateGame (float deltaTime);

    // ������Ƿ��ڸ��귶Χ�ڡ�
    void CheckFishInBar ();

    // ������Ϸ��
    // succeed ��Ϸ�Ƿ�ɹ���
    void EndGame (bool succeed);
};
