 #include "ui/CocosGUI.h"
#include "mailBoxUI.h"
#include "DetailedtaskUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Components/DarkOverlay.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"

USING_NS_CC;


void mailBoxUI::backgroundcreate () {
    // 使用UIConfig获取调整后的坐标
    auto config = UIConfig::getInstance();
    auto theme = UITheme::getInstance();
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate("farm", playerPos);

    // 使用UI文件夹下的darkOverlay创建黑幕
    auto darkOverlay = DarkOverlay::create ("farm");
    this->addChild ( darkOverlay , 0 );
	CCLOG ( "DarkOverlay created in mailBoxUI" );
    //邮件背景 - 使用Builder创建
    auto mail = SpriteBuilder()
        .setTexture (UIConfig::UIResources::MAILBOX_IMAGE)
        .setAutoScale ( 1.0f )
        .setPosition ( adjustedPos )
        .setZOrder ( 1 )
        .addToParent ( this )
        .build ();
	CCLOG ( "MailBox background created" );
}

void mailBoxUI::close () {
    // 使用UIConfig获取调整后的坐标
    auto config = UIConfig::getInstance();
    auto theme = UITheme::getInstance();
    auto visibleSize = theme->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate("farm", playerPos);

    //关闭按钮 - 使用Builder创建
    auto closeIcon = SpriteBuilder()
        .setTexture ( "npc/bacha.png" )
        .setAutoScale ( 20.5f )
        .setPosition ( Vec2(adjustedPos.x + visibleSize.width * 0.45f, adjustedPos.y + visibleSize.height * 0.4f) )
        .setZOrder ( 1 )
        .setClickCallback ( [this](Sprite* sprite) {
            this->removeFromParent ();
        } )
        .setHoverEffect ( 1.2f )
        .build ();
}

void mailBoxUI::taskDisplay ( TaskManagement& taskManager ) {
    // 使用UIConfig获取调整后的坐标
    auto config = UIConfig::getInstance();
    auto theme = UITheme::getInstance();
    auto visibleSize = theme->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate("farm", playerPos);

    // 创建ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // 设置为垂直滚动
    scrollView->setContentSize ( Size ( 1630 , 600 ) ); // 设置ScrollView的宽度、高度
    scrollView->setPosition ( Vec2 ( adjustedPos.x - visibleSize.width * 0.589 , adjustedPos.y - visibleSize.height * 0.2 ) ); // 设置位置
    scrollView->setBounceEnabled ( true ); // 设置回弹效果
    scrollView->setScrollBarEnabled ( false );    // 关掉垂直水平滚动条

    // 计算总高度
    float totalItemHeight = 0;
    const int itemCount = 5; // 设置数量
    const float itemHeight = 500; // 每项高度
    totalItemHeight = itemCount * itemHeight; // 计算总高度

    // 设置内部容器的大小
    scrollView->setInnerContainerSize ( Size ( 1630 , totalItemHeight ) ); // 设置内部容器的大小

    // 添加鼠标滚轮事件
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [scrollView]( cocos2d::EventMouse* event ) {
        // 获取滚轮的偏移量
        float scrollDelta = event->getScrollY ();

        // 获取当前的 innerContainer
        auto innerContainer = scrollView->getInnerContainer ();

        // 计算新的 Y 位置
        float currentPosY = innerContainer->getPositionY ();
        float newPosY = currentPosY + scrollDelta * 100; // 计算偏移

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
    // 将事件监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );

    float offsetY = 0;  // 用于存储每个任务项的偏移量
    // 获取任务列表
    std::vector<TaskManagement::Task> tasks = taskManager.returnTasks ();

        for (const auto& task : tasks) {
        //任务框 - 使用Builder创建，使用相对位置
        auto taskframe = SpriteBuilder()
            .setTexture ( "UIresource/SkillTree/background.png" )
            .setScale ( 1.5f , 0.5f )
            .setPosition ( Vec2 ( adjustedPos.x + 180 , adjustedPos.y + 539 - offsetY ) )
            .setZOrder ( 2 )
            .addToParent ( scrollView )
            .build ();

        // 使用Builder创建任务标签
        std::string taskInfo = "Task_Name: " + task.name ;
        auto taskMessage = LabelBuilder()
            .setText ( taskInfo )
            .setFont ( "fonts/Comic Sans MS.ttf" , 50 )
            .setColor ( Color4B::BLACK )
            .setAnchorPoint ( 0 , 0.5 )
            .setPosition ( Vec2 (adjustedPos.x + 180 , adjustedPos.y + 539 - offsetY ) )
            .setZOrder ( 2 )
            .addToParent ( scrollView )
            .build ();

        // 设置事件监听器
        auto listener = EventListenerMouse::create ();

        listener->onMouseMove = [this , taskframe , scrollView , adjustedPos]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            Vec2 scrollViewPos = scrollView->getPosition ();
            Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
            Rect itemBoundingBox = taskframe->getBoundingBox ();

            float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
            float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;
            if (mousePos.x >= adjustedPosX - 300 && mousePos.x <= adjustedPosX + itemBoundingBox.size.width  - 300 &&
            mousePos.y >= adjustedPosY + adjustedPos.y - 250 && mousePos.y <= adjustedPos.y + adjustedPosY + itemBoundingBox.size.height - 250) {
                taskframe->setTexture ( "UIresource/xinxiang/xuanzhong.png" );
            }
            else {
                taskframe->setTexture ( "UIresource/SkillTree/background.png" );
            }
        };

        listener->onMouseDown = [this , taskframe , scrollView , adjustedPos , task]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );

            Vec2 scrollViewPos = scrollView->getPosition ();
            Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
            Rect itemBoundingBox = taskframe->getBoundingBox ();

            float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
            float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;

            if (mousePos.x >= adjustedPosX - 300 && mousePos.x <= adjustedPosX + itemBoundingBox.size.width - 300 &&
            mousePos.y >= adjustedPosY + adjustedPos.y - 250 && mousePos.y <= adjustedPos.y + adjustedPosY + itemBoundingBox.size.height - 250) {
                this->removeFromParent ();
                Scene* currentScene = Director::getInstance ()->getRunningScene ();
                currentScene->addChild ( DetailedtaskUI::create ( task ) , 20 );
            }
        };

        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , taskframe );

        // 增加下一个任务项的位置偏移量
        offsetY += 350;  // 每个任务项的间距
    }
    // 将滚动视图添加到Layer中
    this->addChild ( scrollView , 5 );
}

bool mailBoxUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    //taskDisplay ( *taskManager );
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

