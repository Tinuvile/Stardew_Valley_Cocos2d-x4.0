#include "CreateCharacterUI.h"
#include "Town.h"
#include "AppDelegate.h"
#include "Myhouse.h"

USING_NS_CC;


Scene* CreateCharacter::createScene ()
{
    return CreateCharacter::create ();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void CreateCharacter::cloudAni ( float dt )
{
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    auto clouds = Sprite::create ( "UIresource/Clouds.png" );
    if (clouds) {
        Size cloudsSize = clouds->getContentSize ();
        float maxWidth = visibleSize.width * 1.1f;
        float maxHeight = visibleSize.height * 1.1f;
        float scaleX = maxWidth / cloudsSize.width;
        float scaleY = maxHeight / cloudsSize.height;
        clouds->setScale ( std::min ( scaleX , scaleY ) );
        clouds->setPosition ( Vec2 ( visibleSize.width * 1.5 + origin.x , visibleSize.height * 0.8 + origin.y ) );
        this->addChild ( clouds , 1 );
    }
    else {
        problemLoading ( "'Clouds.png'" );
    }

    // 计算精灵移动的目标位置（屏幕的左侧）
    auto moveTo_s = cocos2d::MoveTo::create ( 50.0f , cocos2d::Vec2 ( -visibleSize.width * 0.6 , clouds->getPosition ().y ) );
    clouds->runAction ( cocos2d::RepeatForever::create ( moveTo_s ) );
}

void CreateCharacter::BackgroundAdd () {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    // add "CreateCharacter" splash screen"
    auto background = Sprite::create ( "UIresource/background2-half.png" );
    if (background == nullptr)
    {
        problemLoading ( "'background2-half.png'" );
    }
    else
    {
        // 计算所需的缩放比例  
        float scaleX = visibleSize.width / background->getContentSize ().width;
        float scaleY = visibleSize.height / background->getContentSize ().height;

        // 选择较大的缩放因子进行放大（以确保填充整个窗口）  
        float scaleFactor = std::max ( scaleX , scaleY );
        background->setScale ( scaleFactor );

        // position the sprite on the center of the screen
        background->setPosition ( Vec2 ( visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y ) );

        // add the sprite as a child to this layer
        this->addChild ( background , 0 );
    }
}

void CreateCharacter::optionFace () {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    auto optionface = Sprite::create ( "UIresource/create/create.png" );
    optionface->setTag ( 201 );
    if (optionface == nullptr)
    {
        problemLoading ( "'create.png'" );
    }
    else
    {
        float newWidth = visibleSize.width * 0.7f;
        float newHeight = visibleSize.height * 0.9f;
        optionface->setContentSize ( Size ( newWidth , newHeight ) );

        // 获取精灵的高度
        float spriteHeight = optionface->getContentSize ().height;

        // 设置精灵的坐标，使其底部紧贴屏幕下界
        // visibleSize.height 是屏幕的高度，spriteHeight 是精灵的高度
        optionface->setPosition ( visibleSize.width / 2 , spriteHeight / 2 );  // 居中对齐宽度

        // add the sprite as a child to this layer
        this->addChild ( optionface , 1 );
    }

    auto displaycharacter = Sprite::create ( "UIresource/create/displaycharacter.png" );
    if (displaycharacter == nullptr)
    {
        problemLoading ( "'displaycharacter.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = displaycharacter->getContentSize ().width;
        float originalHeight = displaycharacter->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        displaycharacter->setScale ( scale / 5 );
        Vec2 leftTopPos = Vec2 ( visibleSize.width / 2 - optionface->getContentSize ().width * 0.2 , visibleSize.height / 2 + optionface->getContentSize ().height * 0.2 );

        // 设置小图位置
        displaycharacter->setPosition ( leftTopPos );

        // add the sprite as a child to this layer
        this->addChild ( displaycharacter , 2 );
    }
    Vec2 displaycharacterPos = displaycharacter->getPosition ();
    auto male = Sprite::create ( "UIresource/create/male.png" );
    if (male == nullptr)
    {
        problemLoading ( "'male.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = male->getContentSize ().width;
        float originalHeight = male->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        male->setScale ( scale / 16.5 );
        Vec2 displaycharacterPos = displaycharacter->getPosition ();
        Vec2 Pos = Vec2 ( displaycharacterPos.x - displaycharacter->getContentSize ().width / 2 , displaycharacterPos.y - displaycharacter->getContentSize ().height );

        male->setPosition ( Pos );

        // add the sprite as a child to this layer
        this->addChild ( male , 2 );
    }
    auto female = Sprite::create ( "UIresource/create/female.png" );
    if (female == nullptr)
    {
        problemLoading ( "'female.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = female->getContentSize ().width;
        float originalHeight = female->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        female->setScale ( scale / 16.5 );
        Vec2 Pos = Vec2 ( displaycharacterPos.x + displaycharacter->getContentSize ().width / 2 , displaycharacterPos.y - displaycharacter->getContentSize ().height );

        female->setPosition ( Pos );

        // add the sprite as a child to this layer
        this->addChild ( female , 2 );
    }

    auto xuanzhong = Sprite::create ( "UIresource/create/xuanzhong.png" );
    if (xuanzhong == nullptr)
    {
        problemLoading ( "'xuanzhong.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = xuanzhong->getContentSize ().width;
        float originalHeight = xuanzhong->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        xuanzhong->setScale ( scale / 13 );
        Vec2 Pos = Vec2 ( displaycharacterPos.x - displaycharacter->getContentSize ().width / 2 , displaycharacterPos.y - displaycharacter->getContentSize ().height );

        xuanzhong->setPosition ( Pos );

        // add the sprite as a child to this layer
        this->addChild ( xuanzhong , 2 );
    }
    auto CharacterDisplay = Sprite::create ( "UIresource/zhujue/1.png" );
    CharacterDisplay->setTag ( 666 );
    if (CharacterDisplay == nullptr)
    {
        problemLoading ( "'1.png'" );
    }
    else
    {
        float originalWidth = CharacterDisplay->getContentSize ().width;
        float originalHeight = CharacterDisplay->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        CharacterDisplay->setScale ( scale / 7.5 );
        CharacterDisplay->setPosition ( Vec2 ( visibleSize.width / 2 - optionface->getContentSize ().width * 0.2 , visibleSize.height / 2 + optionface->getContentSize ().height * 0.2 ) );
        this->addChild ( CharacterDisplay , 4 );
    }

    auto OK = ui::Button::create ( "UIresource/create/OK.png" , "UIresource/create/OK.png" );
    OK->setTag ( 202 );

    float originalWidth = OK->getContentSize ().width;
    float originalHeight = OK->getContentSize ().height;
    float scaleX = visibleSize.width / originalWidth;
    float scaleY = visibleSize.height / originalHeight;
    float scale = std::min ( scaleX , scaleY );
    OK->setScale ( scale / 8 );
    OK->setOpacity ( 128 );
    auto listener = EventListenerMouse::create ();
    listener->onMouseMove = [this , OK , scale]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        if (OK->getBoundingBox ().containsPoint ( mousePos )) {
            OK->setScale ( scale / 8 * 1.2f );
        }
        else
            OK->setScale ( scale / 8 );
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , OK );
    OK->setEnabled ( false );  // 禁用点击事件
    OK->addClickEventListener ( [this]( Ref* sender ) {
        AudioEngine::pauseAll ( );
        // auto backgroundAudioID = AudioEngine::play2d ( "mymusic.mp3" , true );
        player1 = Player::create();
        auto nextscene = Myhouse::create();
        Director::getInstance ()->replaceScene ( TransitionFade::create ( 3.0f , nextscene ) );
} );
    Vec2 Pos = Vec2 ( visibleSize.width * 0.5 , visibleSize.height * 0.2 );
    OK->setPosition ( Pos );
    this->addChild ( OK , 2 );

    Vec2 leftPos = Vec2 ( displaycharacterPos.x - displaycharacter->getContentSize ().width / 1.5 , displaycharacterPos.y - displaycharacter->getContentSize ().height / 1.7 );
    auto leftarrow = directions ( "UIresource/create/left.png" , origin , leftPos );
    Vec2 rightPos = Vec2 ( displaycharacterPos.x + displaycharacter->getContentSize ().width / 1.5 , displaycharacterPos.y - displaycharacter->getContentSize ().height / 1.7 );
    auto rightarrow = directions ( "UIresource/create/right.png" , origin , rightPos );
    mouseListen ( leftarrow , rightarrow , male , female , xuanzhong , displaycharacter );

}

cocos2d::Sprite* CreateCharacter::directions ( const std::string& normalImage , const Vec2& origin , const Vec2& position )
{
    auto item = Sprite::create ( normalImage );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    if (item) {
        Size itemSize = item->getContentSize ();
        // 获取原始图片的宽高
        float originalWidth = item->getContentSize ().width;
        float originalHeight = item->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        item->setScale ( scale / 18 );
        item->setPosition ( position );
        this->addChild ( item , 3 );
    }
    else {
        problemLoading ( normalImage.c_str () );
    }
    return item;
}

void CreateCharacter::mouseListen ( cocos2d::Sprite* leftarrow , cocos2d::Sprite* rightarrow , cocos2d::Sprite* male , cocos2d::Sprite* female , cocos2d::Sprite* xuanzhong , cocos2d::Sprite* displaycharacter ) {
    auto listener = EventListenerMouse::create ();
    listener->onMouseMove = [this , leftarrow , rightarrow , male , female]( EventMouse* event ) {
        updateItems ( leftarrow , "UIresource/create/left.png" , event , 18 );
        updateItems ( rightarrow , "UIresource/create/right.png" , event , 18 );
        updateItems ( male , "UIresource/create/male.png" , event , 16.5 );
        updateItems ( female , "UIresource/create/female.png" , event , 16.5 );
        };
    cocos2d::Vec2 anchor1 = leftarrow->getAnchorPoint ();
    cocos2d::Vec2 anchor2 = rightarrow->getAnchorPoint ();
    cocos2d::Vec2 anchor3 = xuanzhong->getAnchorPoint ();
    auto node = getChildByTag ( 666 );
    Sprite* CharacterDisplay = dynamic_cast<cocos2d::Sprite*>(node);
    static int which = 1;
    listener->onMouseDown = [this , leftarrow , rightarrow , male , female , xuanzhong , anchor1 , anchor2 , anchor3 , displaycharacter , CharacterDisplay]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        if (leftarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mousedowncallback ( leftarrow , leftarrow );
            which++;
            if (which >= 4) {
                which = 0;
            }
            string photoAddress = "UIresource/zhujue/" + std::to_string ( which ) + ".png";
            CharacterDisplay->setTexture ( photoAddress );
        }
        else if (rightarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mousedowncallback ( rightarrow , rightarrow );
            which--;
            if (which < 0) {
                which = 3;
            }
            string photoAddress = "UIresource/zhujue/" + std::to_string ( which ) + ".png";
            CharacterDisplay->setTexture ( photoAddress );
        }
        else if (male->getBoundingBox ().containsPoint ( mousePos )) {
            if (anchor2.x == anchor3.x && anchor2.y == anchor3.y) {
                Vec2 displaycharacterPos = displaycharacter->getPosition ();
                auto move = MoveTo::create ( 0.0f , Vec2 ( displaycharacterPos.x - displaycharacter->getContentSize ().width / 2 , displaycharacterPos.y - displaycharacter->getContentSize ().height ) );
                xuanzhong->runAction ( move );
            }
            mousedowncallback ( male , male );
        }
        else if (female->getBoundingBox ().containsPoint ( mousePos )) {
            if (anchor1.x == anchor3.x && anchor1.y == anchor3.y) {
                Vec2 displaycharacterPos = displaycharacter->getPosition ();
                auto move = MoveTo::create ( 0.0f , Vec2 ( displaycharacterPos.x + displaycharacter->getContentSize ().width / 2 , displaycharacterPos.y - displaycharacter->getContentSize ().height ) );
                xuanzhong->runAction ( move );
            }
            mousedowncallback ( female , female );
        }
        };
    listener->onMouseUp = [this , leftarrow , rightarrow , male , female]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        if (leftarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( leftarrow , leftarrow );
        }
        else if (rightarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( rightarrow , rightarrow );
        }
        else if (male->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( male , male );
        }
        else if (female->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( female , female );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void CreateCharacter::textIn () {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    auto optionface = this->getChildByTag ( 201 );
    auto textBox1 = Sprite::create ( "UIresource/create/textBox.png" );
    auto nameLabel = cocos2d::Label::createWithSystemFont ( "Name" , "fonts/Comic Sans MS.ttf" , 25 );
    nameLabel->setTag ( 10 );
    nameLabel->setTextColor ( cocos2d::Color4B::RED );  // 初始颜色是红色
    this->addChild ( nameLabel , 2 );
    auto textBox2 = Sprite::create ( "UIresource/create/textBox.png" );
    auto Farmname = cocos2d::Label::createWithSystemFont ( "Farm name" , "fonts/Comic Sans MS.ttf" , 25 );
    Farmname->setTag ( 20 );
    Farmname->setTextColor ( cocos2d::Color4B::RED );  // 初始颜色是红色
    this->addChild ( Farmname , 2 );
    auto textBox3 = Sprite::create ( "UIresource/create/textBox.png" );
    auto Favoritethings = cocos2d::Label::createWithSystemFont ( "Favorite things" , "fonts/Comic Sans MS.ttf" , 25 );
    Favoritethings->setTag ( 30 );
    Favoritethings->setTextColor ( cocos2d::Color4B::RED );  // 初始颜色是红色
    this->addChild ( Favoritethings , 2 );
    if (textBox1 == nullptr)
    {
        // 示例图片
        problemLoading ( "'textBox.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = textBox1->getContentSize ().width;
        float originalHeight = textBox1->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        textBox1->setScale ( scale / 8 );
        textBox2->setScale ( scale / 8 );
        textBox3->setScale ( scale / 8 );
        Vec2 Pos1 = Vec2 ( visibleSize.width / 2 + optionface->getContentSize ().width * 0.2 , visibleSize.height / 2.05 + optionface->getContentSize ().height * 0.3 );
        Vec2 Pos2 = Vec2 ( visibleSize.width / 2 + optionface->getContentSize ().width * 0.2 , visibleSize.height / 2.05 + optionface->getContentSize ().height * 0.2 );
        Vec2 Pos3 = Vec2 ( visibleSize.width / 2 + optionface->getContentSize ().width * 0.2 , visibleSize.height / 2.05 + optionface->getContentSize ().height * 0.1 );
        textBox1->setPosition ( Pos1 );
        nameLabel->setPosition ( Pos1.x * 0.8 , Pos1.y );
        textBox2->setPosition ( Pos2 );
        Farmname->setPosition ( Pos2.x * 0.8 , Pos2.y );
        textBox3->setPosition ( Pos3 );
        Favoritethings->setPosition ( Pos3.x * 0.8 , Pos3.y );
        // add the sprite as a child to this layer
        this->addChild ( textBox1 , 2 );
        this->addChild ( textBox2 , 2 );
        this->addChild ( textBox3 , 2 );
        auto textField1 = createTextIn ( originalWidth * scale , originalHeight * scale , Pos1 );
        auto textField2 = createTextIn ( originalWidth * scale , originalHeight * scale , Pos2 );
        auto textField3 = createTextIn ( originalWidth * scale , originalHeight * scale , Pos3 );
        this->addChild ( textField1 , 3 );
        this->addChild ( textField2 , 3 );
        this->addChild ( textField3 , 3 );
        textField1->addEventListener ( [=]( cocos2d::Ref* sender , cocos2d::ui::TextField::EventType type ) {
            checkTextFields ( textField1 , textField2 , textField3 );
            } );
        textField2->addEventListener ( [=]( cocos2d::Ref* sender , cocos2d::ui::TextField::EventType type ) {
            checkTextFields ( textField1 , textField2 , textField3 );
            } );
        textField3->addEventListener ( [=]( cocos2d::Ref* sender , cocos2d::ui::TextField::EventType type ) {
            checkTextFields ( textField1 , textField2 , textField3 );
            } );
    }
}

ui::TextField* CreateCharacter::createTextIn ( float sizex , float sizey , const Vec2& Pos ) {
    // 创建一个 TextField
    auto textField = ui::TextField::create ( "Please enter" , "Arial" , 24 );
    textField->setPosition ( Pos );
    textField->setContentSize ( Size ( sizex , sizey ) );
    textField->setMaxLength ( 20 );
    textField->setCursorEnabled ( true );
    textField->setTouchSize ( Size ( sizex , sizey ) );
    // 监听文本输入
    textField->addEventListener ( [=]( cocos2d::Ref* sender , cocos2d::ui::TextField::EventType type ) {
        if (type == cocos2d::ui::TextField::EventType::ATTACH_WITH_IME) {
            CCLOG ( "TextField attach with IME" );
        }
        else if (type == cocos2d::ui::TextField::EventType::DETACH_WITH_IME) {
            CCLOG ( "TextField detach with IME" );
        }
        else if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT) {
            CCLOG ( "Text inserted: %s" , textField->getString ().c_str () );
        }
        else if (type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            CCLOG ( "Backspace pressed, current text: %s" , textField->getString ().c_str () );
        }
    } );
    return textField;
}

void CreateCharacter::checkTextFields ( ui::TextField* textfield1 , ui::TextField* textfield2 , ui::TextField* textfield3 ) {
    auto OK = dynamic_cast<cocos2d::ui::Button*>(this->getChildByTag ( 202 ));
    std::string text1 = textfield1->getString ();
    protagonistName = text1;
    CCLOG ( "%s" , protagonistName );
    std::string text2 = textfield2->getString ();
    FarmName = text2;
    CCLOG ( "%s" , FarmName );
    std::string text3 = textfield3->getString ();
    auto namelable = getChildByTag ( 10 );
    auto farmname = getChildByTag ( 20 );
    auto favanimal = getChildByTag ( 30 );
    if (!text1.empty ()) {
        namelable->setColor ( cocos2d::Color3B::BLACK );
    }
    if (!text2.empty ()) {
        farmname->setColor ( cocos2d::Color3B::BLACK );
    }
    if (!text3.empty ()) {
        favanimal->setColor ( cocos2d::Color3B::BLACK );
    }
    // 检查三个文本框是否都有内容
    if (!text1.empty () && !text2.empty () && !text3.empty ())
    {
        OK->setOpacity ( 255 );    // 使OK不透明
        OK->setEnabled ( true );   // 启用OK按钮的点击事件
    }
    else
    {
        OK->setOpacity ( 128 );
        OK->setEnabled ( false );
        // 如果任一文本框为空，恢复
    }
}

void CreateCharacter::favoranimal () {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    //文字添加
    auto favanimal = cocos2d::Label::createWithSystemFont ( "Favorite animal" , "fonts/Comic Sans MS.ttf" , 25 );
    favanimal->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色是黑色
    Vec2 Pos = Vec2 ( visibleSize.width / 2.0 , visibleSize.height / 2.05 );
    favanimal->setPosition ( Pos );
    this->addChild ( favanimal , 2 );

    //箭头添加
    Vec2 leftPos = Vec2 ( visibleSize.width / 1.7 , visibleSize.height / 2.05 );
    auto leftarrow = directions ( "UIresource/create/left.png" , origin , leftPos );
    Vec2 rightPos = Vec2 ( visibleSize.width / 1.4 , visibleSize.height / 2.05 );
    auto rightarrow = directions ( "UIresource/create/right.png" , origin , rightPos );
    //动物图片添加
    auto animal = Sprite::create ( "UIresource/create/like1.png" );
    if (animal == nullptr)
    {
        problemLoading ( "'like1.png'" );
    }
    else
    {
        float originalWidth = animal->getContentSize ().width;
        float originalHeight = animal->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        animal->setScale ( scale / 18 );
        Vec2 Pos = Vec2 ( (leftPos.x + rightPos.x) / 2 , leftPos.y );
        animal->setPosition ( Pos );
        // add the sprite as a child to this layer
        this->addChild ( animal , 2 );
    }
    auto listener = EventListenerMouse::create ();
    listener->onMouseMove = [this , leftarrow , rightarrow]( EventMouse* event ) {
        updateItems ( leftarrow , "UIresource/create/left.png" , event , 18 );
        updateItems ( rightarrow , "UIresource/create/right.png" , event , 18 );
        };
    cocos2d::Vec2 anchor1 = leftarrow->getAnchorPoint ();
    cocos2d::Vec2 anchor2 = rightarrow->getAnchorPoint ();
    listener->onMouseDown = [this , leftarrow , rightarrow , anchor1 , anchor2 , animal]( EventMouse* event ) {
        static int count = 1;
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        if (leftarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mousedowncallback ( leftarrow , leftarrow );
            count--;
            if (count <= 0)
                count = 6;
            std::string like = StringUtils::format ( "UIresource/create/like%d.png" , count );
            animal->setTexture ( like );
        }
        else if (rightarrow->getBoundingBox ().containsPoint ( mousePos )) {
            count++;
            if (count >= 6)
                count = 1;
            std::string like = StringUtils::format ( "UIresource/create/like%d.png" , count );
            animal->setTexture ( like );
            mousedowncallback ( rightarrow , rightarrow );
        }
        };
    listener->onMouseUp = [this , leftarrow , rightarrow]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        if (leftarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( leftarrow , leftarrow );
        }
        else if (rightarrow->getBoundingBox ().containsPoint ( mousePos )) {
            mouseupcallback ( rightarrow , rightarrow );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void CreateCharacter::updateItems ( cocos2d::Sprite* item , const std::string& normalImage , cocos2d::Event* event , const int Magnification )
{
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    EventMouse* e = (EventMouse*)event;
    Vec2 mousePos = e->getLocationInView ();  // 获取鼠标位置
    Rect targetRect = item->getBoundingBox ();  // 获取目标节点的矩形区域
    Size itemSize = item->getContentSize ();
    // 获取原始图片的宽高
    float originalWidth = item->getContentSize ().width;
    float originalHeight = item->getContentSize ().height;

    // 根据屏幕宽度和图片原始宽高计算比例
    float scaleX = visibleSize.width / originalWidth;
    float scaleY = visibleSize.height / originalHeight;

    // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
    float scale = std::min ( scaleX , scaleY );

    if (targetRect.containsPoint ( mousePos )) {
        // 鼠标悬停在目标节点上，放大
        item->setScale ( scale / Magnification * 1.2 );
    }
    else {
        // 鼠标离开，恢复原大小
        item->setScale ( scale / Magnification );
    }
}

void CreateCharacter::mousedowncallback ( Ref* pSender , Sprite* item ) {
    // 获取当前精灵的缩放比例
    float currentScale = item->getScale ();
    // 计算新的缩放比例（当前比例 / 1.2）
    float newScale = currentScale / 1.2f;
    // 设置新的缩放比例
    item->setScale ( newScale );
}

void CreateCharacter::mouseupcallback ( Ref* pSender , Sprite* item ) {
    // 获取当前精灵的缩放比例
    float currentScale = item->getScale ();
    // 计算新的缩放比例（当前比例 * 1.2）
    float newScale = currentScale * 1.2f;
    // 设置新的缩放比例
    item->setScale ( newScale );
}

bool CreateCharacter::init ()
{
    if (!Scene::init ())
    {
        return false;
    }
    BackgroundAdd ();
    cloudAni ( 1.0f );
    optionFace ();
    favoranimal ();
    textIn ();
    return true;
}
