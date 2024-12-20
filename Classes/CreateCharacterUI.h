#ifndef __CreateCharacter_UI_H__
#define __CreateCharacter_UI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class CreateCharacter : public cocos2d::Scene
{
public:
    CREATE_FUNC ( CreateCharacter );
    static cocos2d::Scene* createScene ();
    virtual bool init ();
    void mousedowncallback ( cocos2d::Ref* pSender , cocos2d::Sprite* item );
    void mouseupcallback ( cocos2d::Ref* pSender , cocos2d::Sprite* item );
private:
    void cloudAni ( float dt );
    void BackgroundAdd ();
    void optionFace ();
    cocos2d::Sprite* directions ( const std::string& normalImage , const cocos2d::Vec2& origin , const cocos2d::Vec2& position );
    void mouseListen ( cocos2d::Sprite* leftarrow , cocos2d::Sprite* rightarrow , cocos2d::Sprite* male  , cocos2d::Sprite* female , cocos2d::Sprite* xuanzhong , cocos2d::Sprite* displaycharacter);
    void updateItems ( cocos2d::Sprite* item , const std::string& normalImage , cocos2d::Event* event , const int Magnification );
    void textIn ();
    void favoranimal ();
    void checkTextFields ( ui::TextField* textfield1 , ui::TextField* textfield2 , ui::TextField* textfield3 );
    ui::TextField* createTextIn ( float sizex , float sizey , const Vec2& Pos);
    // implement the "static create()" method manually
};

#endif // __CreateCharacter_UI_H__
