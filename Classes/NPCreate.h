  #include "cocos2d.h"  
#include <string>  
#include <vector>
#include <cstdlib>
#include "Town.h"

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

    // NPC ����Ϊ�߼�  
    virtual void Talk () const;  // NPC ˵����Ϊ  

    // NPC�ƶ�
    void NPC::MoveToPosition ( const cocos2d::Vec2& targetPosition );

    void NPC::RandomMove ();

    bool NPC::IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction );

protected:
    std::string name;            // NPC ������  
    cocos2d::Vec2 position;      // NPC ������λ��  
    cocos2d::Sprite* sprite;     // NPC �ľ���  

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
};

// NPC ������  
class NPCreate {
public:
    // ��̬���������� NPC ʵ��  
    static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position , 
        const std::vector<std::vector<std::string>>& animationFrames , 
        const std::vector<cocos2d::Vec2>& validPositions );

    // ������� NPC �ķ���  
    static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData , 
        const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
        const std::vector<cocos2d::Vec2>& validPositions );

    cocos2d::AnimationCache* animationCache; // ���涯�� 
};
