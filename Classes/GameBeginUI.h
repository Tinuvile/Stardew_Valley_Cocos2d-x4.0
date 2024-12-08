//该头文件及其cpp用来实现初始动画和初始界面

#include "cocos2d.h"

#ifndef _SCENE_SEC_H__
#define _SCENE_SEC_H__


class BeginScene : public cocos2d::Scene
{
public:
    // implement the "static create()" method manually  
    CREATE_FUNC(BeginScene);

    // Initializes the scene  
    virtual bool init();
private:
    // Plays the splash screen animation  
    void playSplashAnimation();

    // Called when the animation completes  
    void onAnimationComplete();
};

class NextScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(NextScene);
    virtual bool init();

    void menuNewCallback ( cocos2d::Ref* pSender );
    void menuCloseCallback ( cocos2d::Ref* pSender );

private:
    void addfirstscene (const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);//第一个图层动画效果
    void birdfly();
    void scenechangedown ();
    void addLogo_sec ( const cocos2d::Size& visibleSize , const cocos2d::Vec2& origin );
    void cloudsAni ( float dt );

    cocos2d::MenuItemImage* createMenuItem ( const std::string& normalImage , const std::string& selectedImage , const cocos2d::ccMenuCallback& callback , const cocos2d::Vec2& origin , float offsetX );
    void addMouseListener ( cocos2d::MenuItemImage* BeginItem , cocos2d::MenuItemImage* LoadItem , cocos2d::MenuItemImage* coopItem , cocos2d::MenuItemImage* closeItem );
    void updateMenuItem ( cocos2d::MenuItemImage* item , const cocos2d::Vec2& mousePos , const std::string& normalImage , const std::string& selectedImage );
};

#endif // _SCENE_SEC_H__








