#include "CreateCharacterUI.h"

USING_NS_CC;

Scene* CreateCharacter::createScene()
{
    return CreateCharacter::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CreateCharacter::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "CreateCharacter" splash screen"
    auto example = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/Cloudy_Ocean_BG.png");
    if (example == nullptr)
    {
        // 示例图片
        problemLoading("'Cloudy_Ocean_BG.png'");
    }
    else
    {
        // 获取窗口的可视大小  
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // 计算所需的缩放比例  
        float scaleX = visibleSize.width / example->getContentSize().width;
        float scaleY = visibleSize.height / example->getContentSize().height;

        // 选择较大的缩放因子进行放大（以确保填充整个窗口）  
        float scaleFactor = std::max(scaleX, scaleY);
        example->setScale(scaleFactor);

        // position the sprite on the center of the screen
        example->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(example, 0);
    }


    return true;
}
