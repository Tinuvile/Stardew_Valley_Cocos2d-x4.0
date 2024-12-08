#include "NPCreate.h"  

// NPC 类构造函数  
NPC::NPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath )
    : name ( name ) , position ( position ) {
    sprite = cocos2d::Sprite::create ( spritePath );
    if (sprite) {
        sprite->setPosition ( position );
    }
    else {
        CCLOG ( "Error: Could not load sprite from path: %s" , spritePath.c_str () );
    }
}

// NPC 的说话行为实现  
void NPC::Talk () const {
    CCLOG ( "NPC %s says: Hello!" , name.c_str () );
}

// NPCreate 静态方法创建 NPC 实例的实现  
NPC* NPCreate::CreateNPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath ) {
    NPC* npc = new NPC ( name , position , spritePath ); // 创建 NPC 实例  
    return npc; // 返回新创建的 NPC 指针  
}

// NPCreate 创建多个 NPC 的实现  
std::vector<NPC*> NPCreate::CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData ) {
    std::vector<NPC*> npcs; // 用于存储创建的 NPC  
    for (const auto& data : npcData) {
        // 假设提供默认精灵路径，您可以根据需要修改路径  
        npcs.push_back ( CreateNPC ( data.first , data.second , "npc/Abigail/Abigail-0.png" ) );
    }
    return npcs; // 返回创建的 NPC 列表  
}