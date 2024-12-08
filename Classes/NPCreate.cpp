#include "NPCreate.h"  

// NPC �๹�캯��  
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

// NPC ��˵����Ϊʵ��  
void NPC::Talk () const {
    CCLOG ( "NPC %s says: Hello!" , name.c_str () );
}

// NPCreate ��̬�������� NPC ʵ����ʵ��  
NPC* NPCreate::CreateNPC ( const std::string& name , const cocos2d::Vec2& position , const std::string& spritePath ) {
    NPC* npc = new NPC ( name , position , spritePath ); // ���� NPC ʵ��  
    return npc; // �����´����� NPC ָ��  
}

// NPCreate ������� NPC ��ʵ��  
std::vector<NPC*> NPCreate::CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData ) {
    std::vector<NPC*> npcs; // ���ڴ洢������ NPC  
    for (const auto& data : npcData) {
        // �����ṩĬ�Ͼ���·���������Ը�����Ҫ�޸�·��  
        npcs.push_back ( CreateNPC ( data.first , data.second , "npc/Abigail/Abigail-0.png" ) );
    }
    return npcs; // ���ش����� NPC �б�  
}