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
    // ����һ����͸���ĺ�ɫ����
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( position - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );

    auto mybag = Sprite::create ( "UIresource/supermarket/wupinlan.png" );
    mybag->setTag ( 101 );
    if (mybag == nullptr)
    {
        problemLoading ( "'wupinlan.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = mybag->getContentSize ().width;
        float originalHeight = mybag->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        mybag->setScale ( scale / 2 );
        mybag->setPosition ( Vec2 ( position.x + visibleSize.width * 0.2 , position.y - visibleSize.height * 0.25 ) );
        this->addChild ( mybag , 1 );
    }
    //ͷ���
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
    //����ͷ��
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
    //�̵�ӭ����
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
    welcome->setTextColor ( cocos2d::Color4B::BLACK );  // ��ʼ��ɫ�Ǻ�ɫ
    welcome->setPosition ( Vec2 ( position.x - visibleSize.width / 2.7 , position.y * 1.15 ) );
    this->addChild ( welcome , 2 );
}

void StoreUI::ProductDisplay ( Inventory* mybag , Inventory* goods ) {
    _goods = goods;
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //��Ʒ��
    auto Productcolumn = Sprite::create ( "UIresource/supermarket/wupinlan_final.png" );
    if (Productcolumn == nullptr)
    {
        problemLoading ( "'wupinlan_final.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = Productcolumn->getContentSize ().width;
        float originalHeight = Productcolumn->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        Productcolumn->setScale ( scale / 1.4 );
        Productcolumn->setPosition ( Vec2 ( position.x + visibleSize.width / 9.5 , position.y * 1.4 ) );
        this->addChild ( Productcolumn , 0 );
    }
    //���� ScrollView
    auto scrollView = cocos2d::ui::ScrollView::create ();
    scrollView->setDirection ( cocos2d::ui::ScrollView::Direction::VERTICAL ); // ����Ϊ��ֱ����
    scrollView->setContentSize ( Size ( 1230 , 400 ) ); // ScrollView ����� Productcolumn һ�£��߶�Ϊ Productcolumn ������
    scrollView->setInnerContainerSize ( Size ( 1230 , 400 ) );
    scrollView->setPosition ( Vec2 ( 220 , visibleSize.height / 2.3 ) ); // ����λ��
    scrollView->setBounceEnabled ( true ); // ���õ���Ч��

    // �����������¼�
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseScroll = [scrollView]( cocos2d::EventMouse* event ) {
        // ��ȡ�����ֵ�ƫ����
        float scrollDelta = event->getScrollY ();

        // ���� ScrollView �Ĺ��������ݹ��ַ���
        auto innerContainer = scrollView->getInnerContainer ();
        innerContainer->setPositionY ( innerContainer->getPositionY () + scrollDelta * 105 );  // ����������
        };

    // ����������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
    
    //ÿ����Ʒ
    float offsetY = 0;  // �����洢��Ʒ���������
    for (int i = 0; i < 24; ++i) {
        // ��ȡ��λ��Ʒ 
        auto item = _goods->GetItemAt ( i + 1 ); // ��ȡ�ض���λ����Ʒ��ע���λ��1��ʼ 
        auto itemSprite = Sprite::create ( item->initial_pic );
        if (itemSprite == nullptr) {
            CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
            continue;  // ������ǰ��Ʒ������������һ����Ʒ
        }
        if (itemSprite) {
            //�����Ʒ����
            std::string itemname = item->GetName ();
            auto Item_name = cocos2d::Label::createWithSystemFont ( itemname , "fonts/Comic Sans MS.ttf" , 30 );
            Item_name->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
            Item_name->setTextColor ( cocos2d::Color4B::BLACK );  // ��ʼ��ɫ�Ǻ�ɫ
            Item_name->setPosition ( Vec2 ( 380 , 357 - offsetY ) );
            scrollView->addChild ( Item_name , 2 );

            //�����ƷͼƬ
            itemSprite->setPosition ( Vec2 ( 290 , 357 - offsetY ) );
            itemSprite->setScale ( 0.7f );
            scrollView->addChild ( itemSprite , 2 );

            //�����Ʒ��ֵ
            int itemvalue = item->GetValue ();
            std::string ItemValue = std::to_string ( itemvalue );
            auto item_value = cocos2d::Label::createWithSystemFont ( ItemValue , "fonts/Comic Sans MS.ttf" , 30 );
            item_value->setAnchorPoint ( Vec2 ( 0 , 0.5 ) );
            item_value->setTextColor ( cocos2d::Color4B::BLACK );  // ��ʼ��ɫ�Ǻ�ɫ
            item_value->setPosition ( Vec2 ( 1080 , 357 - offsetY ) );
            scrollView->addChild ( item_value , 2 );
            CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
        }
        else {
            CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
        }
            // ������һ����Ʒ��λ��ƫ����
            offsetY += 105;  // 21 ����Ʒ��ļ��
    }
    

    // ��������ͼ��ӵ�������
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

    // ��ʼ����Ʒ��Ϣ��ǩ�����ڵ��ԣ�  
    _itemLabel = Label::createWithSystemFont ( "Selected: None" , "Arial" , 24 );
    if (_itemLabel) {
        _itemLabel->setPosition ( visibleSize.width / 2 , visibleSize.height / 4 );
        this->addChild ( _itemLabel , 10 ); // ��ӵ��㼶��  
    }
    else {
        CCLOG ( "Failed to create _itemLabel" );
    }

    updateDisplay (); // ������ʾ����  

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
    _selectedSlot = 1; // Ĭ��ѡ�е�һ����λ  


    // ��ʼ����Ʒ�� Sprite 
    for (int m = 0; m < 3; m++)
    {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create ( "UIresource/beibao/wupincao.png" );
            auto bag = getChildByTag ( 101 );
            // ��ȡԭʼͼƬ�Ŀ��
            float originalWidth = slot->getContentSize ().width;
            float originalHeight = slot->getContentSize ().height;
            // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
            float scale = std::min ( scaleX , scaleY );
            slot->setScale ( scale / 22 );
            float bagWidth = bag->getContentSize ().width;
            float bagHeight = bag->getContentSize ().height;
            slot->setPosition ( position.x - bagWidth * 0.12 + (originalWidth * scale / 22 + 5) * i , position.y - bagHeight * 2.7 - m * (originalHeight * scale / 22 + 23) ); // �����λλ��  
            slot->setTag ( i + 1 ); // ���ò�λ�ı�ǩ  
            this->addChild ( slot , 2 );

            _itemSlots.pushBack ( slot );

            // ��Ӵ����¼�  
            auto listener = EventListenerTouchOneByOne::create ();
            listener->onTouchBegan = [this , slot]( Touch* touch , Event* event ) {
                Vec2 location = touch->getLocation ();
                if (slot->getBoundingBox ().containsPoint ( location )) {
                    //onItemSlotClicked ( slot );
                    return true; // ��������¼�  
                }
                return false; // ����������¼�  
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , slot );
        }
    }
}

void StoreUI::updateDisplay () {
    if (!_mybag) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // �˳�����  
    }

    // ��ȡ��ǰѡ�����Ʒ�Ĳ�λ  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // ȷ����ʾ���в�λ  

        // ��ȡ��λ��Ʒ  
        auto item = _mybag->GetItemAt ( i + 1 ); // ��ȡ�ض���λ����Ʒ��ע���λ��1��ʼ 

        // ��ȡ��Ʒ����   
        int itemCount = _mybag->GetItemCountAt ( i + 1 ); // ��ȡ�ò�λ����Ʒ����  

        if (item) {
            CCLOG ( "Item in slot %d: %s" , i + 1 , item->GetName ().c_str () );
        }
        else {
            CCLOG ( "No item in slot %d" , i + 1 );
        }

        // �����Ҫ��ȡ�ض���λ����Ʒ��ʹ�� GetItemAt(int position) �����º���  

        // ���²�λ�Ӿ�����  
        if (item) {
            // ���֮ǰ���ӽڵ�  
            slot->removeAllChildren ();

            // ͼƬ·��  
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

            // ���� item �������������������ǩ�������Ҫ����  
            // ���������ﴴ��һ�� Label ��ʾ����  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i )); // ʹ�ò�λ�ı�ǩ����������ǩ��ΨһID  
            if (!countLabel) {
                // �����ǩ�����ڣ������µı�ǩ  
                countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Arial Bold.ttf" , 20 );
                countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                countLabel->setPosition ( slot->getPosition ().x + slot->getContentSize ().width * 1.7 , slot->getPosition ().y - slot->getContentSize ().height * 1.7 ); // ����λ���ڲ�λ�·�  
                countLabel->setTag ( 200 + i ); // ���ñ�ǩ  
                slot->addChild ( countLabel , 4 ); // ��ӵ��㼶��  
            }
            else {
                // �����ǩ���ڣ���������  
                countLabel->setString ( std::to_string ( itemCount ) );
            }
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
    if (_itemLabel) { // ��� _itemLabel �Ƿ�Ϊ nullptr  
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
    int position = slot->getTag (); // ��ȡ��λλ��  

    // ����Ϊѡ��״̬������ Inventory ����  
    _mybag->SetSelectedItem ( position );
    _selectedSlot = position;

    // ������ʾ  
    updateDisplay ();
}