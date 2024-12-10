// StoreUI.cpp  
#include "StoreUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"

extern Player* player1;
USING_NS_CC;
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void StoreUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    // 创建一个半透明的黑色遮罩
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( position - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );

    auto mybag = Sprite::create ( "UIresource/supermarket/wupinlan.png" );
    mybag->setTag ( 101 );
    if (mybag == nullptr)
    {
        problemLoading ( "'wupinlan.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = mybag->getContentSize ().width;
        float originalHeight = mybag->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        mybag->setScale ( scale / 2 );
        mybag->setPosition ( Vec2 ( position.x + visibleSize.width * 0.2 , position.y - visibleSize.height * 0.25 ) );
        this->addChild ( mybag , 1 );
    }
    //头像框
    auto Characterframe = Sprite::create ( "UIresource/supermarket/frame.png" );
    if (Characterframe == nullptr)
    {
        problemLoading ( "'frame.png'" );
    }
    else
    {
        float originalWidth = Characterframe->getContentSize ().width;
        float originalHeight = Characterframe->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        Characterframe->setScale ( scale / 5 );
        Characterframe->setPosition ( Vec2 ( position.x - visibleSize.width / 2.7 , position.y * 1.57 ) );
        this->addChild ( Characterframe , 1 );
    }
    //人物头像
    auto Characterpicture = Sprite::create ( "Portraits/Pierre/Pierre-0.png" );
    if (Characterpicture == nullptr)
    {
        problemLoading ( "'Pierre-0.png'" );
    }
    else
    {
        float originalWidth = Characterpicture->getContentSize ().width;
        float originalHeight = Characterpicture->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        Characterpicture->setScale ( scale / 5.2 );
        Characterpicture->setPosition ( Vec2 ( position.x - visibleSize.width / 2.7 , position.y * 1.57 ) );
        this->addChild ( Characterpicture , 2 );
    }
    //商店迎接语
    auto welcomeframe = Sprite::create ( "UIresource/supermarket/wupinlan.png" );
    if (welcomeframe == nullptr)
    {
        problemLoading ( "'wupinlan.png'" );
    }
    else
    {
        float originalWidth = welcomeframe->getContentSize ().width;
        float originalHeight = welcomeframe->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        welcomeframe->setScale ( scale / 5 );
        welcomeframe->setPosition ( Vec2 ( position.x - visibleSize.width / 2.7 , position.y * 1.15 ) );
        this->addChild ( welcomeframe , 1 );
    }
    auto welcome = cocos2d::Label::createWithSystemFont ( "Welcome to the\nPierre store" , "fonts/Arial Bold.ttf" , 25 );
    welcome->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色是黑色
    welcome->setPosition ( Vec2 ( position.x - visibleSize.width / 2.7 , position.y * 1.15 ) );
    this->addChild ( welcome , 2 );
}

void StoreUI::ProductDisplay ( Inventory* mybag , Inventory* goods ) {
    _goods = goods;
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //商品框
    auto Productcolumn = Sprite::create ( "UIresource/supermarket/wupinlan_final.png" );
    if (Productcolumn == nullptr)
    {
        problemLoading ( "'wupinlan_final.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = Productcolumn->getContentSize ().width;
        float originalHeight = Productcolumn->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        Productcolumn->setScale ( scale / 1.4 );
        Productcolumn->setPosition ( Vec2 ( position.x + visibleSize.width / 9.5 , position.y * 1.4 ) );
        this->addChild ( Productcolumn , 0 );
    }
    //创建 ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // 设置为垂直滚动
    scrollView->setContentSize ( Size ( 1230 , 400 ) ); // ScrollView 宽度与 Productcolumn 一致，高度为 Productcolumn 的两倍
    scrollView->setInnerContainerSize ( Size ( 1230 , 400 ) );
    scrollView->setPosition ( Vec2 ( 220 , visibleSize.height / 2.3 ) ); // 设置位置
    scrollView->setBounceEnabled ( true ); // 启用弹性效果

    // 监听鼠标滚轮事件
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [scrollView]( cocos2d::EventMouse* event ) {
        // 获取鼠标滚轮的偏移量
        float scrollDelta = event->getScrollY ();

        // 调整 ScrollView 的滚动，依据滚轮方向
        auto innerContainer = scrollView->getInnerContainer ();
        innerContainer->setPositionY ( innerContainer->getPositionY () + scrollDelta * 105 );  // 控制灵敏度
        };

    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
    
    //每个商品
    float offsetY = 0;  // 用来存储商品间的纵向间距
    for (int i = 0; i < 24; ++i) {
        // 获取槽位物品 
        auto item = _goods->GetItemAt ( i + 1 ); // 获取特定槽位的物品，注意槽位从1开始 
        auto itemSprite = Sprite::create ( item->initial_pic );
        if (itemSprite == nullptr) {
            CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
            continue;  // 跳过当前商品，继续处理下一个商品
        }
        if (itemSprite) {
            //添加物品名称
            std::string itemname = item->GetName ();
            auto Item_name = cocos2d::Label::createWithSystemFont ( itemname , "fonts/Comic Sans MS.ttf" , 30 );
            Item_name->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
            Item_name->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色是红色
            Item_name->setPosition ( Vec2 ( 380 , 357 - offsetY ) );
            scrollView->addChild ( Item_name , 2 );

            //添加物品图片
            itemSprite->setPosition ( Vec2 ( 290 , 357 - offsetY ) );
            itemSprite->setScale ( 0.7f );
            scrollView->addChild ( itemSprite , 2 );

            //添加物品价值
            int itemvalue = item->GetValue ();
            std::string ItemValue = std::to_string ( itemvalue );
            auto item_value = cocos2d::Label::createWithSystemFont ( ItemValue , "fonts/Comic Sans MS.ttf" , 30 );
            item_value->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
            item_value->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色是红色
            item_value->setPosition ( Vec2 ( 1080 , 357 - offsetY ) );
            scrollView->addChild ( item_value , 2 );
            CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
        }
        else {
            CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
        }
            // 更新下一个商品的位置偏移量
            offsetY += 105;  // 21 是商品间的间距
    }
    

    // 将滚动视图添加到场景中
    this->addChild ( scrollView , 2 );
}

bool StoreUI::init ( Inventory* mybag , Inventory* goods ) {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    ProductDisplay ( mybag , goods );

    Itemblock ( mybag , goods );

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

StoreUI* StoreUI::create ( Inventory* mybag , Inventory* goods ) {
    StoreUI* ret = new StoreUI ();
    if (ret && ret->init ( mybag , goods )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void StoreUI::Itemblock ( Inventory* mybag , Inventory* goods ) {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _mybag = mybag;
    _selectedSlot = 1; // 默认选中第一个槽位  


    // 初始化物品槽 Sprite 
    for (int m = 0; m < 3; m++)
    {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create ( "UIresource/beibao/wupincao.png" );
            auto bag = getChildByTag ( 101 );
            // 获取原始图片的宽高
            float originalWidth = slot->getContentSize ().width;
            float originalHeight = slot->getContentSize ().height;
            // 根据屏幕宽度和图片原始宽高计算比例
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
            float scale = std::min ( scaleX , scaleY );
            slot->setScale ( scale / 22 );
            float bagWidth = bag->getContentSize ().width;
            float bagHeight = bag->getContentSize ().height;
            slot->setPosition ( position.x - bagWidth * 0.12 + (originalWidth * scale / 22 + 5) * i , position.y - bagHeight * 2.7 - m * (originalHeight * scale / 22 + 23) ); // 计算槽位位置  
            slot->setTag ( i + 1 ); // 设置槽位的标签  
            this->addChild ( slot , 2 );

            _itemSlots.pushBack ( slot );

            // 添加触摸事件  
            auto listener = EventListenerTouchOneByOne::create ();
            listener->onTouchBegan = [this , slot]( Touch* touch , Event* event ) {
                Vec2 location = touch->getLocation ();
                if (slot->getBoundingBox ().containsPoint ( location )) {
                    //onItemSlotClicked ( slot );
                    return true; // 处理这个事件  
                }
                return false; // 不处理这个事件  
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , slot );
        }
    }
}

void StoreUI::updateDisplay () {
    if (!_mybag) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // 退出方法  
    }

    // 获取当前选择的物品的槽位  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // 确保显示所有槽位  

        // 获取槽位物品  
        auto item = _mybag->GetItemAt ( i + 1 ); // 获取特定槽位的物品，注意槽位从1开始 

        // 获取物品数量   
        int itemCount = _mybag->GetItemCountAt ( i + 1 ); // 获取该槽位的物品数量  

        if (item) {
            CCLOG ( "Item in slot %d: %s" , i + 1 , item->GetName ().c_str () );
        }
        else {
            CCLOG ( "No item in slot %d" , i + 1 );
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
                itemSprite->setScale ( 0.2f );
                slot->addChild ( itemSprite , 3 );
                CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
            }
            else {
                CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
            }

            // 根据 item 里的数量来设置数量标签（如果需要）。  
            // 可以在这里创建一个 Label 显示数量  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i )); // 使用槽位的标签生成数量标签的唯一ID  
            if (!countLabel) {
                // 如果标签不存在，创建新的标签  
                countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Arial Bold.ttf" , 20 );
                countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                countLabel->setPosition ( slot->getPosition ().x + slot->getContentSize ().width * 1.7 , slot->getPosition ().y - slot->getContentSize ().height * 1.7 ); // 设置位置在槽位下方  
                countLabel->setTag ( 200 + i ); // 设置标签  
                slot->addChild ( countLabel , 4 ); // 添加到层级中  
            }
            else {
                // 如果标签存在，更新数量  
                countLabel->setString ( std::to_string ( itemCount ) );
            }
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

    // 更新物品信息标签（用于调试）  
    if (_itemLabel) { // 检查 _itemLabel 是否为 nullptr  
        if (auto selectedItem = _mybag->GetSelectedItem ()) {
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

void StoreUI::onItemSlotClicked ( cocos2d::Ref* sender ) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag (); // 获取槽位位置  

    // 设置为选中状态并更新 Inventory 数据  
    _mybag->SetSelectedItem ( position );
    _selectedSlot = position;

    // 更新显示  
    updateDisplay ();
}