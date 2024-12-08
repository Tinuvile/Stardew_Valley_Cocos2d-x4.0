// InventoryUI.cpp  
#include "InventoryUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  

USING_NS_CC;
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}
void InventoryUI::backgroundcreate(){
    // 创建一个半透明的黑色遮罩
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为180
    darkLayer->setPosition ( cocos2d::Vec2 ( -visibleSize.width / 2 , -visibleSize.height / 3 ) ); // 可以设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    auto bag = Sprite::create ( "UIresource/beibao/bag.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'bag.png'" );
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
        Vec2 Pos = Vec2 ( visibleSize.width / 4.5 + origin.x , visibleSize.height / 3 + origin.y );
        bag->setPosition ( Pos );

        // add the sprite as a child to this layer
        this->addChild ( bag , 1 );
    }
}
void InventoryUI::Itemblock ( Inventory* inventory ) {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;
    _selectedSlot = 1; // 默认选中第一个槽位  

    // 创建并初始化物品显示标签  
    _itemLabel = Label::createWithTTF ( "" , "fonts/Marker Felt.ttf" , 20 );
    _itemLabel->setPosition ( 200 , 400 );
    this->addChild ( _itemLabel );

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
            slot->setScale ( scale / 16.5 );
            float bagWidth = bag->getContentSize ().width;
            float bagHeight = bag->getContentSize ().height;
            slot->setPosition ( visibleSize.width / 4.5 + origin.x - bagWidth * 2.086 + (originalWidth * scale / 16.5 + 5) * i , visibleSize.height / 1.8 + origin.y - m * (originalHeight * scale / 16.5 + 10) ); // 计算槽位位置  
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
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // 确保显示所有槽位  

        // 获取槽位物品  
        auto item = _inventory->GetSelectedItem (); // 或者使用 `_inventory->package[i + 1]`  

        // 更新槽位视觉表现  
        if (item) {
            // 假设 Item 有一个方法可以返回它的图片路径  
            auto itemSprite = Sprite::create ( item->initial_pic );
            itemSprite->setPosition ( slot->getContentSize () / 2 );
            slot->addChild ( itemSprite );
        }
        else {
            slot->removeAllChildren (); // 清空槽位  
        }
    }
    // 更新物品信息标签  
    if (auto selectedItem = _inventory->GetSelectedItem ()) {
        _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
    }
    else {
        _itemLabel->setString ( "No item selected." );
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