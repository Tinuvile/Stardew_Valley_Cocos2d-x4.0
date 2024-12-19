// InventoryUI.cpp  
#include "intimacyUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  

const int characternum = 5;

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void intimacyUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    if (SceneName == "Town") {
        Leftboundary = -170.0f;
        rightboundary = 1773.0f;
        upperboundary = 1498.0f;
        lowerboundary = -222.0f;
    }
    else if (SceneName == "Cave") {
        Leftboundary =  786.0f;
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
    else if (x >= rightboundary){
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

void intimacyUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // ����һ����͸���ĺ�ɫ����
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );
    //����
    auto IntimacyFace = Sprite::create ( "UIresource/qinmidu/intimacyDisplay.png" );
    IntimacyFace->setTag ( 101 );
    if (IntimacyFace == nullptr)
    {
        problemLoading ( "'intimacyDisplay.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = IntimacyFace->getContentSize ().width;
        float originalHeight = IntimacyFace->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        IntimacyFace->setScale ( scale / 1.5 );
        IntimacyFace->setPosition ( Vec2 ( currentx , currenty + 13 ) );
       
        this->addChild ( IntimacyFace , 1 );
        for (int i = 0; i < characternum; i++) {
            auto oneframe = Sprite::create ( "UIresource/qinmidu/weixuanzhong.png" );
            oneframe->setTag ( i + 1 );
            float originalframeHeight = oneframe->getContentSize ().height;
            oneframe->setScale ( scale / 1.5 );
            oneframe->setPosition ( currentx - 2 , currenty + 280 - i * (originalframeHeight * scale / 1.5 + 12) );
            oneframe->setTag ( i + 1 );
            this->addChild ( oneframe , 2 );
            auto listener = EventListenerMouse::create ();
            listener->onMouseMove = [this , oneframe]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );
                if (oneframe->getBoundingBox ().containsPoint ( mousePos ))
                    oneframe->setTexture ( "UIresource/qinmidu/xuanzhong.png" );
                else
                    oneframe->setTexture ( "UIresource/qinmidu/weixuanzhong.png" );
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , oneframe );

        }
    }
    if (Season == "Spring" || Season == "Autumn") {
        characterInfo ( "Abigail" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.2215 ) );
        characterInfo ( "Alex" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.1165 ) );
        characterInfo ( "Caroline" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.0115 ) );
        characterInfo ( "Elliott" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.0935 ) );
        characterInfo ( "Emily" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.1985 ) );
    }
    else {
        characterInfo ( "Abigail" , Season + "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.2215 ) );
        characterInfo ( "Alex" , Season + "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.1165 ) );
        characterInfo ( "Caroline" , Season + "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.0115 ) );
        characterInfo ( "Elliott" , Season + "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.0935 ) );
        characterInfo ( "Emily" , Season + "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.1985 ) );
    }

    intimacyDisplay ( "Abigail" , Vec2 ( currentx - visibleSize.width * 0.09 , currenty + visibleSize.height * 0.217 ) );
    intimacyDisplay ( "Alex" , Vec2 ( currentx - visibleSize.width * 0.09 , currenty + visibleSize.height * 0.112 ) );
    intimacyDisplay ( "Caroline" , Vec2 ( currentx - visibleSize.width * 0.09 , currenty + visibleSize.height * 0.007 ) );
    intimacyDisplay ( "Elliott" , Vec2 ( currentx - visibleSize.width * 0.09 , currenty - visibleSize.height * 0.098 ) );
    intimacyDisplay ( "Emily" , Vec2 ( currentx - visibleSize.width * 0.09 , currenty - visibleSize.height * 0.203 ) );
}

void intimacyUI::characterInfo ( const string& name , const string& status , Vec2 Pos_photo) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //����ͷ��
    std::string photo = getNPCportraits ( name , status );
    auto characterPhoto = Sprite::create ( photo );
    cocos2d::log("%s", photo.c_str());
    if (characterPhoto == NULL) {
        cocos2d::log("failed");
    }
    else {
        float originalWidth = characterPhoto->getContentSize().width;
        float originalHeight = characterPhoto->getContentSize().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min(scaleX, scaleY);
        characterPhoto->setScale(scale * 0.1);
        characterPhoto->setPosition(Pos_photo);
        this->addChild(characterPhoto, 2);
    }
    //����
    auto NameLabel = Label::createWithSystemFont ( name , "fonts/Comic Sans MS.ttf" , 35 );
    NameLabel->setTextColor ( cocos2d::Color4B::BLACK );
    NameLabel->setPosition ( Vec2 ( Pos_photo.x + visibleSize.width * 0.1 , Pos_photo.y ) );
    this->addChild ( NameLabel , 2 );
}

void intimacyUI::intimacyDisplay ( const string& name , Vec2 Pos ) {
    int fullheart_num = NPC_RELATIONSHIP->getRelationship ( "player" , name ) / 10;
    int emptyheart_num = 10 - fullheart_num;
    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    //������ʾ
    for (int i = 0; i < 10; i++) {
        if (fullheart_num > 0)
        {
            auto fullHeart = Sprite::create ( "UIresource/qinmidu/fullheart.png" );
            if (fullHeart == nullptr)
            {
                problemLoading ( "'fullheart.png'" );
            }
            else
            {
                fullHeart->setScale ( 1.2f );
                fullHeart->setPosition ( Vec2 ( Pos.x + 32 * 1600 / 884 / 1.5 * i , Pos.y ) );
                this->addChild ( fullHeart , 3 );
            }
            fullheart_num--;
            continue;
        }
        if (emptyheart_num > 0)
        {
            auto emptyheart = Sprite::create ( "UIresource/qinmidu/emptyheart.png" );
            if (emptyheart == nullptr)
            {
                problemLoading ( "'emptyheart.png'" );
            }
            else
            {
                emptyheart->setScale ( 1.2f );
                emptyheart->setPosition ( Vec2 ( Pos.x + 32 * 1600 / 884 / 1.5 * i , Pos.y ) );
                this->addChild ( emptyheart , 3 );
            }
            emptyheart_num--;
            continue;
        }
    }

    //�Ƿ�˵������ʾ
    if (NPC_RELATIONSHIP->getRelationship ( "player" , name ) != 0)
    {
        auto IsTalked = Sprite::create ( "UIresource/qinmidu/is.png" );
        if (IsTalked == nullptr)
        {
            problemLoading ( "'is.png'" );
        }
        else
        {
            float originalWidth = IsTalked->getContentSize ().width;
            float originalHeight = IsTalked->getContentSize ().height;
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
            float scale = std::min ( scaleX , scaleY );
            IsTalked->setScale ( scale * 0.026 );
            IsTalked->setPosition ( Vec2 ( Pos.x + visibleSize.width * 0.374 , Pos.y - 27 ) );

            this->addChild ( IsTalked , 3 );
        }
    }

    //������ʾ
    int GiftTime = 0;
    CCLOG ( "%d" , NPC_RELATIONSHIP->NpcGiftTIme ( name ) );
    if (NPC_RELATIONSHIP->NpcGiftTIme ( name ) > 0)
    {
        if (NPC_RELATIONSHIP->NpcGiftTIme ( name ) >= 2) {
            GiftTime = 2;
        }
        else
            GiftTime = 1;
        for (int i = 0; i < GiftTime; i++)
        {
            auto IsGifted = Sprite::create ( "UIresource/qinmidu/is.png" );
            if (IsGifted == nullptr)
            {
                problemLoading ( "'is.png'" );
            }
            else
            {
                float originalWidth = IsGifted->getContentSize ().width;
                float originalHeight = IsGifted->getContentSize ().height;
                float scaleX = visibleSize.width / originalWidth;
                float scaleY = visibleSize.height / originalHeight;
                // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
                float scale = std::min ( scaleX , scaleY );
                IsGifted->setScale ( scale * 0.026 );
                IsGifted->setPosition ( Vec2 ( Pos.x + visibleSize.width * 0.271 + i * 50.0f , Pos.y - 27 ) );

                this->addChild ( IsGifted , 3 );
            }
        }
    }
}

void intimacyUI::Buttons_switching () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //ͼ����ʾ
    auto bagkey = Sprite::create ( "UIresource/beibao/bagkey.png" );
    auto Skillkey = Sprite::create ( "UIresource/beibao/Skillkey.png" );
    auto intimacykey = Sprite::create ( "UIresource/beibao/intimacykey.png" );
    if (bagkey == nullptr)
    {
        problemLoading ( "'bagkey.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = bagkey->getContentSize ().width;
        float originalHeight = bagkey->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        bagkey->setScale ( scale / 16.5 );
        bagkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.25 , currenty + visibleSize.height * 0.315 ) );//0.305��ѡ��ʱλ��
        Skillkey->setScale ( scale / 16.5 );
        Skillkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.19 , currenty + visibleSize.height * 0.315 ) );//0.315��δѡ��ʱλ��
        intimacykey->setScale ( scale / 16.5 );
        intimacykey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.13 , currenty + visibleSize.height * 0.305 ) );//0.315��δѡ��ʱλ��
        this->addChild ( bagkey , 2 );
        this->addChild ( Skillkey , 2 );
        this->addChild ( intimacykey , 2 );
    }

    //�����Լ��л�Layer
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , bagkey , Skillkey , intimacykey]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        //CCLOG ( "X:%f,Y:%f" , event->getCursorX () , event->getCursorY () );
        if (bagkey->getBoundingBox ().containsPoint ( mousePos )) {
            // �Ƴ���ǰ��Layer
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( InventoryUI::create ( inventory , nowScene ) , 20 );
        }
        else if (Skillkey->getBoundingBox ().containsPoint ( mousePos )) {
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( SkillTreeUI::create ( nowScene ) , 20 );
        }
        else if (intimacykey->getBoundingBox ().containsPoint ( mousePos )) {
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void intimacyUI::close () {
    // ���ü��̼�����  
    auto listenerClose = EventListenerKeyboard::create ();
    listenerClose->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            this->removeFromParent ();
        }
        };
    // ����������ӵ��¼��ַ�����  
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerClose , this );
}

bool intimacyUI::init ( std::string sceneName ) {
    if (!Layer::init ()) {
        return false;
    }
    SceneName = sceneName;
    NPC_RELATIONSHIP = npc_relationship;
    backgroundcreate ();
    Buttons_switching ();
    close ();
    return true;
}

intimacyUI* intimacyUI::create ( std::string sceneName ) {
    intimacyUI* ret = new intimacyUI ();
    if (ret && ret->init ( sceneName )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

