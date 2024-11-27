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
    void playSplashAnimation();
    void onAnimationComplete();
    virtual bool init();

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
};

#endif // __GameBegin_UI_H__
