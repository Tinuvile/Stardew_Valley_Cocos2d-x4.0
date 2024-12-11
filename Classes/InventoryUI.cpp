// InventoryUI.cpp  
#include "InventoryUI.h"  
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
void InventoryUI::backgroundcreate(){
    Vec2 position = player1->getPosition ();
    // 创建一个半透明的黑色遮罩
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( position - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    auto bag = Sprite::create ( "UIresource/beibao/newbag1.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'newbag1.png'" );
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
        bag->setPosition ( position );
        this->addChild ( bag , 0 );
    }
}
void InventoryUI::Itemblock ( Inventory* inventory ) {
    Vec2 position = player1->getPosition ();
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
            slot->setPosition ( position.x - bagWidth * 0.545 + (originalWidth * scale / 16.5 + 5) * i , position.y + bagHeight * 1.73 / 3.643 - m * (originalHeight * scale / 16.5 + 10) ); // 计算槽位位置  
            slot->setTag ( i + 1 ); // 设置槽位的标签  
            this->addChild ( slot , 2 );

            _itemSlots.pushBack ( slot );

            // 添加触摸事件  
            auto listener = EventListenerTouchOneByOne::create ();
            listener->onTouchBegan = [this , slot]( Touch* touch , Event* event ) {
                Vec2 location = touch->getLocation ();
                if (slot->getBoundingBox ().containsPoint ( location )) {
                    onItemSlotClicked ( slot );
                    return true; // 处理这个事件  
                }
                return false; // 不处理这个事件  
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , slot );
        }
    }
}
bool InventoryUI::init ( Inventory* inventory ) {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();

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

InventoryUI* InventoryUI::create ( Inventory* inventory ) {
    InventoryUI* ret = new InventoryUI ();
    if (ret && ret->init ( inventory )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void InventoryUI::updateDisplay () {
    Vec2 position = player1->getPosition ();
    if (!_inventory) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // 退出方法  
    }

    // 获取当前选择的物品的槽位  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // 确保显示所有槽位  

        // 获取槽位物品  
        auto item = _inventory->GetItemAt ( i + 1 ); // 获取特定槽位的物品，注意槽位从1开始 

        // 获取物品数量   
        int itemCount = _inventory->GetItemCountAt(i + 1); // 获取该槽位的物品数量  

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
                itemSprite->setScale ( 0.7f );
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
                countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Comic Sans MS.ttf" , 20 );
                countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                countLabel->setPosition ( slot->getContentSize ().width * 0.8 ,  slot->getContentSize ().height * 0.2 ); // 设置位置在槽位右下方  
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

void InventoryUI::onItemSlotClicked ( cocos2d::Ref* sender ) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag (); // 获取槽位位置  

    // 设置为选中状态并更新 Inventory 数据  
    _inventory->SetSelectedItem ( position );
    _selectedSlot = position;

    // 更新显示  
    updateDisplay ();
}