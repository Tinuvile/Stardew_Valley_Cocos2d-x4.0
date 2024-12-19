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
    // ����һ����͸���ĺ�ɫ����
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 10 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );
    //����
    auto mail = Sprite::create ( "UIresource/xinxiang/renwu2.png" );
    if (mail == nullptr)
    {
        problemLoading ( "'renwu2.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = mail->getContentSize ().width;
        float originalHeight = mail->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
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
    //���� ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // ����Ϊ��ֱ����
    scrollView->setContentSize ( Size ( 1630 , 600 ) ); // ����ScrollView ��ȣ��߶�
    scrollView->setPosition ( Vec2 ( currentx - visibleSize.width * 0.589 , currenty - visibleSize.height * 0.2 ) ); // ����λ��
    scrollView->setBounceEnabled ( true ); // ���õ���Ч��
    scrollView->setScrollBarEnabled ( false );    // ���ô�ֱ��ˮƽ������

    // �����ܸ߶�  
    float totalItemHeight = 0;
    const int itemCount = 5; // ��������  
    const float itemHeight = 500; // ÿ���߶�  
    totalItemHeight = itemCount * itemHeight; // �����ܸ߶�  

    // �����ڲ������Ĵ�С  
    scrollView->setInnerContainerSize ( Size ( 1630 , totalItemHeight ) ); // �����ڲ������Ĵ�С

    // �����������¼�
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [scrollView]( cocos2d::EventMouse* event ) {
        // ��ȡ�����ֵ�ƫ����  
        float scrollDelta = event->getScrollY ();

        // ��ȡ��ǰ�� innerContainer  
        auto innerContainer = scrollView->getInnerContainer ();

        // �����µ� Y λ��  
        float currentPosY = innerContainer->getPositionY ();
        float newPosY = currentPosY + scrollDelta * 100; // ����������  

        // ���ƹ��������±߽�  
        float lowerLimit = scrollView->getContentSize ().height - innerContainer->getContentSize ().height;
        float upperLimit = -1400;

        //CCLOG ( "currentPosY: %f, newPosY: %f, lowerLimit: %f, upperLimit: %f" , currentPosY , newPosY , lowerLimit , upperLimit );

        // ʹ�� std::max �� std::min ȷ�� newPosY �ڱ߽���  
        newPosY = std::max ( newPosY , lowerLimit );
        newPosY = std::min ( newPosY , upperLimit );

        // �����µ�λ��  
        innerContainer->setPositionY ( newPosY );

        };
    // ����������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );

    float offsetY = 0;  // �����洢������������
    // ��ȡ��������  
    std::vector<TaskManagement::Task> tasks = taskManager.returnTasks ();

    // ����һ���ַ����Դ洢�����������Ϣ  
    std::string allTasksInfo;
    for (const auto& task : tasks) {
        //��ӿ�
        auto taskframe = Sprite::create ( "UIresource/SkillTree/background.png" );
        taskframe->setScale ( 1.5f , 0.5f );
        taskframe->setPosition ( Vec2 ( visibleSize.width * 0.6 , 539 + visibleSize.height * 1.4 - offsetY ) );
        scrollView->addChild ( taskframe , 2 );

        // ��ʽ��������Ϣ  
        std::string taskInfo = "Task_Name: " + task.name ;
        // ������ǩ����ʾ������Ϣ  
        auto taskMessage = Label::createWithSystemFont ( taskInfo , "fonts/Comic Sans MS.ttf" , 50 );
        taskMessage->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
        taskMessage->setTextColor ( Color4B::BLACK );

        // ���ñ�ǩ��λ��  
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

        // ������һ����Ʒ��λ��ƫ����
        offsetY += 350;  // ÿ�������ĵļ��
    }
    // ��������ͼ��ӵ�Layer��
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

