#ifndef __GameBegin_UI_H__
#define __GameBegin_UI_H__

#include "cocos2d.h"

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
