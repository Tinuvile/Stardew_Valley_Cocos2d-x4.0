#include "ui/CocosGUI.h"  
#include "DetailedtaskUI.h"
#include "mailBoxUI.h"

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void DetailedtaskUI::updateCoordinate ( float& x , float& y ) {
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

void DetailedtaskUI::backgroundcreate () {
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
        mail->setScale ( scale );
        mail->setPosition ( Vec2 ( currentx , currenty ) );

        this->addChild ( mail , 1 );
    }
}

void DetailedtaskUI::close () {
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
                Scene* currentScene = Director::getInstance ()->getRunningScene ();
                currentScene->addChild ( mailBoxUI::create () , 20 );
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , closeIcon );
    }
}

void DetailedtaskUI::displayTask ( TaskManagement::Task task ) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );

    // ����һ���ַ����Դ洢�����������Ϣ  
    std::string allTasksInfo;

    // ��ʽ��������Ϣ  
    std::string taskInfo = "------------------------\n";
    taskInfo += "Task Name: " + task.name + "\n";
    taskInfo += "Task Type: " + std::to_string ( task.type ) + "\n";
    if (task.type == TaskManagement::NPC_TASK) {
        taskInfo += "Release NPC: " + task.npcName + "\n";
    }
    taskInfo += "Reward coins: " + std::to_string ( task.rewardCoins ) + "\n";
    taskInfo += "Enhance favorability: " + std::to_string ( task.relationshipPoints ) + "\n";
    taskInfo += "------------------------\n";

    allTasksInfo += taskInfo; // ��ÿ��������Ϣ��ӵ����ַ�����  

    // ������ǩ����ʾ������Ϣ  
    auto taskMessage = Label::createWithSystemFont ( allTasksInfo , "fonts/Comic Sans MS.ttf" , 80 );
    taskMessage->setTextColor ( Color4B::BLACK );

    // ���ñ�ǩ��λ��  
    Vec2 visibleSize = Director::getInstance ()->getVisibleSize ();
    taskMessage->setPosition ( Vec2 ( currentx , currenty ) );

    // ����ǩ��ӵ�Layer��  
    this->addChild ( taskMessage , 2 );
}

bool DetailedtaskUI::init ( TaskManagement::Task task ) {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    displayTask ( task );
    close ();
    return true;
}

DetailedtaskUI* DetailedtaskUI::create ( TaskManagement::Task task ) {
    DetailedtaskUI* ret = new DetailedtaskUI ();
    if (ret && ret->init (task )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

