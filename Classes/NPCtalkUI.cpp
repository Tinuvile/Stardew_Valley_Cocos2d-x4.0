// InventoryUI.cpp  
#include "NPCtalkUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"
#include "NPC.h"

extern Player* player1;
extern NpcRelationship* npc_relationship;

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void NPCtalkUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    if (SceneName  == "Town") {
        Leftboundary = -170.0f;
        rightboundary = 1773.0f;
        upperboundary = 1498.0f;
        lowerboundary = -222.0f;
    }
    else if (SceneName == "Cave") {
        Leftboundary = 786.0f;
        rightboundary = 817.0f;
        upperboundary = 808.0f;
        lowerboundary = 460.0f;
    }
    else if (SceneName == "Beach") {
        Leftboundary = -315.0f;
        rightboundary = 20000.0f;
        upperboundary = 920.0f;
        lowerboundary = 360.0f;
    }
    else if (SceneName == "Forest") {
        Leftboundary = -600.0f;
        rightboundary = 2197.0f;
        upperboundary = 2200.0f;
        lowerboundary = -850.0f;
    }
    else if (SceneName == "farm") {
        Leftboundary = 637.0f;
        rightboundary = 960.0f;
        upperboundary = 777.0f;
        lowerboundary = 500.0f;
    }
    else if (SceneName == "Barn") {
        Leftboundary = 805.0f;
        rightboundary = 805.0f;
        upperboundary = 569.0f;
        lowerboundary = 569.0f;
    }
    else if (SceneName == "Myhouse") {
        Leftboundary = 800.0f;
        rightboundary = 800.0f;
        upperboundary = 580.0f;
        lowerboundary = 580.0f;
    }
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

void NPCtalkUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    CCLOG ( "%f %f" , currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( position - visibleSize );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    //对话框
    auto dialogBox = Sprite::create ( "npc/kuang.png" );
    if (dialogBox == nullptr)
    {
        problemLoading ( "'npc/kuang.png'" );
    }
    else
    {
        float originalWidth = dialogBox->getContentSize ().width;
        float originalHeight = dialogBox->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        dialogBox->setScale ( scale * 0.9 );
        dialogBox->setPosition ( Vec2 ( currentx , currenty - visibleSize.height * 0.27 ) );

        this->addChild ( dialogBox , 1 );
    }
    //头像
    std::string photo;
    if (Season == "Spring" || Season == "Autumn") {
        photo = getNPCportraits ( npc->GetName () , "Normal" );
    }
    else {
        photo = getNPCportraits ( npc->GetName () , Season + "Normal" );
    }
    auto characterPhoto = Sprite::create ( photo );

    float originalWidth = characterPhoto->getContentSize ().width;
    float originalHeight = characterPhoto->getContentSize ().height;
    float scaleX = visibleSize.width / originalWidth;
    float scaleY = visibleSize.height / originalHeight;
    float scale = std::min ( scaleX , scaleY );
    characterPhoto->setScale ( scale * 0.25 );
    characterPhoto->setPosition ( Vec2 ( currentx + visibleSize.width * 0.27 , currenty - visibleSize.height * 0.233 ) );

    this->addChild ( characterPhoto , 2 );

    //姓名
    std::string name = npc->GetName ();
    auto NameLabel =Label::createWithSystemFont ( name , "fonts/Comic Sans MS.ttf" , 40 );
    NameLabel->setTextColor ( cocos2d::Color4B::BLACK );
    NameLabel->setPosition ( Vec2 ( currentx + visibleSize.width * 0.26 , currenty - visibleSize.height * 0.4 ) );
    this->addChild ( NameLabel , 2 );
}

//对话选中框添加
void NPCtalkUI::SelectedBox () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto Selectedbox1 = Sprite::create ( "npc/xuanzhongkuang.png" );
    auto Selectedbox2 = Sprite::create ( "npc/xuanzhongkuang.png" );
    auto Selectedbox3 = Sprite::create ( "npc/xuanzhongkuang.png" );
    auto Selectedbox4 = Sprite::create ( "npc/xuanzhongkuang.png" );
    if (Selectedbox1 == nullptr)
    {
        problemLoading ( "'npc/xuanzhongkuang.png'" );
    }
    else
    {
        float originalWidth = Selectedbox1->getContentSize ().width;
        float originalHeight = Selectedbox1->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        Selectedbox1->setScale ( scale * 0.5 );
        //差是0.064，第一个位置在Selectedbox1的Y基础上加0.064
        Selectedbox1->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.21 ) );
        Selectedbox2->setScale ( scale * 0.5 );
        Selectedbox2->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.274 ) );
        Selectedbox3->setScale ( scale * 0.5 );
        Selectedbox3->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.338 ) );
        Selectedbox4->setScale ( scale * 0.5 );
        Selectedbox4->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.402 ) );

        this->addChild ( Selectedbox1 , 0 );
        this->addChild ( Selectedbox2 , 0 );
        this->addChild ( Selectedbox3 , 0 );
        this->addChild ( Selectedbox4 , 0 );

        // NPC 对话添加
        std::vector<std::vector<std::string>> npc_Dialog = getDialog(npc->GetName() , 
            NPC_RELATIONSHIP->getRelationshipLevel ("player" , npc->GetName ()));
        
        int choose = rand() % npc_Dialog.size();
        // NPC 对话
        auto NPC_talk_Label = Label::createWithSystemFont ( npc_Dialog[choose][0] , "fonts/Comic Sans MS.ttf" , 40);
        NPC_talk_Label->setTextColor ( cocos2d::Color4B::BLACK );
        NPC_talk_Label->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.14 ) );
        this->addChild ( NPC_talk_Label , 2 );
        // 四个回答
        auto Player_talk_Label1 = Label::createWithSystemFont ( npc_Dialog[choose][1] , "fonts/Comic Sans MS.ttf" , 30 );
        Player_talk_Label1->setTextColor ( cocos2d::Color4B::BLACK );
        Player_talk_Label1->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.21 ) );
        this->addChild ( Player_talk_Label1 , 2 );

        auto Player_talk_Label2 = Label::createWithSystemFont ( npc_Dialog[choose][2] , "fonts/Comic Sans MS.ttf" , 30 );
        Player_talk_Label2->setTextColor ( cocos2d::Color4B::BLACK );
        Player_talk_Label2->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.274 ) );
        this->addChild ( Player_talk_Label2 , 2 );

        auto Player_talk_Label3 = Label::createWithSystemFont ( npc_Dialog[choose][3] , "fonts/Comic Sans MS.ttf" , 30 );
        Player_talk_Label3->setTextColor ( cocos2d::Color4B::BLACK );
        Player_talk_Label3->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.338 ) );
        this->addChild ( Player_talk_Label3 , 2 );

        auto Player_talk_Label4 = Label::createWithSystemFont ( npc_Dialog[choose][4] , "fonts/Comic Sans MS.ttf" , 30 );
        Player_talk_Label4->setTextColor ( cocos2d::Color4B::BLACK );
        Player_talk_Label4->setPosition ( Vec2 ( currentx - visibleSize.width * 0.17 , currenty - visibleSize.height * 0.402 ) );
        this->addChild ( Player_talk_Label4 , 2 );


        // 鼠标移动事件  
        auto listener = EventListenerMouse::create ();
        listener->onMouseMove = [=]( EventMouse* event ) {
            Vec2 mousePosition = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePosition = this->convertToNodeSpace ( mousePosition );
            // 检查每个 Selectedbox  
            if (Selectedbox1->getBoundingBox ().containsPoint ( mousePosition )) {
                Selectedbox1->setLocalZOrder ( 2 ); // 显示在上层  
            }
            else {
                Selectedbox1->setLocalZOrder ( 0 ); // 隐藏在下层  
            }
            if (Selectedbox2->getBoundingBox ().containsPoint ( mousePosition )) {
                Selectedbox2->setLocalZOrder ( 2 );
            }
            else {
                Selectedbox2->setLocalZOrder ( 0 );
            }
            if (Selectedbox3->getBoundingBox ().containsPoint ( mousePosition )) {
                Selectedbox3->setLocalZOrder ( 2 );
            }
            else {
                Selectedbox3->setLocalZOrder ( 0 );
            }
            if (Selectedbox4->getBoundingBox ().containsPoint ( mousePosition )) {
                Selectedbox4->setLocalZOrder ( 2 );
            }
            else {
                Selectedbox4->setLocalZOrder ( 0 );
            }
            };

        listener->onMouseDown = [this, Selectedbox1 , Selectedbox2 , Selectedbox3 , Selectedbox4]( EventMouse* event ) {
            Vec2 mousePosition = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePosition = this->convertToNodeSpace ( mousePosition );

            // 检查每个 Selectedbox  
            if (Selectedbox1 && Selectedbox1->getBoundingBox ().containsPoint ( mousePosition )) {
                if (npc_relationship->getRelationship ( "player" , npc->GetName () ) < 60) {
                    npc_relationship->increaseRelationship ( "player" , npc->GetName () , 10.2 );
                }
                this->removeFromParent ();
                return; // 提前返回，避免执行后续选择框检查  
            }
            if (Selectedbox2 && Selectedbox2->getBoundingBox ().containsPoint ( mousePosition )) {
                if (npc_relationship->getRelationship ( "player" , npc->GetName () ) < 60) {
                    npc_relationship->increaseRelationship ( "player" , npc->GetName () , 5.0001 );
                }
                this->removeFromParent ();
                return; // 提前返回  
            }
            if (Selectedbox3 && Selectedbox3->getBoundingBox ().containsPoint ( mousePosition )) {
                npc_relationship->decreaseRelationship ( "player" , npc->GetName () , 0.001 );
                this->removeFromParent ();
                return; // 提前返回  
            }
            if (Selectedbox4 && Selectedbox4->getBoundingBox ().containsPoint ( mousePosition )) {
                npc_relationship->decreaseRelationship ( "player" , npc->GetName () , 5.01 );
                this->removeFromParent ();
                return; // 提前返回  
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
    }
}

void NPCtalkUI::close () {
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
        closeIcon->setPosition ( Vec2 ( currentx + visibleSize.width * 0.40 , currenty - visibleSize.height * 0.13 ) );

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

bool NPCtalkUI::init ( NPC* npc_name , std::string sceneName ) {
    if (!Layer::init ()) {
        return false;
    }
    SceneName = sceneName;
    npc = npc_name;
    NPC_RELATIONSHIP = npc_relationship;

    backgroundcreate ();
    SelectedBox ();
    close ();
    return true;
}

NPCtalkUI* NPCtalkUI::create ( NPC* npc_name , std::string sceneName ) {
    NPCtalkUI* ret = new NPCtalkUI ();
    if (ret && ret->init ( npc_name , sceneName )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}
