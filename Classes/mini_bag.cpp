#include "mini_bag.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"


USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void mini_bag::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    //updateCoordinate ( 0 , 0 );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto bag = Sprite::create ( "UIresource/beibao/minibag.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'minibag.png'" );
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
        bag->setPosition ( Vec2 ( 0 , 0 - visibleSize.height * 0.45 ) );
        this->addChild ( bag , 0 );
    }
}

void mini_bag::Itemblock ( Inventory* inventory ) {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;


    // 初始化物品槽 Sprite 
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
        slot->setPosition ( 0 - bagWidth * 0.57 + (originalWidth * scale / 16.5 + 5) * i , 0 - visibleSize.height * 0.485 + bagHeight * 1.73 / 3.643 ); // 计算槽位位置  
        slot->setTag ( i + 1 ); // 设置槽位的标签  
        this->addChild ( slot , 2 );

        _itemSlots.pushBack ( slot );

    }
}

bool mini_bag::init ( Inventory* inventory ) {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();

    Itemblock ( inventory );

    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    updateDisplay (); // 更新显示内容  

    return true;
}

mini_bag* mini_bag::create ( Inventory* inventory ) {
    mini_bag* ret = new mini_bag ();
    if (ret && ret->init ( inventory )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void mini_bag::updateDisplay () {
    if (!_inventory) {
        return; // 退出方法  
    }

    // 获取当前选择的物品的槽位  
    for (int i = 0; i < kRowSize; ++i) {
        int serial_number = i;
        auto slot = _itemSlots.at ( serial_number );
        slot->setVisible ( true ); // 确保显示所有槽位  

        // 获取槽位物品  
        auto item = _inventory->GetItemAt ( serial_number + 1 ); // 获取特定槽位的物品，注意槽位从1开始 

        // 获取物品数量   
        int itemCount = _inventory->GetItemCountAt ( serial_number + 1 ); // 获取该槽位的物品数量  

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
            listener->onMouseDown = [this , slot , itemSprite , serial_number]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );

                // 检查鼠标是否点击了 slot  
                if (slot->getBoundingBox ().containsPoint ( mousePos )) {
                    if (!isClick) {
                        currentItemSprite = itemSprite; // 记录当前选择的物品
                        _selectedSlot = serial_number + 1;
                    }
                    else {
                        currentItemSprite = nullptr;
                        _selectedSlot = 0;
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

        auto keyboard_listener = EventListenerKeyboard::create ();
        keyboard_listener->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
            if (keyCode == EventKeyboard::KeyCode::KEY_E && !is_key_e_pressed) {
                is_key_e_pressed = true;
                auto selected_item = std::dynamic_pointer_cast<Food>(this->getSelectedItem ());
                if (selected_item != nullptr) {
                    CCLOG ( "EAT FOOD!" );
                    strength = std::min ( 100 , strength + selected_item->GetEnergy () );
                    inventory->RemoveItem ( *selected_item );
                    inventory->DisplayPackageInCCLOG ();
                }
            }
            };
        keyboard_listener->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
            if (keyCode == EventKeyboard::KeyCode::KEY_E) {
                is_key_e_pressed = false;
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( keyboard_listener , this );
    }

    // 更新物品信息标签（用于调试）  
    //if (_itemLabel) { // 检查 _itemLabel 是否为 nullptr  
    //    if (auto selectedItem = _inventory->GetSelectedItem ()) {
    //        _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
    //    }
    //    else {
    //        _itemLabel->setString ( "No item selected." );
    //    }
    //}
}


void mini_bag::getSelectBack () {
    _selectedSlot = 0;
    currentItemSprite = nullptr;
}


// 复制并返回当前选中的物品（Item）
std::shared_ptr<Item> mini_bag::getSelectedItem () {
    // 确保选中了槽位
    if (_selectedSlot == 0) {
        return nullptr;  // 如果没有选中任何槽位，返回空
    }

    // 获取当前选中的槽位索引
    int serial_number = _selectedSlot - 1;  // 假设槽位从1开始，索引从0开始

    // 从库存中获取物品实例
    std::shared_ptr<Item> itemPtr = _inventory->GetItemAt ( serial_number + 1 );  // 获取 shared_ptr

    if (itemPtr != nullptr) {

        auto temp = itemPtr->GetCopy ();
        return temp;
    }
    else {
        return nullptr;
    }

}