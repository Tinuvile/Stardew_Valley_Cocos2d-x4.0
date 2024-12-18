// StoreUI.cpp  
#include "StoreUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"


USING_NS_CC;
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}
void StoreUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    if (x <= 725) {
        x = 725;
    }
    else {
        x = position.x;
    }
    if (y <= -66) {
        y = -66;
    }
    else {
        y = position.y;
    }
}

void StoreUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );

    //背包
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
        mybag->setPosition ( Vec2 ( currentx + visibleSize.width * 0.2 , currenty - visibleSize.height * 0.25 ) );
        this->addChild ( mybag , 1 );

        auto listener = EventListenerMouse::create ();
        // 检查鼠标是否点击了背包物品槽  
           // 添加鼠标按下事件  
        listener->onMouseDown = [this , mybag]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );

            // 检查鼠标是否点击了 mybag  
            if (mybag->getBoundingBox ().containsPoint ( mousePos )) {
                if (isClick) {
                    //economicSystem->buyItem ( chosen_Item->GetName () );
                    int goldAmount = economicSystem->getGoldAmount ();
                    CCLOG ( "goldAmount: %d , Value: %d" , goldAmount , chosen_Item->GetValue () );
                    std::string chosen_item_name = chosen_Item->GetName ();
                    if (goldAmount >= chosen_Item->GetValue ()) {
                        //若所选物品为动物
                        if (chosen_item_name.find ( "Animal" )!=std::string::npos) {
                            std::pair<Rect , bool>* space = nullptr;
                            for (auto& pair : barn_space) {
                                //畜棚仍有空间
                                if (!pair.second) {
                                    space = &pair;
                                    break;
                                }
                            }
                            //若有空间
                            if (space != nullptr) {
                                Livestock* livestock = nullptr;
                                //检查品种
                                if (chosen_item_name == "AnimalChicken") {
                                    livestock = Chicken::create ( space->first );
                                }
                                else if (chosen_item_name == "AnimalSheep") {
                                    livestock = Sheep::create ( space->first );
                                }
                                else if (chosen_item_name == "AnimalCow") {
                                    livestock = Cow::create ( space->first );
                                }
                                if (livestock != nullptr) {
                                    space->second = true;
                                    livestocks.push_back ( livestock );
                                    livestock->retain ();
                                    economicSystem->subtractGold ( chosen_Item->GetValue () );
                                    updateDisplay ();
                                    CCLOG ( "Purchased item: %s" , chosen_Item->GetName ().c_str () );
                                }
                            }
                            else {
                                CCLOG ( "fail to place %s in your barn" , chosen_item_name.c_str () );
                            }
                            
                        }
                        else {
                            economicSystem->subtractGold ( chosen_Item->GetValue () );
                            _mybag->AddItem ( *chosen_Item );
                            _mybag->is_updated = true;
                            updateDisplay ();
                            CCLOG ( "Purchased item: %s" , chosen_Item->GetName ().c_str () );
                        }
                    }
                    else {
                        CCLOG ( "Not enough gold to buy %s." , chosen_Item->GetName ().c_str () );
                    }
                    isClick = false;
                    chosen_Item = nullptr;
                }
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , mybag );
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
        Characterframe->setPosition ( Vec2 ( currentx - visibleSize.width / 2.7 , currenty + visibleSize.height * 0.24 ) );
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
        Characterpicture->setPosition ( Vec2 ( currentx - visibleSize.width / 2.7 , currenty + visibleSize.height * 0.24 ) );
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
        welcomeframe->setPosition ( Vec2 ( currentx - visibleSize.width / 2.7 , currenty + visibleSize.height * 0.06316 ) );
        this->addChild ( welcomeframe , 1 );
    }
    auto welcome = cocos2d::Label::createWithSystemFont ( "Welcome to the\nPierre store" , "fonts/Arial Bold.ttf" , 25 );
    welcome->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色是黑色
    welcome->setPosition ( Vec2 ( currentx - visibleSize.width / 2.7 , currenty + visibleSize.height * 0.06316 ) );
    this->addChild ( welcome , 2 );

    //拥有金币框
    auto moneyFrame = Sprite::create ( "UIresource/supermarket/moneyFrame_new.png" );
    if (moneyFrame == nullptr)
    {
        problemLoading ( "'moneyFrame_new.png'" );
    }
    else
    {
        float originalWidth = moneyFrame->getContentSize ().width;
        float originalHeight = moneyFrame->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        moneyFrame->setScale ( scale / 4 );
        moneyFrame->setPosition ( Vec2 ( currentx - visibleSize.width * 0.1 , currenty - visibleSize.height * 0.042 ) );
        this->addChild ( moneyFrame , 1 );
    }
}

void StoreUI::ProductDisplay ( Inventory* mybag , Inventory* goods ) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //商品框
    auto Productcolumn = Sprite::create ( "UIresource/supermarket/wupinlan.png" );

        // 获取原始图片的宽高
        float originalWidth = Productcolumn->getContentSize ().width;
        float originalHeight = Productcolumn->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        Productcolumn->setScale ( scale / 1.4 );
        Productcolumn->setPosition ( Vec2 ( currentx + visibleSize.width / 9.5 , currenty + visibleSize.height * 0.1684 ) );
        this->addChild ( Productcolumn , 0 );

    //创建 ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // 设置为垂直滚动
    scrollView->setContentSize ( Size ( 1630 , 400 ) ); // 设置ScrollView 宽度，高度
    scrollView->setPosition ( Vec2 ( currentx - visibleSize.width * 0.389 , currenty + visibleSize.height * 0.01368 ) ); // 设置位置
    scrollView->setBounceEnabled ( true ); // 启用弹性效果
    scrollView->setScrollBarEnabled ( false );    // 禁用垂直和水平滑动条

    // 计算商品的总高度  
    float totalItemHeight = 0;
    const int itemCount = 24; // 假设有24个商品  
    const float itemHeight = 105; // 每个商品的高度  
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
        float newPosY = currentPosY + scrollDelta * 105; // 调整灵敏度  

        // 限制滚动的上下边界  
        float lowerLimit = scrollView->getContentSize ().height - innerContainer->getContentSize ().height;
        float upperLimit = -20;

        //CCLOG ( "currentPosY: %f, newPosY: %f, lowerLimit: %f, upperLimit: %f" , currentPosY , newPosY , lowerLimit , upperLimit );

        // 使用 std::max 和 std::min 确保 newPosY 在边界内  
        newPosY = std::max ( newPosY , lowerLimit );
        newPosY = std::min ( newPosY , upperLimit );

        // 设置新的位置  
        innerContainer->setPositionY ( newPosY );

        };
    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
    
    //每个商品
    float offsetY = 0;  // 用来存储商品间的纵向间距
    for (int i = 0; i < 24; ++i) {
        //添加物品框
        auto itemframe = Sprite::create ( "UIresource/supermarket/goodframe.png" );
            itemframe->setScale ( scale / 1.4 );
            itemframe->setPosition ( Vec2 ( visibleSize.width * 0.4933 , 539 + visibleSize.height * 1.51 - offsetY ) );
            scrollView->addChild ( itemframe , 1 );

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
            Item_name->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色
            Item_name->setPosition ( Vec2 (  visibleSize.width * 0.2386 ,539+ visibleSize.height * 1.51 - offsetY ) );
            scrollView->addChild ( Item_name , 2 );

            //添加物品图片
            itemSprite->setPosition ( Vec2 ( visibleSize.width * 0.1783 ,539+ visibleSize.height * 1.51 - offsetY ) );
            itemSprite->setScale ( 0.7f );
            scrollView->addChild ( itemSprite , 2 );

            //添加物品价值
            int itemvalue = item->GetValue ();
            std::string ItemValue = std::to_string ( itemvalue );
            auto item_value = cocos2d::Label::createWithSystemFont ( ItemValue , "fonts/Comic Sans MS.ttf" , 30 );
            item_value->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
            item_value->setTextColor ( cocos2d::Color4B::BLACK );  // 初始颜色
            item_value->setPosition ( Vec2 (visibleSize.width * 0.6750 , 539 + visibleSize.height * 1.51 - offsetY ) );
            scrollView->addChild ( item_value , 2 );
            //CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
        }
        else {
            //CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
        }

        auto listener = EventListenerMouse::create ();
            listener->onMouseMove = [this , itemframe , scrollView , currenty]( EventMouse* event ) {

                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );

                mousePos = this->convertToNodeSpace ( mousePos );
                Vec2 scrollViewPos = scrollView->getPosition ();

                Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
                Rect itemBoundingBox = itemframe->getBoundingBox ();

                float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
                float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;
                if (mousePos.x >= adjustedPosX && mousePos.x <= adjustedPosX + itemBoundingBox.size.width &&
                mousePos.y >= adjustedPosY + currenty && mousePos.y <= currenty + adjustedPosY + itemBoundingBox.size.height) {
                        itemframe->setTexture ( "UIresource/supermarket/xuanzhong_frame.png" );
                }
                else {
                        itemframe->setTexture ( "UIresource/supermarket/goodframe.png" );
                }
            };

            listener->onMouseDown = [this , itemframe , scrollView , currenty , currentx ,item , visibleSize , i]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );

                Vec2 scrollViewPos = scrollView->getPosition ();

                Vec2 innerContainerPos = scrollView->getInnerContainer ()->getPosition ();
                Rect itemBoundingBox = itemframe->getBoundingBox ();

                float adjustedPosY = itemBoundingBox.getMinY () + innerContainerPos.y;
                float adjustedPosX = itemBoundingBox.getMinX () + innerContainerPos.x;
                if (mousePos.x >= adjustedPosX && mousePos.x <= adjustedPosX + itemBoundingBox.size.width &&
                    mousePos.y >= adjustedPosY + currenty && mousePos.y <= currenty + adjustedPosY + itemBoundingBox.size.height &&
                    mousePos.x >= currentx - visibleSize.width * 0.25 && mousePos.x < currentx + visibleSize.width * 0.455 &&
                     mousePos.y >= currenty - visibleSize.height * 0.0772 && mousePos.y < currenty + visibleSize.height * 0.3025
                    ) {
                    isClick = true;
                    chosen_Item = item;
                    CCLOG ( "chosen_Item: %s" , item->GetName ().c_str () );
                }
                };

            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , itemframe );

            // 更新下一个商品的位置偏移量
            offsetY += 105;  // 105 是商品间的间距
    }

    // 将滚动视图添加到场景中
    this->addChild ( scrollView , 2 );
}

void StoreUI::SliderDisplay () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //滑动条和滑动块
    auto Sliders = Sprite::create ( "UIresource/supermarket/huadongtiao.png" );
    if (Sliders == nullptr)
    {
        problemLoading ( "'huadongtiao.png'" );
    }
    else
    {
        float originalWidth = Sliders->getContentSize ().width;
        float originalHeight = Sliders->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        Sliders->setScale ( scale / 2.4 );
        Sliders->setPosition ( Vec2 ( currentx + visibleSize.width * 0.48 , currenty + visibleSize.height * 0.16 ) );
        this->addChild ( Sliders , 5 );
    }
    auto Slider = Sprite::create ( "UIresource/supermarket/huadongkuai.png" );
    if (Slider == nullptr)
    {
        problemLoading ( "'huadongkuai.png'" );
    }
    else
    {
        float originalWidth = Slider->getContentSize ().width;
        float originalHeight = Slider->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        Slider->setScale ( scale / 29 );
        Slider->setPosition ( Vec2 ( currentx + visibleSize.width * 0.478 , currenty + visibleSize.height * 0.34375 ) );
        this->addChild ( Slider , 6 );
    }
    // 监听滚轮事件
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [Slider,currenty,visibleSize]( cocos2d::EventMouse* event ) {
        float _minY = currenty + visibleSize.height * 0.34375 - 20 * 23.8;
        float _maxY = currenty + visibleSize.height * 0.34375;

        // 获取滚轮滚动的增量（单位：像素）
        float scrollDelta = event->getScrollY ();

        // 获取当前精灵的位置
        cocos2d::Vec2 currentPos = Slider->getPosition ();

        // 根据滚轮的滚动方向来调整精灵的位置
        float newY = currentPos.y - scrollDelta * 23.8; // 每次滚动的像素

        // 限制精灵的垂直位置在[minY, maxY]范围内
        if (newY < _minY)
            newY = _minY;
        if (newY > _maxY)
            newY = _maxY;

        // 设置新的位置
        Slider->setPosition ( cocos2d::Vec2 ( currentPos.x , newY ) );
        };

    // 获取当前事件分发器并添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void StoreUI::moneyDisplay () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //金币更新
    static Label* GoldAmount = nullptr;
    int goldAmount = economicSystem->getGoldAmount ();
    if (GoldAmount == nullptr) {
        GoldAmount = Label::createWithSystemFont ( std::to_string ( goldAmount ) , "fonts/Comic Sans MS.ttf" , 45 );
        GoldAmount->setTextColor ( Color4B::BLACK );
        GoldAmount->setPosition ( Vec2 ( currentx - visibleSize.width * 0.1 , currenty - visibleSize.height * 0.0425 ) );
        this->addChild ( GoldAmount , 4 );
    }
    else {
        GoldAmount->setString ( std::to_string ( goldAmount ) );
    }
    auto listenerWithPlayer = EventListenerKeyboard::create ();
    listenerWithPlayer->onKeyPressed = [this, goldAmount]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                GoldAmount = nullptr;
            }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerWithPlayer , this );
}

bool StoreUI::init ( Inventory* mybag , Inventory* goods ) {
    if (!Layer::init ()) {
        return false;
    }

    _mybag = mybag;
    _goods = goods;
    economicSystem = std::make_shared<EconomicSystem> ( _mybag , _goods); // 在这里初始化  
    CCLOG ( "%d" , economicSystem->getGoldAmount () );

    backgroundcreate ();

    ProductDisplay ( mybag , goods );

    SliderDisplay ();

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
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
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
            slot->setPosition ( currentx - bagWidth * 0.12 + (originalWidth * scale / 22 + 5) * i , currenty - bagHeight * 2.7 - m * (originalHeight * scale / 22 + 23) ); // 计算槽位位置  
            slot->setTag ( i + 1 ); // 设置槽位的标签  
            slot->setOpacity ( 128 );
            this->addChild ( slot , 2 );

            _itemSlots.pushBack ( slot );
        }
    }
}

void StoreUI::updateDisplay () {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    if (!_mybag) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // 退出方法  
    }

    //金币更新
    moneyDisplay ();

    for (int m = 0; m < 3; m++) {
        // 获取当前选择的物品的槽位  
        for (int i = 0; i < kRowSize; ++i) {
            int serial_number = i + m * 12;
            auto slot = _itemSlots.at ( serial_number );
            slot->setVisible ( true ); // 确保显示所有槽位  

            // 获取槽位物品  
            auto item = _mybag->GetItemAt ( serial_number + 1 ); // 获取特定槽位的物品，注意槽位从1开始 

            // 获取物品数量   
            int itemCount = _mybag->GetItemCountAt ( serial_number + 1 ); // 获取该槽位的物品数量  

            if (item) {
                //CCLOG ( "Item in slot %d: %s" , serial_number + 1 , item->GetName ().c_str () );
            }
            else {
                //CCLOG ( "No item in slot %d" , serial_number + 1 );
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
                    //itemSprite->setOpacity ( 128 );
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
                    countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Comic Sans MS.ttf" , 8 );
                    countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                    countLabel->setPosition ( slot->getContentSize ().width * 0.8 , slot->getContentSize ().height * 0.2 ); // 设置位置在槽位右下方  
                    countLabel->setTag ( 200 + serial_number ); // 设置标签  
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