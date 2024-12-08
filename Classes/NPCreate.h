#pragma once  

#include "cocos2d.h"  
#include <string>  
#include <vector>  

// NPC 角色类  
class NPC {
public:
    NPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath );

    // 获取 NPC 的精灵  
    cocos2d::Sprite* GetSprite () const { return sprite; }

    // NPC 的名称  
    const std::string& GetName () const { return name; }

    // NPC 的位置  
    const cocos2d::Vec2& GetPosition () const { return position; }

    // 设定 NPC 的位置  
    void SetPosition ( const cocos2d::Vec2& pos ) { position = pos; }

    // NPC 的行为逻辑  
    virtual void Talk () const;  // NPC 说话行为  

protected:
    std::string name;            // NPC 的名字  
    cocos2d::Vec2 position;      // NPC 的坐标位置  
    cocos2d::Sprite* sprite;     // NPC 的精灵  
};

// NPC 创建类  
class NPCreate {
public:
    // 静态方法，创建 NPC 实例  
    static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath );

    // 创建多个 NPC 的方法  
    static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData );
};
