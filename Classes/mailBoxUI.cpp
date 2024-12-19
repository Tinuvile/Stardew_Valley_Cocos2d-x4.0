 #include "ui/CocosGUI.h"  
#include "mailBoxUI.h"
#include "DetailedtaskUI.h"

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void mailBoxUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    Leftboundary = 637.0f;
    rightboundary = 960.0f;
    upperboundary = 777.0f;
    lowerboundary = 500.0f;
    if (x <= Leftboundary) {
        x = Leftboundary;
    }
    else if (x >= rightboundary) {
        x = rightboundary;
    }
    else {
        x = position.x;
    }

    if (y >= upperboundary) {
        y = upperboundary;
    }
    else if (y <= lowerboundary) {
        y = lowerboundary;
    }
    else {
        y = position.y;
    }
}

void mailBoxUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 10 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    //大框架
    auto mail = Sprite::create ( "UIresource/xinxiang/renwu2.png" );
    if (mail == nullptr)
    {
        problemLoading ( "'renwu2.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = mail->getContentSize ().width;
        float originalHeight = mail->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        mail->setScale ( scale);
        mail->setPosition ( Vec2 ( currentx , currenty ) );

        this->addChild ( mail , 1 );
    }
}

void mailBoxUI::close () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto closeIcon = Sprite::create ( "npc/bacha.png" );
    if (closeIcon == nullptr)
    {
        problemLoading ( "'npc/bacha.png'" );
    }
    else
    {
        float originalWidth = closeIcon->getContentSize ().width;
        float originalHeight = closeIcon->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        closeIcon->setScale ( scale / 20.5 );
        closeIcon->setPosition ( Vec2 ( currentx + visibleSize.width * 0.45 , currenty + visibleSize.height * 0.4 ) );

        this->addChild ( closeIcon , 1 );
        auto listener = EventListenerMouse::create ();
        listener->onMouseMove = [this , closeIcon , scale]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            if (closeIcon->getBoundingBox ().containsPoint ( mousePos ))
            {
                closeIcon->setScale ( scale / 20.5 * 1.2 );
            }
            else
                closeIcon->setScale ( scale / 20.5 );
            };
        listener->onMouseDown = [this , closeIcon]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            CCLOG ( "%f %f" , mousePos.x , mousePos.y );
            if (closeIcon->getBoundingBox ().containsPoint ( mousePos )) {
                this->removeFromParent ();
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , closeIcon );
    }
}

void mailBoxUI::taskDisplay ( TaskManagement& taskManager ) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //创建 ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // 设置为垂直滚动
    scrollView->setContentSize ( Size ( 1630 , 600 ) ); // 设置ScrollView 宽度，高度
    scrollView->setPosition ( Vec2 ( currentx - visibleSize.width * 0.589 , currenty - visibleSize.height * 0.2 ) ); // 设置位置
    scrollView->setBounceEnabled ( true ); // 启用弹性效果
    scrollView->setScrollBarEnabled ( false );    // 禁用垂直和水平滑动条

    // 计算总高度  
    float totalItemHeight = 0;
    const int itemCount = 5; // 任务数量  
    const float itemHeight = 500; // 每个高度  
    totalItemHeight = itemCount * itemHeight; // 计算总高度  

    // 设置内部容器的大小  
    scrollView->setInnerContainerSize ( Size ( 1630 , totalItemHeight ) ); // 设置内部容器的大小

    // 监听鼠标滚轮事件
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [scrollView]( cocos2d::EventMouse* event ) {
        // 获取鼠标滚轮的偏移量  
        float scrollDelta = event->getScrollY ();

        // 获取当前的 innerContainer  
        auto innerContainer = scrollView->getInnerContainer ();

        // 计算新的 Y 位置  
        float currentPosY = innerContainer->getPositionY ();
        float newPosY = currentPosY + scrollDelta * 100; // 调整灵敏度  

        // 限制滚动的上下边界  
        float lowerLimit = scrollView->getContentSize ().height - innerContainer->getContentSize ().height;
        float upperLimit = -1400;

        //CCLOG ( "currentPosY: %f, newPosY: %f, lowerLimit: %f, upperLimit: %f" , currentPosY , newPosY , lowerLimit , upperLimit );

        // 使用 std::max 和 std::min 确保 newPosY 在边界内  
        newPosY = std::max ( newPosY , lowerLimit );
        newPosY = std::min ( newPosY , upperLimit );

        // 设置新的位置  
        innerContainer->setPositionY ( newPosY );

        };
    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );

    float offsetY = 0;  // 用来存储任务间的纵向间距
    // 获取所有任务  
    std::vector<TaskManagement::Task> tasks = taskManager.returnTasks ();

    // 创建一个字符串以存储所有任务的信息  
    std::string allTasksInfo;
    for (const auto& task : tasks) {
        //添加框
        auto taskframe = Sprite::create ( "UIresource/SkillTree/background.png" );
        taskframe->setScale ( 1.5f , 0.5f );
        taskframe->setPosition ( Vec2 ( visibleSize.width * 0.6 , 539 + visibleSize.height * 1.4 - offsetY ) );
        scrollView->addChild ( taskframe , 2 );

        // 格式化任务信息  
        std::string taskInfo = "Task_Name: " + task.name ;
        // 创建标签来显示任务信息  
        auto taskMessage = Label::createWithSystemFont ( taskInfo , "fonts/Comic Sans MS.ttf" , 50 );
        taskMessage->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
        taskMessage->setTextColor ( Color4B::BLACK );

        // 设置标签的位置  
        Vec2 visibleSize = Director::getInstance ()->getVisibleSize ();
        taskMessage->setPosition ( Vec2 (visibleSize.x * 0.35 , 539 + visibleSize.y * 1.4 - offsetY ) );

        scrollView->addChild ( taskMessage , 2 );
        auto listener = EventListenerMouse::create ();
        
        listener->onMouseMove = [this , taskframe , scrollView , currenty]( EventMouse* event ) {

            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );

            mousePos = this->convertToNodeSpace ( mousePos );
            Vec2 scrollViewPos = scrollView->getPosition ();

            Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
            Rect itemBoundingBox = taskframe->getBoundingBox ();

            float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
            float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;
            if (mousePos.x >= adjustedPosX - 300 && mousePos.x <= adjustedPosX + itemBoundingBox.size.width  - 300 &&
            mousePos.y >= adjustedPosY + currenty - 250 && mousePos.y <= currenty + adjustedPosY + itemBoundingBox.size.height - 250) {
                taskframe->setTexture ( "UIresource/xinxiang/xuanzhong.png" );
            }
            else {
                taskframe->setTexture ( "UIresource/SkillTree/background.png" );
            }
            };
            
        listener->onMouseDown = [this , taskframe , scrollView , currenty , currentx , task , visibleSize]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );

            Vec2 scrollViewPos = scrollView->getPosition ();

            Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
            Rect itemBoundingBox = taskframe->getBoundingBox ();

            float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
            float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;

            if (mousePos.x >= adjustedPosX - 300 && mousePos.x <= adjustedPosX + itemBoundingBox.size.width - 300 &&
            mousePos.y >= adjustedPosY + currenty - 250 && mousePos.y <= currenty + adjustedPosY + itemBoundingBox.size.height - 250) {
                this->removeFromParent ();
                Scene* currentScene = Director::getInstance ()->getRunningScene ();
                currentScene->addChild ( DetailedtaskUI::create ( task ) , 20 );
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , taskframe );

        // 更新下一个商品的位置偏移量
        offsetY += 350;  // 每个任务间的的间距
    }
    // 将滚动视图添加到Layer中
    this->addChild ( scrollView , 5 );
}

bool mailBoxUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    taskDisplay ( *taskManager );
    close ();
    return true;
}

mailBoxUI* mailBoxUI::create () {
    mailBoxUI* ret = new mailBoxUI ();
    if (ret && ret->init ()) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

