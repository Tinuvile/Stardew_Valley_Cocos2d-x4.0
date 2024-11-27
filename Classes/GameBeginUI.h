//该头文件及其cpp用来实现初始动画和初始界面

#include "cocos2d.h"

#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class BeginScene : public cocos2d::Scene
{
public:
    // implement the "static create()" method manually  
    CREATE_FUNC(BeginScene);

    static cocos2d::Scene* createScene();

    // Initializes the scene  
    virtual bool init() override;

    // Plays the splash screen animation  
    void playSplashAnimation();

    // Called when the animation completes  
    void onAnimationComplete();
};

#endif // __SPLASH_SCENE_H__


#ifndef __GameBegin_UI_H__
#define __GameBegin_UI_H9__

class GameBegin : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void GameBegin::menuNewCallback(cocos2d::Ref* pSender);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameBegin);

private:
    // Helper methods  
    cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin, float offsetX);
    void addBackground(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void addLogo(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void addMouseListener(cocos2d::MenuItemImage* BeginItem, cocos2d::MenuItemImage* LoadItem, cocos2d::MenuItemImage* coopItem, cocos2d::MenuItemImage* closeItem);
    void updateMenuItem(cocos2d::MenuItemImage* item, const cocos2d::Vec2& mousePos, const std::string& normalImage, const std::string& selectedImage);
};

#endif // __GameBegin_UI_H__
