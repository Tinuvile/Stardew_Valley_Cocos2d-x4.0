// InventoryUI.cpp  
#include "InventoryUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"

USING_NS_CC;


static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void InventoryUI::updateCoordinate ( float &x , float &y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    if (SceneName == "Town") {
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
    CCLOG ( "%f  %f" , x , y );
}

void InventoryUI::backgroundcreate(){
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );   
    // 创建一个半透明的黑色遮罩
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    auto bag = Sprite::create ( "UIresource/beibao/newbag2.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'newbag2.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = bag->getContentSize ().width;
        float originalHeight = bag->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        bag->setScale ( scale / 1.5 );
        bag->setPosition ( Vec2 ( currentx , currenty ) );
        this->addChild ( bag , 0 );
    }
}

void InventoryUI::Itemblock ( Inventory* inventory ) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;
    _selectedSlot = 1; // 默认选中第一个槽位  


    // 初始化物品槽 Sprite 
    for (int m = 0; m < 3; m++)
    {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create ( "UIresource/beibao/itemblock.png" );
            auto bag = getChildByTag ( 101 );
            // 获取原始图片的宽高
            float originalWidth = slot->getContentSize ().width;
            float originalHeight = slot->getContentSize ().height;
            // 根据屏幕宽度和图片原始宽高计算比例
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
            float scale = std::min ( scaleX , scaleY );
            slot->setScale ( scale / 16.5 );
            float bagWidth = bag->getContentSize ().width;
            float bagHeight = bag->getContentSize ().height;
            slot->setPosition ( currentx - bagWidth * 0.545 + (originalWidth * scale / 16.5 + 5) * i , currenty + bagHeight * 1.73 / 3.643 - m * (originalHeight * scale / 16.5 + 10) ); // 计算槽位位置  
            slot->setTag ( i + 1 ); // 设置槽位的标签  
            this->addChild ( slot , 2 );

            _itemSlots.pushBack ( slot );

        }
    }
}

bool InventoryUI::init ( Inventory* inventory , std::string sceneName ) {
    if (!Layer::init ()) {
        return false;
    }

    SceneName = sceneName;

    backgroundcreate ();

    Buttons_switching ();

    Itemblock ( inventory );

    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    // 初始化物品信息标签（用于调试）  
    _itemLabel = Label::createWithSystemFont ( "Selected: None" , "Arial" , 24 );
    if (_itemLabel) {
        _itemLabel->setPosition ( visibleSize.width / 2 , visibleSize.height / 4 );
        this->addChild ( _itemLabel , 10 ); // 添加到层级中  
    }
    else {
        CCLOG ( "Failed to create _itemLabel" );
    }

    updateDisplay (); // 更新显示内容  

    return true;
}

void InventoryUI::Buttons_switching () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //图标显示
    auto bagkey = Sprite::create ( "UIresource/beibao/bagkey.png" );
    auto Skillkey = Sprite::create ( "UIresource/beibao/Skillkey.png" );
    auto intimacykey = Sprite::create ( "UIresource/beibao/intimacykey.png" );
    if (bagkey == nullptr)
    {
        problemLoading ( "'bagkey.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = bagkey->getContentSize ().width;
        float originalHeight = bagkey->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        bagkey->setScale ( scale / 16.5 );
        bagkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.25 , currenty + visibleSize.height * 0.305 ) );//0.305是选中时位置
        Skillkey->setScale ( scale / 16.5 );
        Skillkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.19 , currenty + visibleSize.height * 0.315 ) );//0.315是未选中时位置
        intimacykey->setScale ( scale / 16.5 );
        intimacykey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.13 , currenty + visibleSize.height * 0.315 ) );//0.315是未选中时位置
        this->addChild ( bagkey , 1 );
        this->addChild ( Skillkey , 1 );
        this->addChild ( intimacykey , 1 );
    }

    //动画以及切换Layer
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this, bagkey, Skillkey,intimacykey]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        //CCLOG ( "X:%f,Y:%f" , event->getCursorX () , event->getCursorY () );
        if (bagkey->getBoundingBox ().containsPoint ( mousePos )) {
        }
        else if (Skillkey->getBoundingBox ().containsPoint ( mousePos )) {
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( SkillTreeUI::create ( nowScene ) , 20 );
        }
        else if (intimacykey->getBoundingBox ().containsPoint ( mousePos )) {
            CCLOG ( "Clicked on intimacykey" );
            // 移除当前的Layer
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( intimacyUI::create ( nowScene ) , 20 );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

InventoryUI* InventoryUI::create ( Inventory* inventory , std::string sceneName ) {
    InventoryUI* ret = new InventoryUI ();
    if (ret && ret->init ( inventory , sceneName )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void InventoryUI::updateDisplay () {
    if (!_inventory) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // 退出方法  
    }

    for (int m = 0; m < 3; m++) {
        // 获取当前选择的物品的槽位  
        for (int i = 0; i < kRowSize; ++i) {
            int serial_number = i + m * 12;
            auto slot = _itemSlots.at ( serial_number );
            slot->setVisible ( true ); // 确保显示所有槽位  

            // 获取槽位物品  
            auto item = _inventory->GetItemAt ( serial_number + 1 ); // 获取特定槽位的物品，注意槽位从1开始 

            // 获取物品数量   
            int itemCount = _inventory->GetItemCountAt ( serial_number + 1 ); // 获取该槽位的物品数量  

            if (item) {
                CCLOG ( "Item in slot %d: %s" , serial_number + 1 , item->GetName ().c_str () );
            }
            else {
                CCLOG ( "No item in slot %d" , serial_number + 1 );
            }

            // 如果需要获取特定槽位的物品，使用 GetItemAt(int position) 定义新函数  

            // 更新槽位视觉表现  
            if (item) {
                // 清除之前的子节点  
                slot->removeAllChildren ();

                // 图片路径  
                auto itemSprite = Sprite::create ( item->initial_pic );
                if (itemSprite) {
                    itemSprite->setPosition ( slot->getContentSize () / 2 );
                    itemSprite->setScale ( 0.7f );
                    slot->addChild ( itemSprite , 3 );
                    CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
                }
                else {
                    CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
                }

                // 根据 item 里的数量来设置数量标签（如果需要）。  
                // 可以在这里创建一个 Label 显示数量  
                auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + serial_number )); // 使用槽位的标签生成数量标签的唯一ID  
                if (!countLabel) {
                    // 如果标签不存在，创建新的标签  
                    countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Comic Sans MS.ttf" , 20 );
                    countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                    countLabel->setPosition ( slot->getContentSize ().width * 0.8 , slot->getContentSize ().height * 0.2 ); // 设置位置在槽位右下方  
                    countLabel->setTag ( 200 + serial_number ); // 设置标签  
                    slot->addChild ( countLabel , 4 ); // 添加到层级中  
                }
                else {
                    // 如果标签存在，更新数量  
                    countLabel->setString ( std::to_string ( itemCount ) );
                }


                // 添加触摸事件  
                auto listener = EventListenerMouse::create ();

                // 鼠标移动事件
                listener->onMouseMove = [this , slot , itemSprite , countLabel]( EventMouse* event ) {
                    Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                    mousePos = this->convertToNodeSpace ( mousePos );
                    if (slot && slot->getBoundingBox ().containsPoint ( mousePos )) {
                        itemSprite->setScale ( 1.1f );
                        countLabel->setScale ( 1.5f );
                    }
                    else if (slot && itemSprite != currentItemSprite) {
                        itemSprite->setScale ( 0.7f ); // 恢复原大小
                        countLabel->setScale ( 1.0f );
                    }
                    };

                // 添加鼠标按下事件  
                listener->onMouseDown = [this , slot , itemSprite, serial_number]( EventMouse* event ) {
                    Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                    mousePos = this->convertToNodeSpace ( mousePos );

                    // 检查鼠标是否点击了 slot  
                    if (slot->getBoundingBox ().containsPoint ( mousePos )) {
                        if (!isClick) {
                            currentItemSprite = itemSprite; // 记录当前选择的物品
                            _selectedSlot = serial_number + 1;
                            CCLOG ( "_selectedSlot:%d" , _selectedSlot );
                        }
                        else {
                            currentItemSprite = nullptr;
                        }
                        isClick = !isClick;
                    }
                    };

                _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , itemSprite );
            }
            else {
                slot->removeAllChildren (); // 清空槽位  

                // 清除数量标签  
                auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i ));
                if (countLabel) {
                    countLabel->removeFromParent (); // 移除数量标签  
                }
            }
        }
    }

    // 更新物品信息标签（用于调试）  
    if (_itemLabel) { // 检查 _itemLabel 是否为 nullptr  
        if (auto selectedItem = _inventory->GetSelectedItem ()) {
            _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
        }
        else {
            _itemLabel->setString ( "No item selected." );
        }
    }
    else {
        CCLOG ( "Warning: _itemLabel is nullptr" );
    }
}
