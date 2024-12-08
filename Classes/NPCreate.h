#pragma once  

#include "cocos2d.h"  
#include <string>  
#include <vector>  

// NPC ��ɫ��  
class NPC {
public:
    NPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath );

    // ��ȡ NPC �ľ���  
    cocos2d::Sprite* GetSprite () const { return sprite; }

    // NPC ������  
    const std::string& GetName () const { return name; }

    // NPC ��λ��  
    const cocos2d::Vec2& GetPosition () const { return position; }

    // �趨 NPC ��λ��  
    void SetPosition ( const cocos2d::Vec2& pos ) { position = pos; }

    // NPC ����Ϊ�߼�  
    virtual void Talk () const;  // NPC ˵����Ϊ  

protected:
    std::string name;            // NPC ������  
    cocos2d::Vec2 position;      // NPC ������λ��  
    cocos2d::Sprite* sprite;     // NPC �ľ���  
};

// NPC ������  
class NPCreate {
public:
    // ��̬���������� NPC ʵ��  
    static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath );

    // ������� NPC �ķ���  
    static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData );
};
