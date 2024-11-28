//��ͷ�ļ�����cpp����ʵ�ֳ�ʼ�����ͳ�ʼ����

#include "cocos2d.h"

#ifndef _SCENE_H__
#define _SCENE_H__

#include "cocos2d.h"

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

#endif // _SCENE_H__

#ifndef _SCENE_SEC_H__
#define _SCENE_SEC_H__

class NextScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(NextScene);
    virtual bool init();
private:
    void addBackground(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void addmoun_tree(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void birdfly();
    void AnimationComplete();
};

#endif // _SCENE_SEC_H__


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
    cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const cocos2d::Vec2& origin, float offsetX);
    void addBackground(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void addLogo(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
    void addMouseListener(cocos2d::MenuItemImage* BeginItem, cocos2d::MenuItemImage* LoadItem, cocos2d::MenuItemImage* coopItem, cocos2d::MenuItemImage* closeItem);
    void updateMenuItem(cocos2d::MenuItemImage* item, const cocos2d::Vec2& mousePos, const std::string& normalImage, const std::string& selectedImage);
};

#endif  //  __GameBegin_UI_H__

#include "cocos2d.h"

USING_NS_CC;

class TransitionSlideDown: public cocos2d::TransitionScene {
public:

    static TransitionSlideDown* TransitionSlideDown::create(float duration, Scene* scene)
    {
        TransitionSlideDown* pScene = new TransitionSlideDown();
        if (pScene && pScene->initWithDuration(duration, scene))
        {
            pScene->autorelease();
            return pScene;
        }
        CC_SAFE_DELETE(pScene);
        return nullptr;
    }

    void onEnter()
    {
        TransitionScene::onEnter();

        // ��ȡ��ǰ�������³�������Ч��С  
        Size size = Director::getInstance()->getVisibleSize();

        // ��ǰ���������ƶ�  
        Node* inScene = this->_inScene;
        inScene->setPosition(Vec2(0, 0)); // ��ʼλ��  

        // �³�����ʼλ������Ϊ��Ļ�ⲿ  
        Node* outScene = this->_outScene;
        outScene->setPosition(Vec2(0, size.height)); // �³�������Ļ�Ϸ�����  

        // �������»����Ķ���  
        auto moveOut = MoveBy::create(_duration, Vec2(0, -size.height)); // �ɳ��������˳�  
        auto moveIn = MoveBy::create(_duration, Vec2(0, -size.height)); // �³����������½���  

        // �������ж���  
        auto sequence = Sequence::create(
            moveOut,
            CallFunc::create(CC_CALLBACK_0(TransitionScene::finish, this)),
            nullptr
        );

        // ���ж���  
        inScene->runAction(sequence);
        outScene->runAction(moveIn); // �����³����Ķ���  
    }
};






