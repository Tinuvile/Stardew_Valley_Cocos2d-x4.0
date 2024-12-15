
// mini_bag.cpp  
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

void mini_bag::updateCoordinate ( float& x , float& y) {
    Vec2 position = player1->getPosition ();
    if (whichScene == "Town") {
        if (x <= -170) {
            x = -170;
        }
        else if (x >= 1773) {
            x = 1773;
        }
        else {
            x = position.x;
        }

        if (y >= 1498) {
            y = 1498;
        }
        else if (y <= -222) {
            y = -222;
        }
        else {
            y = position.y;
        }
    }
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
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = bag->getContentSize ().width;
        float originalHeight = bag->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        bag->setScale ( scale / 1.5 );
        bag->setPosition ( Vec2 ( 0 , 0 - visibleSize.height * 0.4 ) );
        this->addChild ( bag , 0 );
    }
}

void mini_bag::Itemblock ( Inventory* inventory ) {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;
    _selectedSlot = 1; // Ĭ��ѡ�е�һ����λ  


    // ��ʼ����Ʒ�� Sprite 
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = Sprite::create ( "UIresource/beibao/itemblock.png" );
        auto bag = getChildByTag ( 101 );
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = slot->getContentSize ().width;
        float originalHeight = slot->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        slot->setScale ( scale / 16.5 );
        float bagWidth = bag->getContentSize ().width;
        float bagHeight = bag->getContentSize ().height;
        slot->setPosition ( 0 - bagWidth * 0.57 + (originalWidth * scale / 16.5 + 5) * i , 0 - visibleSize.height * 0.435 + bagHeight * 1.73 / 3.643); // �����λλ��  
        slot->setTag ( i + 1 ); // ���ò�λ�ı�ǩ  
        this->addChild ( slot , 2 );

        _itemSlots.pushBack ( slot );

    }
}

bool mini_bag::init ( Inventory* inventory , std::string& WhichScene ) {
    if (!Layer::init ()) {
        return false;
    }
    whichScene = WhichScene;
    backgroundcreate ();

    Itemblock ( inventory );

    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    updateDisplay (); // ������ʾ����  

    return true;
}

mini_bag* mini_bag::create ( Inventory* inventory , std::string& WhichScene ) {
    mini_bag* ret = new mini_bag ();
    if (ret && ret->init ( inventory, WhichScene )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void mini_bag::updateDisplay () {
    if (!_inventory) {
        return; // �˳�����  
    }

        // ��ȡ��ǰѡ�����Ʒ�Ĳ�λ  
    for (int i = 0; i < kRowSize; ++i) {
        int serial_number = i;
        auto slot = _itemSlots.at ( serial_number );
        slot->setVisible ( true ); // ȷ����ʾ���в�λ  

        // ��ȡ��λ��Ʒ  
        auto item = _inventory->GetItemAt ( serial_number + 1 ); // ��ȡ�ض���λ����Ʒ��ע���λ��1��ʼ 

        // ��ȡ��Ʒ����   
        int itemCount = _inventory->GetItemCountAt ( serial_number + 1 ); // ��ȡ�ò�λ����Ʒ����  

        // �����Ҫ��ȡ�ض���λ����Ʒ��ʹ�� GetItemAt(int position) �����º���  

        // ���²�λ�Ӿ�����  
        if (item) {
            // ���֮ǰ���ӽڵ�  
            slot->removeAllChildren ();

            // ͼƬ·��
            auto itemSprite = Sprite::create ( item->initial_pic );
            if (itemSprite) {
                itemSprite->setPosition ( slot->getContentSize () / 2 );
                itemSprite->setScale ( 0.7f );
                slot->addChild ( itemSprite , 3 );
            }
            // ���� item �������������������ǩ�������Ҫ����  
            // ���������ﴴ��һ�� Label ��ʾ����  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + serial_number )); // ʹ�ò�λ�ı�ǩ����������ǩ��ΨһID  
            if (!countLabel) {
                // �����ǩ�����ڣ������µı�ǩ  
                countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Comic Sans MS.ttf" , 20 );
                countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                countLabel->setPosition ( slot->getContentSize ().width * 0.8 , slot->getContentSize ().height * 0.2 ); // ����λ���ڲ�λ���·�  
                countLabel->setTag ( 200 + serial_number ); // ���ñ�ǩ  
                slot->addChild ( countLabel , 4 ); // ��ӵ��㼶��  
            }
            else {
                // �����ǩ���ڣ���������  
                countLabel->setString ( std::to_string ( itemCount ) );
            }


            // ��Ӵ����¼�  
            auto listener = EventListenerMouse::create ();

            // ����ƶ��¼�
            listener->onMouseMove = [this , slot , itemSprite , countLabel]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );
                if (slot && slot->getBoundingBox ().containsPoint ( mousePos )) {
                    itemSprite->setScale ( 1.1f );
                    countLabel->setScale ( 1.5f );
                }
                else if (slot && itemSprite != currentItemSprite) {
                    itemSprite->setScale ( 0.7f ); // �ָ�ԭ��С
                    countLabel->setScale ( 1.0f );
                }
                };

            // �����갴���¼�  
            listener->onMouseDown = [this , slot , itemSprite, serial_number]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );

                // �������Ƿ����� slot  
                if (slot->getBoundingBox ().containsPoint ( mousePos )) {
                    if (!isClick) {
                        currentItemSprite = itemSprite; // ��¼��ǰѡ�����Ʒ
                        _selectedSlot = serial_number + 1;
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
            slot->removeAllChildren (); // ��ղ�λ  

            // ���������ǩ  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i ));
            if (countLabel) {
                countLabel->removeFromParent (); // �Ƴ�������ǩ  
            }
        }
    }
    

    // ������Ʒ��Ϣ��ǩ�����ڵ��ԣ�  
    //if (_itemLabel) { // ��� _itemLabel �Ƿ�Ϊ nullptr  
    //    if (auto selectedItem = _inventory->GetSelectedItem ()) {
    //        _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
    //    }
    //    else {
    //        _itemLabel->setString ( "No item selected." );
    //    }
    //}
}

void mini_bag::onItemSlotClicked ( cocos2d::Ref* sender ) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag (); // ��ȡ��λλ��  

    // ����Ϊѡ��״̬������ Inventory ����  
    _inventory->SetSelectedItem ( position );
    _selectedSlot = position;

    // ������ʾ  
    updateDisplay ();
}