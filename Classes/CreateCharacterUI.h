#ifndef __CreateCharacter_UI_H__
#define __CreateCharacter_UI__

#include "cocos2d.h"

class CreateCharacter : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    // implement the "static create()" method manually
    CREATE_FUNC(CreateCharacter);
};

#endif // __CreateCharacter_UI_H__
