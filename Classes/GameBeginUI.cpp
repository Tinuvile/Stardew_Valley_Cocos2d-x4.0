#include "GameBeginUI.h"  
#include "CreateCharacterUI.h"  
#include "Player.h"  
#include "Town.h"  

USING_NS_CC;
///////////////////////////////
//以下为BeginScene初始动画的实现部分
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
bool BeginScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255)); // 设置背景颜色为白色  
    this->addChild(layer);

    // 播放开场动画  
    playSplashAnimation();

    return true;
}

void BeginScene::playSplashAnimation()
{
    //动画制作

    cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
    std::string frameName1 = "UIresource/hebing1.png";
    auto frame1 = SpriteFrame::create("UIresource/hebing1.png", Rect(0, 0, 214, 67));
    auto frame2 = SpriteFrame::create("UIresource/hebing2.png", Rect(0, 0, 220, 69));
    auto frame3 = SpriteFrame::create("UIresource/hebing3.png", Rect(0, 0, 214, 67));
    auto frame4 = SpriteFrame::create("UIresource/hebing4.png", Rect(0, 0, 220, 69));
    auto frame5 = SpriteFrame::create("UIresource/hebing5.png", Rect(0, 0, 214, 67));
    auto frame6 = SpriteFrame::create("UIresource/hebing6.png", Rect(0, 0, 220, 69));
    animationFrames.pushBack(frame1);
    animationFrames.pushBack(frame2);
    animationFrames.pushBack(frame3);
    animationFrames.pushBack(frame4);
    animationFrames.pushBack(frame5);
    animationFrames.pushBack(frame6);
    auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.2f); // 0.2秒为每帧的持续时间  

    auto sprite = cocos2d::Sprite::createWithSpriteFrame(animationFrames.at(0));

    sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    sprite->setPosition(visibleSize.width / 2.5 + visibleSize.width * 0.139, visibleSize.height / 2 );
    this->addChild(sprite); // 添加到场景  

    // 4. 使用动画播放  
    auto animate = cocos2d::Animate::create(animation);
    auto repeat = Repeat::create ( animate , 3 );  // 动画重复3次
    // 在动画完成后让精灵透明
    auto fadeOut = FadeOut::create(1.0f); // 1.0秒逐渐消失
    auto sequence1 = Sequence::create(repeat, fadeOut, nullptr); // 动画完成后执行FadeOut
    auto animateSequence = Sequence::create(
        sequence1,
        CallFunc::create([this, sprite]() {
            // 确保在动画结束后仍保持在中心位置  
            auto visibleSize = Director::getInstance()->getVisibleSize();
            sprite->setPosition(visibleSize.width / 2.5 + visibleSize.width * 0.139, visibleSize.height / 2); // 确定精灵位置在原处  
            onAnimationComplete();
            }),
        nullptr
    );
    sprite->setScale(3.0f);  // 设置整个动画的缩放
    sprite->runAction(animateSequence); // 播放动画   
}

void BeginScene::onAnimationComplete()
{
    Director::getInstance()->replaceScene(NextScene::create());
}

/////////////////////
//以下为NextScene实现部分，用于实现紧接上部分、连接主菜单的动画效果
bool NextScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 初始动画播放完后，切换此动画
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255),
        visibleSize.width,
        visibleSize.height);
    this->addChild(layer, 5);
    // 使用 fadeIn 动画，使层从透明到完全不透明
    layer->runAction(cocos2d::FadeTo::create(2.0f, 0)); // 2秒内从透明到完全不透明
    addLogo_sec  (visibleSize , origin);
    cloudsAni ( 1.0f );
    this->schedule ( [this]( float dt ) {
        cloudsAni ( dt );
     } , 20.0f , "create_sprite_key" );
    addfirstscene(visibleSize , origin);
    birdfly();
    return true;
}

void NextScene::addfirstscene(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin)
{
    //添加背景
    auto background = Sprite::create ( "UIresource/background2.png" );
    if (background) {
        /*
        float scaleX = visibleSize.width / background->getContentSize ().width;
        float scaleY = visibleSize.height / background->getContentSize ().height;
        float scaleFactor = std::max ( scaleX , scaleY );
        background->setScale ( scaleFactor );
        background->setPosition ( Vec2 ( visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y ) );
        */
        background->setContentSize ( Size ( visibleSize.width , visibleSize.height * 2 ) );
        background->setPosition    ( Vec2 ( visibleSize.width / 2 + origin.x , origin.y + visibleSize.height ) );
        this->addChild ( background , 0 );
    }
    else {
        problemLoading ( "'background.png'" );
    }

    auto mountain1 = Sprite::create("UIresource/mountainfront.png");
    mountain1->setTag ( 101 );
    auto mountain2 = Sprite::create("UIresource/mountainbehind.png");
    mountain2->setTag ( 102 );
    auto treeleft  = Sprite::create("UIresource/treeleft.png");
    treeleft->setTag (  103 );
    auto treeright = Sprite::create("UIresource/treeright.png");
    treeright->setTag ( 104 );
    if (mountain1) {
        // 获取精灵的原始尺寸
        Size spriteSize = mountain1->getContentSize();

        // 计算缩放比例
        float scaleX = visibleSize.width / spriteSize.width; // 根据屏幕宽度和精灵宽度计算水平缩放比例
        float scaleY = scaleX; // 保持长宽比不变，因此Y轴的缩放比例等于X轴的缩放比例

        // 根据计算出的比例设置精灵的缩放
        mountain1->setScale(2 * scaleX); // 或者使用 setScale(scaleX, scaleY);
        mountain1->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.25));
        this->addChild(mountain1, 3);
    }
    else {
        problemLoading("'mountain1.png'");
    }
    if (mountain2) {
        Size spriteSize = mountain2->getContentSize();

        // 计算缩放比例
        float scaleX = visibleSize.width / spriteSize.width; // 根据屏幕宽度和精灵宽度计算水平缩放比例
        float scaleY = scaleX; // 保持长宽比不变，因此Y轴的缩放比例等于X轴的缩放比例

        // 根据计算出的比例设置精灵的缩放
        mountain2->setScale(2 * scaleX);
        mountain2->setPosition(Vec2(visibleSize.width / 2 + origin.x - visibleSize.width * 0.05, origin.y + visibleSize.height * 0.35));
        this->addChild(mountain2, 2);
    }
    else {
        problemLoading("'mountain2.png'");
    }
    if (treeleft) {
        Size spriteSize = treeleft->getContentSize();

        // 计算缩放比例
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / spriteSize.width;
        float scaleY = maxHeight / spriteSize.height;
        // 使用 setScale 来缩放图片
        treeleft->setScale(std::min(scaleX, scaleY));  // 保持宽高比
        // 设置锚点为左下角
        treeleft->setAnchorPoint(Vec2(0, 0));
        // 将精灵的位置设置为屏幕左下角
        treeleft->setPosition(Vec2(0, 0));
        this->addChild(treeleft, 4);
    }
    else {
        problemLoading("'treeleft.png'");
    }
    if (treeright) {
        Size spriteSize = treeright->getContentSize();

        // 计算缩放比例
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / spriteSize.width;
        float scaleY = maxHeight / spriteSize.height;
        // 使用 setScale 来缩放图片
        treeright->setScale(std::min(scaleX, scaleY));  // 保持宽高比
        // 设置锚点为右下角
        treeright->setAnchorPoint(Vec2(1, 0));
        // 将精灵的位置设置为屏幕右下角
        treeright->setPosition(Vec2(visibleSize.width + origin.x , 0));
        this->addChild(treeright, 4);
    }
    else {
        problemLoading("'treeright.png'");
    }
}

void NextScene::birdfly()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 创建精灵帧
    Vector<cocos2d::SpriteFrame*> animFrames;

    // 加载4张图片
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly1.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly2.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly3.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly4.png", cocos2d::Rect(0, 0, 26, 26)));

    // 创建动画
    auto animation1 = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);  // 每帧0.2秒
    auto animation2 = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);  // 每帧0.2秒
    // 创建动画对象
    auto animate1 = cocos2d::Animate::create(animation1);
    auto animate2 = cocos2d::Animate::create(animation2);
    // 计算重复的次数，使总时间符合要求
    float totalDuration = 4.5f;  // 设定总时间
    int repeatCount1 = totalDuration / animation1->getDuration();
    auto repeatedAction1 = Repeat::create(animate1, repeatCount1);
    int repeatCount2 = totalDuration / animation2->getDuration();
    auto repeatedAction2 = Repeat::create(animate2, repeatCount2);
    // 创建移动动作
    auto moveAction1 = MoveBy::create(5.0f, Vec2(-visibleSize.width / 2, 0)); // 2秒内沿X轴移动
    auto moveAction2 = MoveBy::create(5.0f, Vec2(-visibleSize.width / 2, 0)); // 2秒内沿X轴移动
    // 创建精灵并播放动画
     auto sprite1 = cocos2d::Sprite::createWithSpriteFrame(animFrames.at(0));
     auto sprite2 = cocos2d::Sprite::createWithSpriteFrame(animFrames.at(0));
     sprite1->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 3));  // 设置精灵位置
     sprite2->setPosition(cocos2d::Vec2(visibleSize.width / 1.8, visibleSize.height / 3.2));  // 设置精灵位置
     // 同时执行动画和移动
     auto spawnAction1 = Spawn::create(repeatedAction1, moveAction1, nullptr);
     auto spawnAction2 = Spawn::create(repeatedAction2, moveAction2, nullptr);
     auto sequence = Sequence::create(
         spawnAction1,
         //鸟飞出屏幕后开始进行转场
         CallFunc::create([this, sprite1]() {
             scenechangedown();
              }),
         nullptr);
     sprite1->runAction(sequence); // 循环播放动画
     sprite2->runAction(spawnAction2);  // 循环播放动画
    // 将精灵添加到场景中
    sprite1->setScale(2.0f);  // 设置整个动画的缩放
    sprite2->setScale(2.0f);  // 设置整个动画的缩放
    this->addChild(sprite1, 3);
    this->addChild(sprite2, 3);
}

void NextScene::addLogo_sec ( const Size& visibleSize , const Vec2& origin )
{
    auto logo = Sprite::create ( "UIresource/title.png" );
    if (logo) {
        Size logoSize = logo->getContentSize ();
        float maxWidth = visibleSize.width * 0.7f;
        float maxHeight = visibleSize.height * 0.7f;
        float scaleX = maxWidth / logoSize.width;
        float scaleY = maxHeight / logoSize.height;
        logo->setScale ( std::min ( scaleX , scaleY ) );
        logo->setPosition( Vec2 ( visibleSize.width / 2 + origin.x , visibleSize.height / 4 * 2.5 + origin.y + visibleSize.height) );
        this->addChild ( logo , 2 );
    }
    else {
        problemLoading ( "'title.png'" );
    }
}
void NextScene::cloudsAni ( float dt )
{
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    auto cloud0 = Sprite::create ( "UIresource/Cloud.png" );
    auto clouds = Sprite::create ( "UIresource/Clouds.png" );
    if (cloud0) {
        Size spriteSize = cloud0->getContentSize ();
        // 计算缩放比例
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / spriteSize.width;
        float scaleY = maxHeight / spriteSize.height;
        // 使用 setScale 来缩放图片
        cloud0->setScale ( std::min ( scaleX , scaleY ) );  // 保持宽高比
        // 设置锚点为右下角
        cloud0->setAnchorPoint ( Vec2 ( 1 , 0 ) );
        // 将精灵的位置设置为屏幕右下角靠上一点靠右一点
        cloud0->setPosition ( Vec2 ( visibleSize.width * 1.5 + origin.x , visibleSize.height / 1.8 + origin.y ) );
        this->addChild ( cloud0 , 1 );
    }
    else {
        problemLoading ( "'Cloud.png'" );
    }
    if (clouds) {
        Size cloudsSize = clouds->getContentSize ();
        float maxWidth = visibleSize.width * 1.1f;
        float maxHeight = visibleSize.height * 1.1f;
        float scaleX = maxWidth / cloudsSize.width;
        float scaleY = maxHeight / cloudsSize.height;
        clouds->setScale ( std::min ( scaleX , scaleY ) );
        cloud0->setAnchorPoint ( Vec2 ( 1 , 0 ) );
        clouds->setPosition ( Vec2 ( visibleSize.width * 1.8 + origin.x , visibleSize.height * 0.8 + origin.y + visibleSize.height ) );
        this->addChild ( clouds , 1 );
    }
    else {
        problemLoading ( "'Clouds.png'" );
    }

    // 计算精灵移动的目标位置（屏幕的左侧）
    auto moveTo_0 = cocos2d::MoveTo::create ( 50.0f , cocos2d::Vec2 ( 0 , cloud0->getPosition ().y ) );
    auto moveTo_s = cocos2d::MoveTo::create ( 50.0f , cocos2d::Vec2 ( -visibleSize.width * 0.6 , clouds->getPosition ().y ) );
    cloud0->runAction ( cocos2d::RepeatForever::create ( moveTo_0 ) );
    clouds->runAction ( cocos2d::RepeatForever::create ( moveTo_s ) );
}
void NextScene::scenechangedown ()
{
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    // 获取当前运行的场景
    auto scene = Director::getInstance ()->getRunningScene ();

    // 定义向下移动的位移量，需要向下移动整个可视区域
    Vec2 moveDistance = Vec2 ( 0 , -visibleSize.height );

    // 创建 MoveBy 动作，设置时间为 8 秒
    auto moveAction = MoveBy::create ( 8.0f , moveDistance );


    auto mountain1 = this->getChildByTag ( 101 );
    auto mountain2 = this->getChildByTag ( 102 );
    auto treeleft = this->getChildByTag  ( 103 );
    auto treeright = this->getChildByTag ( 104 );
    auto moveDown1 = cocos2d::MoveBy::create ( 10.0f , cocos2d::Vec2 ( 0 , -visibleSize.height * 3 ) ); // 向下移动
    auto moveDown2 = cocos2d::MoveBy::create ( 20.0f ,cocos2d::Vec2 ( 0 , -visibleSize.height * 3 ) );  // 向下移动
    auto moveDown3 = cocos2d::MoveBy::create ( 8.0f , cocos2d::Vec2 ( 0 , -visibleSize.height * 3 ) );  // 向下移动
    auto moveDown4 = cocos2d::MoveBy::create ( 8.0f , cocos2d::Vec2 ( 0 , -visibleSize.height * 3 ) );  // 向下移动

    scene    ->runAction ( moveAction);
    mountain1->runAction ( moveDown1 );
    mountain2->runAction ( moveDown2 );
    treeleft ->runAction ( moveDown3 );
    treeright->runAction ( moveDown4 );

    // 创建菜单项  
    auto BeginItem = createMenuItem ( "UIresource/start1.png" , "UIresource/start1.png" , CC_CALLBACK_1 ( NextScene::menuNewCallback , this ) , origin , -visibleSize.width * 0.338 );
    auto LoadItem = createMenuItem ( "UIresource/load1.png" , "UIresource/load1.png" , CC_CALLBACK_1 ( NextScene::menuNewCallback , this ) , origin , -visibleSize.width * 0.113 );
    auto coopItem = createMenuItem ( "UIresource/coop1.png" , "UIresource/coop1.png" , CC_CALLBACK_1 ( NextScene::menuNewCallback , this ) , origin , visibleSize.width * 0.113 );
    auto closeItem = createMenuItem ( "UIresource/quit1.png" , "UIresource/quit1.png" , CC_CALLBACK_1 ( NextScene::menuCloseCallback , this ) , origin , visibleSize.width * 0.338 );

    // 使用延时和顺序动画来显示菜单项
    auto delay0 = DelayTime::create ( 5.0f ); // 5秒延迟
    auto delay1 = DelayTime::create ( 1.0f ); // 1秒延迟
    auto delay2 = DelayTime::create ( 1.0f ); // 1秒延迟
    auto delay3 = DelayTime::create ( 1.0f ); // 1秒延迟

    auto showBeginItem = FadeIn::create ( 0.5f );  // 开始按钮渐现
    auto showLoadItem  = FadeIn::create ( 0.5f );   // 加载按钮渐现
    auto showCoopItem  = FadeIn::create ( 0.5f );   // 合作按钮渐现
    auto showCloseItem = FadeIn::create ( 0.5f );  // 退出按钮渐现

    auto sequence1 = Sequence::create ( delay0 , showBeginItem , nullptr );                             // BeginItem 最先渐显
    auto sequence2 = Sequence::create ( delay0 , delay1 , showLoadItem , nullptr );                     // LoadItem 在等待 1 秒后渐显
    auto sequence3 = Sequence::create ( delay0 , delay1 , delay2 , showCoopItem , nullptr );            // CoopItem 在等待 2 秒后渐显
    auto sequence4 = Sequence::create ( delay0 , delay1 , delay2 , delay3 , showCloseItem , nullptr );  // CloseItem 在等待 3 秒后渐显

    BeginItem->runAction ( sequence1->clone () );
    LoadItem->runAction  ( sequence2->clone () );
    coopItem->runAction  ( sequence3->clone () );
    closeItem->runAction ( sequence4->clone () );

    // 创建菜单  
    auto menu = Menu::create ( BeginItem , LoadItem , coopItem , closeItem , nullptr );
    menu->setPosition ( Vec2 ( 0 , visibleSize.height ) );
    this->addChild ( menu , 3 );

    // 添加鼠标监听器  
    addMouseListener ( BeginItem , LoadItem , coopItem , closeItem );
}


MenuItemImage* NextScene::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const Vec2& origin, float offsetX)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (item) {
        Size itemSize = item->getContentSize();
        // 获取屏幕可视区域的大小
        auto visibleSize = Director::getInstance()->getVisibleSize();
        // 设置图标的缩放比率
        float maxWidth = visibleSize.width * 0.2f;
        float maxHeight = visibleSize.height * 0.2f;
        float scaleX = maxWidth / itemSize.width ;
        float scaleY = maxHeight / itemSize.height ;
        // 使用 setScale 来缩放图片
        item->setScale(std::min(scaleX, scaleY));  // 保持宽高比
        float x = origin.x + visibleSize.width / 2 + offsetX;
        float y = origin.y + visibleSize.height / 720 * 100;
        item->setPosition(Vec2(x, y));
        item->setOpacity(0);//初始透明
    }
    else {
        problemLoading(normalImage.c_str());
    }
    return item;
}

void NextScene::addMouseListener(MenuItemImage* BeginItem, MenuItemImage* LoadItem, MenuItemImage* coopItem, MenuItemImage* closeItem)
{
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this, BeginItem, LoadItem, coopItem, closeItem](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());

        updateMenuItem(BeginItem, mousePos, "UIresource/start1.png", "UIresource/start2.png");
        updateMenuItem(LoadItem,  mousePos, "UIresource/load1.png" , "UIresource/load2.png" );
        updateMenuItem(coopItem,  mousePos, "UIresource/coop1.png" , "UIresource/coop2.png" );
        updateMenuItem(closeItem, mousePos, "UIresource/quit1.png" , "UIresource/quit2.png" );
        };
    listener->onMouseDown = [this , BeginItem , LoadItem , coopItem , closeItem]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        if (BeginItem->getBoundingBox ().containsPoint ( mousePos )) {
            menuNewCallback ( BeginItem );  // 如果点击的是 BeginItem，则调用回调
        }
        else if (LoadItem->getBoundingBox ().containsPoint ( mousePos )) {
            menuNewCallback ( LoadItem );  // 如果点击的是 LoadItem，则调用回调
        }
        else if (coopItem->getBoundingBox ().containsPoint ( mousePos )) {
            menuNewCallback ( coopItem );  // 如果点击的是 coopItem，则调用回调
        }
        else if (closeItem->getBoundingBox ().containsPoint ( mousePos )) {
            menuCloseCallback( closeItem );  // 如果点击的是 closeItem，则调用回调
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void NextScene::updateMenuItem(MenuItemImage* item, const Vec2& mousePos, const std::string& normalImage, const std::string& selectedImage)
{
    Size itemSize = item->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 设置图标的缩放比率
    float maxWidth = visibleSize.width * 0.2f;
    float maxHeight = visibleSize.height * 0.2f;
    float scaleX = maxWidth / itemSize.width;
    float scaleY = maxHeight / itemSize.height;

    if (item->getBoundingBox().containsPoint(mousePos)) {
        item->setNormalImage(cocos2d::Sprite::create(selectedImage));
        item->setSelectedImage(cocos2d::Sprite::create(selectedImage));
        item->setScale(1.2* std::min(scaleX, scaleY));
    }
    else {
        item->setNormalImage(cocos2d::Sprite::create(normalImage));
        item->setSelectedImage(cocos2d::Sprite::create(normalImage));
        item->setScale(std::min(scaleX, scaleY));
    }
}

// 跳转到新场景  
void NextScene::menuNewCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(Town::create()); // 进入到主地图  
}

void NextScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}