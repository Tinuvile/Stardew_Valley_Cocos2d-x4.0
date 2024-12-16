#pragma once
#include "cocos2d.h" 

// NPC ��ɫ��  
class NPC : public cocos2d::Node {
public:
    NPC ( const std::string& name , const cocos2d::Vec2& position ,
        const std::vector<std::vector<std::string>>& animationFrames ,
        const std::vector<cocos2d::Vec2>& validPositions );

    // ��ȡ NPC �ľ���  
    cocos2d::Sprite* GetSprite () const { return sprite; }

    // NPC ������
    const std::string& GetName () const { return name; }

    // NPC ��λ��  
    const cocos2d::Vec2& GetPosition () const { return position; }

    // �趨 NPC ��λ��  
    void SetPosition ( const cocos2d::Vec2& pos ) { position = pos; }

    // NPC�ƶ�
    void MoveToPosition ( const cocos2d::Vec2& targetPosition );

    void RandomMove ();

    bool IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction );

    int GetGiftTime () { return GiftTime; }

    int AddGiftTime () { GiftTime++; }

protected:
    std::string name;            // NPC ������  
    cocos2d::Vec2 position;      // NPC ������λ��  
    cocos2d::Sprite* sprite;     // NPC �ľ���

    int GiftTime = 0;                // NPC �Ƿ��͹�����

    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // ��������  
    void CreateAnimation ( const std::string& animationName , const std::vector<std::string>& framePaths , float delay );

    // ���Ŷ���  
    void PlayAnimation ( const std::string& animationName , bool loop = true );

    // ����֡  
    std::vector<std::string> upFrames;
    std::vector<std::string> downFrames;
    std::vector<std::string> leftFrames;
    std::vector<std::string> rightFrames;

    // ����֡·��  
    std::vector<std::vector<std::string>> animations; // [0]: up, [1]: down, [2]: left, [3]: right 

    std::string currentAnimationName; // ���ٵ�ǰ��������

    cocos2d::Vec2 currentDirection; // ��ǰ�ƶ�����
};


std::vector<std::vector<std::string>> getAbigailAnimations ();

std::vector<std::vector<std::string>> getDialog ( std::string npc , std::string relation_ship );

std::string getNPCportraits ( std::string name , std::string status );

std::vector<std::vector<std::string>> getAlexAnimations ();

std::vector<std::vector<std::string>> getCarolineAnimations ();

std::vector<std::vector<std::string>> getElliottAnimations ();

std::vector<std::vector<std::string>> getEmilyAnimations ();